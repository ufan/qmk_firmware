#include QMK_KEYBOARD_H
#include "macro_def.h"

/* Layouts  */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
               TG(1),   TG(2),
    KC_P7, KC_P8, KC_P9, KC_PSLS,
    KC_P4, KC_P5, KC_P6, KC_PAST,
    KC_P1, KC_P2, KC_P3, KC_PMNS,
    LT(1, KC_P0), KC_PDOT, KC_BSPC, KC_PPLS
  ),

  [1] = LAYOUT( /* LED Control */
               _______, _______,
    _______, _______, _______,  RGB_TOG,
    _______, _______, _______,  RGB_MOD,
    _______, _______, _______,  _______,
    _______, QMKPASS_PC, QMKEMAIL_FOX,  KC_ENT
  ),

  [2] = LAYOUT(
               _______, _______,
    _______, _______, _______, KC_2,
    _______, _______, _______, QK_BOOT,
    _______, _______, _______, EE_CLR,
    _______, _______, _______, QMKBEST
  ),

  [3] = LAYOUT(
               _______, _______,
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


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case QMKBEST:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("QMK is the best thing ever!" SS_TAP(X_ENT));
        } else {
            // when keycode QMKBEST is released
        }
        break;
    }
    return true;
};
