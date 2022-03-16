#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
               TG(2),   TG(3),
    KC_P7, KC_P8, KC_P9, KC_PSLS,
    KC_P4, KC_P5, KC_P6, KC_PAST,
    KC_P1, KC_P2, KC_P3, KC_PMNS,
    LT(1, KC_NLCK), KC_P0, KC_PDOT, KC_PPLS
  ),

  [1] = LAYOUT( /* LED Control */
               TG(2), TG(3),
    RESET, RGB_MOD, RGB_RMOD, RGB_TOG,
    RGB_VAD, RGB_VAI, RGB_HUD,  RGB_MODE_BREATHE,
    RGB_SAD, RGB_SAI, _______,  RGB_MODE_RAINBOW,
    _______, _______, KC_BSPC,  KC_ENT
  ),

  [2] = LAYOUT(
               TG(0), TG(3),
    _______, _______, _______, KC_2,
    _______, _______, _______, QK_BOOT,
    _______, _______, _______, EE_CLR,
    _______, _______, _______, _______
  ),

  [3] = LAYOUT(
               TG(2), TG(0),
    _______, _______, _______, KC_3,
    _______, _______, _______, _______,
    _______, _______, _______, _______,
    _______, _______, _______, _______
  ),
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Left Encoder */
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else if (index == 1) { /* Right Encoder */
        if (clockwise) {
            rgblight_increase_hue();
        } else {
            rgblight_decrease_hue();
        }
    }
    return false;
}
#endif
