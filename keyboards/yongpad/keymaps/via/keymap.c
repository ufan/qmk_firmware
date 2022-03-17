#include <avr/pgmspace.h>
#include "keyboard.h"
#include "keycode.h"
#include "rgblight.h"
#include "timer.h"
#include QMK_KEYBOARD_H
#include "macro_def.h"
#include "tap_dance.h"

/* Layouts  */
enum layers {
    _NUM = 0,
    _ULT,
    _NAV,
    _PRG
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NUM] = LAYOUT( /* Numpad */
    TO(2),   TO(3),
    LT(1, KC_P0),    KC_P1,   KC_P4,   KC_P7,
    KC_PDOT,         KC_P2,   KC_P5,   KC_P8,
    KC_BSPC,         KC_P3,   KC_P6,   KC_P9,
    TD(TD_PLUS_EQL), KC_PMNS, KC_PAST, TD(TD_PLUS_NUMLCK)
  ),

  [_ULT] = LAYOUT( /* Utilities */
    _______,  _______,
    _______, MY_EMAIL_FOX,     MY_PASS_PC,         KC_ESC,
    QK_BOOT, MY_EMAIL_GOOGLE,  MY_PASS_ROUTER,     KC_SPC,
    RGB_MOD, MY_EMAIL_PRIVATE, MY_PASS_BITWARDEN,  KC_EQL,
    RGB_TOG, MY_EMAIL_WORK,    MY_PASS_GOOGLE,     KC_ENT
  ),

  [_NAV] = LAYOUT( /* Navigation */
               TO(0), TO(3),
               SWIN(KC_UP),   C(KC_DOWN), C(KC_PGUP), C(KC_UP),
               SWIN(KC_DOWN), KC_MS_BTN5, C(KC_R),    KC_MS_BTN4,
               SWIN(KC_LEFT), KC_PGDN,    C(KC_PGDN), KC_PGUP,
               SWIN(KC_RGHT), C(KC_K),    C(KC_W),    MY_ALT_ESC
  ),

  [_PRG] = LAYOUT( /* Programming */
               TO(0), TO(2),
               KC_R, KC_S, KC_T, KC_U,
               KC_R, KC_S, KC_T, KC_U,
               KC_R, KC_S, KC_T, KC_U,
               KC_R, KC_S, KC_T, KC_U
  ),
};

/* RGB Light Layers */
#ifdef RGBLIGHT_LAYERS

#define HSV_LAYER1        128, 255, 30
#define HSV_LAYER2        191, 128, 30

const rgblight_segment_t PROGMEM my_default_layer[] = RGBLIGHT_LAYER_SEGMENTS(
      {16, 2, HSV_OFF}
                                                                              );

const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
      {16, 2, HSV_LAYER1}
                                                                             );
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
      {0, 8, HSV_LAYER2}
                                                                             );
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
      {8, 8, HSV_LAYER2}
                                                                             );

const rgblight_segment_t* const PROGMEM my_rgb_layers[] =
    RGBLIGHT_LAYERS_LIST(
                         my_default_layer,
                         my_layer1_layer,
                         my_layer2_layer,
                         my_layer3_layer);

void keyboard_post_init_user() {
    rgblight_layers = my_rgb_layers;
    rgblight_set_layer_state(0, true);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    return state;
}
#endif

/* Encoder configuration */
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Up Encoder */
        if (clockwise) {
            tap_code_delay(KC_WH_U, 10);
        } else {
            tap_code_delay(KC_WH_D, 10);
        }
    }
    else { /* Up Encoder */
        if (IS_LAYER_ON(2) | IS_LAYER_ON(1) | IS_LAYER_ON(0)) { // Navigation
            if (clockwise) {
                tap_code16(LCTL(KC_MINS));
            } else {
                tap_code16(LCTL(KC_EQL));
            }
        } else if (IS_LAYER_ON(3)) { // Programming
            if (clockwise) {
                tap_code_delay(KC_KP_MINUS, 10);
            } else {
                tap_code_delay(KC_KP_PLUS, 10);
            }
        }
    }
    return false;
}
#endif

/* Customize process function */
static bool is_alt_esc_active = false;
static uint16_t alt_esc_timer = 0;

void matrix_scan_user(void)
{
    if (is_alt_esc_active) {
        if (timer_elapsed(alt_esc_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_esc_active = false;
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case MY_ALT_ESC:
        if (record->event.pressed) {
            if (!is_alt_esc_active) {
                is_alt_esc_active = true;
                register_code(KC_LALT);
            }
            alt_esc_timer = timer_read();
            register_code(KC_ESC);
        } else {
            unregister_code(KC_ESC);
        }
        break;
    }
    return true;
};
