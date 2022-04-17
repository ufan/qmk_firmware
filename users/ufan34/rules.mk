# Common Build Options for all my keyboards
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
NKRO_ENABLE = yes            # Enable N-Key Rollover
LTO_ENABLE = yes 			# Link time optimization to reduce firmware size

AUDIO_ENABLE = no           # Audio output
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration

NKRO_ENABLE = yes
COMBO_ENABLE = yes
VPATH += keyboards/gboards

# Extra sources
SRC += features/caps_word.c \
       features/custom_shift_keys.c \
	   $(USER_PATH)/ufan34.c	\

# Extra functionality
ACHORDION_ENABLE = no
ifeq ($(strip $(ACHORDION_ENABLE)), yes)
	OPT_DEFS += -DACHORDION_ENABLED
	SRC += features/achordion.c
endif

FLASH_BOOTLOADER = no
ifeq ($(strip $(FLASH_BOOTLOADER)), yes)
    OPT_DEFS += -DFLASH_BOOTLOADER
endif

SELECT_WORD_ENABLE = no
ifeq ($(strip $(SELECT_WORD_ENABLE)), yes)
	OPT_DEFS += -DSELECT_WORD_ENABLED
	SRC += $(USER_PATH)/features/select_word.c
endif
