V=1
SOURCE_DIR=src
BUILD_DIR=build
include $(N64_INST)/include/n64.mk

N64_CFLAGS += -Ilibs/sdl_n64/lib -fdiagnostics-color=never

N64_ROM_TITLE = "Eremit 64"
N64_ROM_SAVETYPE = none
N64_ROM_REGIONFREE = true
N64_ROM_RTC = false

C_ROOT_FILES := $(wildcard src/*.c)
C_SDL_FILES  := $(wildcard libs/sdl_n64/lib/SDL/*.c)

SRC = $(C_ROOT_FILES) $(C_SDL_FILES)
OBJS = $(SRC:%.c=%.o)
DEPS = $(SRC:%.c=%.d)

all: eremit.z64
eremit.z64: $(BUILD_DIR)/eremit.dfs

$(BUILD_DIR)/eremit.dfs: $(wildcard filesystem/*)
	$(N64_MKDFS) $@ filesystem

$(BUILD_DIR)/eremit.elf: $(OBJS)

clean:
	find . -name '*.v64' -delete
	find . -name '*.z64' -delete
	find . -name '*.elf' -delete
	find . -name '*.o' -delete
	find . -name '*.d' -delete
	find . -name '*.bin' -delete
	find . -name '*.plan_bak*' -delete
	find . -name '*.dfs' -delete
	find . -name '*.raw' -delete
	find . -name '*.z64' -delete
	find . -name '*.n64' -delete

-include $(DEPS)

.PHONY: all clean