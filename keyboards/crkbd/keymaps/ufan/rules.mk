MOUSEKEY_ENABLE = yes    # Mouse keys
RGBLIGHT_ENABLE = no    # Enable WS2812 RGB underlight.
VIA_ENABLE      = yes    # Enable VIA
OLED_ENABLE     = yes
OLED_DRIVER     = SSD1306
LTO_ENABLE      = yes
LAYOUTS = split_3x6_3

TAP_DANCE_ENABLE = yes

# extra source file
SRC += tapdance.c
