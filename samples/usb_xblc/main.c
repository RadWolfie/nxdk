#include <hal/debug.h>
#include <hal/video.h>
#include <windows.h>
#include <usbh_lib.h>
#include <xblc_driver.h>
#include <SDL.h>

/*
 * This demo will detect a Xbox Live Communicator headset and loopback audio
 * from the microphone to the headset's speaker.
*/

//Make a circular FIFO buffer to audio input/output loopback
#define RECORD_BUFF_SIZE 384 //Enough for 8 USB frames at 24kHz mono (24000*2/1000*8)
typedef struct {
    short recorded_data[RECORD_BUFF_SIZE];
    int record_pos;
    int playback_pos;
    char got_first_packet;
} loopback_t;

static const char* sample_rates_str[XBLC_RATE_MAX_NUM] = {
    "8000",
    "11025",
    "16000",
    "22050",
    "24000"
};

static const int sample_rates_hz[XBLC_RATE_MAX_NUM] = {
    8000,
    11025,
    16000,
    22050,
    24000
};

//Audio received from the microphone. There is num_samples in rxdata
static int audio_in_cb(xblc_dev_t *xblc_dev, int16_t *rxdata, int num_samples)
{
    loopback_t *loop = (loopback_t *)xblc_dev->user_data;
    int i = 0;
    while (num_samples--) {
        loop->recorded_data[loop->record_pos] = rxdata[i++];
        loop->record_pos = (loop->record_pos + 1) % RECORD_BUFF_SIZE;
    }
    loop->got_first_packet = 1;
    return i;
}

//Audio output is ready for samples. Provide num_samples to txdata.
static int audio_out_cb(xblc_dev_t *xblc_dev, int16_t *txdata, int num_samples)
{
    loopback_t *loop = (loopback_t *)xblc_dev->user_data;

    //We want to be atleast one packet behind the microphone
    if (!loop->got_first_packet) {
        return 0;
    }

    int i = 0;
    while (num_samples--) {
        txdata[i++] = loop->recorded_data[loop->playback_pos];
        loop->playback_pos = (loop->playback_pos + 1) % RECORD_BUFF_SIZE;
    }
    return i;
}

static void connection_callback(xblc_dev_t *xblc_dev, int status) {
    debugPrint("Xbox Live Communicator Connected on Port %d \n", usbh_xblc_get_port(xblc_dev));
    usbh_xblc_set_sample_rate(xblc_dev, XBLC_RATE_24000);

    xblc_dev->user_data = malloc(sizeof(loopback_t));
    loopback_t *loop = (loopback_t *)xblc_dev->user_data;
    memset(loop, 0, sizeof(loopback_t));

    usbh_xblc_start_audio_in(xblc_dev, audio_in_cb);
    usbh_xblc_start_audio_out(xblc_dev, audio_out_cb);
}

static void disconnection_callback(xblc_dev_t *xblc_dev, int status) {
    debugPrint("Xbox Live Communicator Disconnected from Port %d \n", usbh_xblc_get_port(xblc_dev));
    free(xblc_dev->user_data);
}

int main(void)
{
    int sample_rate_index = XBLC_RATE_24000;
    XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);

    usbh_core_init();
    usbh_xblc_init();
    usbh_install_xblc_conn_callback(connection_callback, disconnection_callback);
    SDL_Init(SDL_INIT_GAMECONTROLLER);
    SDL_Event e;

    while (1) {
        usbh_pooling_hubs();

        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_CONTROLLERDEVICEADDED:
                SDL_GameControllerOpen(e.cdevice.which);
                break;
            case SDL_CONTROLLERDEVICEREMOVED:
                SDL_GameControllerClose(SDL_GameControllerFromInstanceID(e.cdevice.which));
                break;
            case SDL_CONTROLLERBUTTONDOWN:
                if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
                    if (sample_rate_index < XBLC_RATE_MAX_NUM - 1) {
                        sample_rate_index++;
                    }
                }
                if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
                    if (sample_rate_index > 0) {
                        sample_rate_index--;
                    }
                }
            }
        }

        SDL_GameControllerUpdate();
        //Update the sample rate for all devices if required.
        xblc_dev_t *xblc_dev = usbh_xblc_get_device_list();
        while (xblc_dev != NULL) {
            int sample_rate_hz_before = usbh_xblc_get_sample_rate(xblc_dev);
            if (sample_rate_hz_before != sample_rates_hz[sample_rate_index]) {
                usbh_xblc_set_sample_rate(xblc_dev, sample_rate_index);
                debugPrint("Xbox Live Communicator #%d sample rate is set to %s Hz\n", usbh_xblc_get_port(xblc_dev), sample_rates_str[sample_rate_index]);
            }
            xblc_dev = xblc_dev->next;
        }
    }
    //Never reached, but shown for clarity
    SDL_Quit();
    usbh_core_deinit();
    return 0;
}
