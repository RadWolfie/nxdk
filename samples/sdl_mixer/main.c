#include <hal/debug.h>
#include <hal/xbox.h>
#include <hal/video.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_mixer.h>

static void printSDLErrorAndReboot(void)
{
    debugPrint("SDL_Error: %s\n", SDL_GetError());
    debugPrint("Rebooting in 5 seconds.\n");
    Sleep(5000);
    XReboot();
}

static void printMIXErrorAndReboot(void)
{
    debugPrint("SDL_Mixer Error: %s\n", Mix_GetError());
    debugPrint("Rebooting in 5 seconds.\n");
    Sleep(5000);
    XReboot();
}

// Screen dimension constants
static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

void demo(void)
{
    int done = 0;
    SDL_Window *window;
    SDL_Event event;
    Mix_Music *music;
    Mix_Chunk *sound;

    /* Enable standard application logging */
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL.\n");
        printSDLErrorAndReboot();
    }

    window = SDL_CreateWindow("Demo",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        debugPrint("Window could not be created!\n");
        SDL_Quit();
        printSDLErrorAndReboot();
    }

    SDL_JoystickOpen(0);

    if (Mix_Init(MIX_INIT_OGG) == 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL_mixer.\n");
        SDL_Quit();
        printMIXErrorAndReboot();
    }

    /* Only this exact audio format is supported */
    if (Mix_OpenAudio(48000, AUDIO_S16LSB, 2, 1024) < 0) {
        debugPrint("Mix_OpenAudio failed!\n");
        Mix_Quit();
        SDL_Quit();
        printSDLErrorAndReboot();
    }

    music = Mix_LoadMUS("D:\\threenote.ogg");
    if (music == NULL) {
        Mix_Quit();
        SDL_Quit();
        printSDLErrorAndReboot();
    }

    sound = Mix_LoadWAV("D:\\nxdk.wav");
    if (sound == NULL) {
        Mix_Quit();
        SDL_Quit();
        printSDLErrorAndReboot();
    }

    debugPrint("Press any button to play sound.\n");

    Mix_PlayMusic(music, -1);

    while (!done) {
        /* Check for events */
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                done = 1;
                break;
            case SDL_KEYDOWN:
            case SDL_JOYBUTTONDOWN:
                debugPrint("!");
                Mix_PlayChannel(-1, sound, 0);
                break;
            default:
                break;
            }
        }
        Sleep(10);
    }

    Mix_Quit();
    SDL_Quit();
}

int main(void)
{
    XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);

    demo();
    return 0;
}
