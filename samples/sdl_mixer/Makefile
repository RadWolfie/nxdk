XBE_TITLE = nxdk\ sample\ -\ SDL2_mixer
GEN_XISO = $(XBE_TITLE).iso
SRCS = $(CURDIR)/main.c
RESOURCES = $(OUTPUT_DIR)/threenote.ogg $(OUTPUT_DIR)/nxdk.wav
NXDK_DIR ?= $(CURDIR)/../..
NXDK_SDL = y
NXDK_SDL_MIXER = y

include $(NXDK_DIR)/Makefile

TARGET += $(RESOURCES)

$(GEN_XISO): $(RESOURCES)

$(OUTPUT_DIR)/%.ogg: $(CURDIR)/%.ogg $(OUTPUT_DIR)
	$(VE)cp '$<' '$@'

$(OUTPUT_DIR)/%.wav: $(CURDIR)/%.wav $(OUTPUT_DIR)
	$(VE)cp '$<' '$@'
