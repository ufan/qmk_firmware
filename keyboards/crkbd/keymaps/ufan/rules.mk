MOUSEKEY_ENABLE = yes    # Mouse keys
RGBLIGHT_ENABLE = no    # Enable WS2812 RGB underlight.
VIA_ENABLE      = yes    # Enable VIA
OLED_ENABLE     = yes
WPM_ENABLE  	= no  	# needed for oled animation
OLED_DRIVER     = SSD1306

LTO_ENABLE      = yes
LAYOUTS = split_3x6_3

TAP_DANCE_ENABLE = no
AUTO_SHIFT_ENABLE = no

LEADER_ENABLE = no

COMBO_ENABLE = yes
VPATH += keyboards/gboards

KEY_LOCK_ENABLE = no

DYNAMIC_TAPPING_TERM_ENABLE = no

ACHORDION_ENABLE = no

# extra source file
ifeq ($(strip $(ACHORDION_ENABLE)), yes)
	OPT_DEFS += -DACHORDION_ENABLED
	SRC += features/achordion.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
SRC += tapdance.c
endif

SRC += features/caps_word.c \
       features/custom_shift_keys.c \
