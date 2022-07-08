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
  $(LIBSDLMIXER_DIR)/src/codecs/music_drflac.c \
  $(LIBSDLMIXER_DIR)/src/codecs/music_drmp3.c \
  $(LIBSDLMIXER_DIR)/src/codecs/music_ogg_stb.c \
  $(LIBSDLMIXER_DIR)/src/codecs/music_timidity.c \
  $(LIBSDLMIXER_DIR)/src/codecs/music_wav.c \
  $(LIBSDLMIXER_DIR)/src/codecs/mp3utils.c \
  $(LIBSDLMIXER_DIR)/src/codecs/timidity/common.c \
  $(LIBSDLMIXER_DIR)/src/codecs/timidity/instrum.c \
  $(LIBSDLMIXER_DIR)/src/codecs/timidity/mix.c \
  $(LIBSDLMIXER_DIR)/src/codecs/timidity/output.c \
  $(LIBSDLMIXER_DIR)/src/codecs/timidity/playmidi.c \
  $(LIBSDLMIXER_DIR)/src/codecs/timidity/readmidi.c \
  $(LIBSDLMIXER_DIR)/src/codecs/timidity/resample.c \
  $(LIBSDLMIXER_DIR)/src/codecs/timidity/tables.c \
  $(LIBSDLMIXER_DIR)/src/codecs/timidity/timidity.c

# public cflags
NXDK_CFLAGS += -I$(LIBSDLMIXER_DIR)/include
NXDK_CXXFLAGS += -I$(LIBSDLMIXER_DIR)/include

# private cflags
LIBSDLMIXER_CFLAGS := \
  -Wno-pragma-pack -Wno-static-in-inline -DXBOX \
  -DMUSIC_WAV -DMUSIC_OGG -DMUSIC_MID_TIMIDITY \
  -DMUSIC_FLAC_DRFLAC -DMUSIC_MP3_DRMP3 \
  -DOGG_USE_STB -DDR_MP3_NO_SIMD -DDR_FLAC_NO_SIMD \
  -DHAVE_ALLOCA -DFLOAT_LOOKUP -DINT_LOOKUP \
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
