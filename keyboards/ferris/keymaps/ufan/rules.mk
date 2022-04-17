VIA_ENABLE      = no    # Enable VIA
LTO_ENABLE      = yes
TAP_DANCE_ENABLE = no
AUTO_SHIFT_ENABLE = no
LEADER_ENABLE = no

NKRO_ENABLE = yes
COMBO_ENABLE = yes
VPATH += keyboards/gboards

DYNAMIC_TAPPING_TERM_ENABLE = no
ACHORDION_ENABLE = no

# extra source file
ifeq ($(strip $(ACHORDION_ENABLE)), yes)
	OPT_DEFS += -DACHORDION_ENABLED
	SRC += features/achordion.c
endif

SRC += features/caps_word.c \
       features/custom_shift_keys.c \
