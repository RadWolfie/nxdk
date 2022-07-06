LIBSDLMIXER_DIR = $(NXDK_DIR)/lib/sdl/SDL2_mixer/SDL_mixer

LIBSDLMIXER_SRCS = \
  $(LIBSDLMIXER_DIR)/src/effect_position.c \
  $(LIBSDLMIXER_DIR)/src/effects_internal.c \
  $(LIBSDLMIXER_DIR)/src/effect_stereoreverse.c \
  $(LIBSDLMIXER_DIR)/src/mixer.c \
  $(LIBSDLMIXER_DIR)/src/music.c \
  $(LIBSDLMIXER_DIR)/src/utils.c \
  $(LIBSDLMIXER_DIR)/src/codecs/load_aiff.c \
  $(LIBSDLMIXER_DIR)/src/codecs/load_voc.c \
  $(LIBSDLMIXER_DIR)/src/codecs/music_cmd.c \
  $(LIBSDLMIXER_DIR)/src/codecs/music_flac.c \
  $(LIBSDLMIXER_DIR)/src/codecs/music_fluidsynth.c \
  $(LIBSDLMIXER_DIR)/src/codecs/music_mad.c \
  $(LIBSDLMIXER_DIR)/src/codecs/music_mikmod.c \
  $(LIBSDLMIXER_DIR)/src/codecs/music_modplug.c \
  $(LIBSDLMIXER_DIR)/src/codecs/music_mpg123.c \
  $(LIBSDLMIXER_DIR)/src/codecs/music_nativemidi.c \
  $(LIBSDLMIXER_DIR)/src/codecs/music_ogg.c \
  $(LIBSDLMIXER_DIR)/src/codecs/music_opus.c \
  $(LIBSDLMIXER_DIR)/src/codecs/music_timidity.c \
  $(LIBSDLMIXER_DIR)/src/codecs/music_wav.c \
  $(LIBSDLMIXER_DIR)/src/codecs/music_xmp.c \
  $(LIBSDLMIXER_DIR)/src/codecs/timidity/common.c \
  $(LIBSDLMIXER_DIR)/src/codecs/timidity/instrum.c \
  $(LIBSDLMIXER_DIR)/src/codecs/timidity/mix.c \
  $(LIBSDLMIXER_DIR)/src/codecs/timidity/output.c \
  $(LIBSDLMIXER_DIR)/src/codecs/timidity/playmidi.c \
  $(LIBSDLMIXER_DIR)/src/codecs/timidity/readmidi.c \
  $(LIBSDLMIXER_DIR)/src/codecs/timidity/resample.c \
  $(LIBSDLMIXER_DIR)/src/codecs/timidity/tables.c \
  $(LIBSDLMIXER_DIR)/src/codecs/timidity/timidity.c \
  $(LIBSDLMIXER_DIR)/external/libvorbisidec-1.2.1/block.c \
  $(LIBSDLMIXER_DIR)/external/libvorbisidec-1.2.1/codebook.c \
  $(LIBSDLMIXER_DIR)/external/libvorbisidec-1.2.1/floor0.c \
  $(LIBSDLMIXER_DIR)/external/libvorbisidec-1.2.1/floor1.c \
  $(LIBSDLMIXER_DIR)/external/libvorbisidec-1.2.1/info.c \
  $(LIBSDLMIXER_DIR)/external/libvorbisidec-1.2.1/mapping0.c \
  $(LIBSDLMIXER_DIR)/external/libvorbisidec-1.2.1/mdct.c \
  $(LIBSDLMIXER_DIR)/external/libvorbisidec-1.2.1/registry.c \
  $(LIBSDLMIXER_DIR)/external/libvorbisidec-1.2.1/res012.c \
  $(LIBSDLMIXER_DIR)/external/libvorbisidec-1.2.1/sharedbook.c \
  $(LIBSDLMIXER_DIR)/external/libvorbisidec-1.2.1/synthesis.c \
  $(LIBSDLMIXER_DIR)/external/libvorbisidec-1.2.1/window.c \
  $(LIBSDLMIXER_DIR)/external/libvorbisidec-1.2.1/vorbisfile.c \
  $(LIBSDLMIXER_DIR)/external/libogg-1.3.2/src/bitwise.c \
  $(LIBSDLMIXER_DIR)/external/libogg-1.3.2/src/framing.c

# public cflags
NXDK_CFLAGS += -I$(LIBSDLMIXER_DIR)/include
NXDK_CXXFLAGS += -I$(LIBSDLMIXER_DIR)/include

# private cflags
LIBSDLMIXER_CFLAGS := \
  -Wno-pragma-pack -DXBOX \
  -DMUSIC_WAV -DMUSIC_OGG -DMUSIC_MID_TIMIDITY \
  -DOGG_USE_TREMOR -DOGG_HEADER="<ivorbisfile.h>" \
  -DHAVE_ALLOCA -DFLOAT_LOOKUP -DINT_LOOKUP \
  -I$(LIBSDLMIXER_DIR)/external/libvorbisidec-1.2.1 \
  -I$(LIBSDLMIXER_DIR)/external/libvorbis-1.3.6/include \
  -I$(LIBSDLMIXER_DIR)/external/libvorbisidec-1.2.1/include \
  -I$(LIBSDLMIXER_DIR)/external/libvorbisidec-1.2.1/lib \
  -I$(LIBSDLMIXER_DIR)/external/libvorbisidec-1.2.1/../libogg-1.3.2/include \
  -I$(LIBSDLMIXER_DIR)/external/libogg-1.3.2/include \
  -I$(LIBSDLMIXER_DIR)/src/codecs \
  -I$(LIBSDLMIXER_DIR)/src

LIBSDLMIXER_CXXFLAGS := $(LIBSDLMIXER_CFLAGS)

LIBSDLMIXER_OBJS = $(addsuffix .obj, $(basename $(LIBSDLMIXER_SRCS)))

$(NXDK_DIR)/lib/libSDL_mixer.lib: CFLAGS += $(LIBSDLMIXER_CFLAGS)
$(NXDK_DIR)/lib/libSDL_mixer.lib: CXXFLAGS += $(LIBSDLMIXER_CXXFLAGS)
$(NXDK_DIR)/lib/libSDL_mixer.lib: $(LIBSDLMIXER_OBJS)

main.exe: $(NXDK_DIR)/lib/libSDL_mixer.lib

CLEANRULES += clean-sdl_mixer

.PHONY: clean-sdl_mixer
clean-sdl_mixer:
	$(VE)rm -f $(LIBSDLMIXER_OBJS) $(NXDK_DIR)/lib/libSDL_mixer.lib
