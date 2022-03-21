# Common Build Options for all my keyboards
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite

MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
NKRO_ENABLE = no            # Enable N-Key Rollover

AUDIO_ENABLE = no           # Audio output
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration

LTO_ENABLE = yes 			# Link time optimization to reduce firmware size

ifeq ($(strip $(FLASH_BOOTLOADER)), yes)
    OPT_DEFS += -DFLASH_BOOTLOADER
endif

# Extra sources
SRC += $(USER_PATH)/ufan.c

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += $(USER_PATH)/tapdance_common.c
endif
