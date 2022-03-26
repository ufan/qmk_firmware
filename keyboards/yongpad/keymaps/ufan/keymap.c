#include <avr/pgmspace.h>
#include "keyboard.h"
#include "keycode.h"
#include "rgblight.h"
#include "timer.h"
#include QMK_KEYBOARD_H
#include "yongpad.h"
#include "tapdance.h"
#include "ufan.h"

/* Layouts  */
enum layers { _NUM = 0, _ULT, _NAV, _PRG, _EXT};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_NUM] = LAYOUT(/* Numpad */
                    TO(0),         MY_PASS_PC,
                    LT(1, KC_0),  MYTD_L0_P1,   KC_4,         KC_7,
                    KC_BSPC,       MYTD_L2_P2,   KC_5,         KC_8,
                    KC_DOT,       MYTD_L3_P3,   KC_6,         KC_9,
                    MYTD_PLUS_EQL, MYTD_L4_PMNS, MYTD_PAST_PERC,MYTD_PSLS_NLCK),

    [_ULT] = LAYOUT(/* Utilities */
                    _______, _______,
                    _______, _______, MYTD_FOX_PC,         _______,
                    QK_BOOT, _______, MYTD_GOOGLES,        _______,
                    MY_MAKE, _______, MYTD_PRIVATE_ROUTER, _______,
                    RGB_TOG, _______, MYTD_WORK_BITWARDEN, MYTD_ENT_ESC),

    [_NAV] = LAYOUT(/* Navigation */
                    _______,     _______,
                    EMACS_SPC_1, MYTD_L0_CDN,         MYTD_CPGUP_MBTN4, C(KC_UP),
                    EMACS_SPC_2, MYTD_L2_SWDN_SWRGHT, MYTD_CR_CK_CW,    MYTD_SWUP_SWLEFT,
                    EMACS_SPC_3, MYTD_L3_PGDN,        MYTD_CPGDN_MBTN5, KC_PGUP,
                    EMACS_SPC_4, KC_F,                MYTD_LWIN_ESC,    MY_ALT_ESC),

    [_PRG] = LAYOUT(/* Programming */
                    _______, _______,
                    KC_ASDN, MYTD_L0_SPC1, KC_T,        KC_U,
                    KC_ASUP, MYTD_L2_SPC2, MY_SEL_WORD, KC_U,
                    KC_ASRP, MYTD_L3_SPC3, KC_T,        KC_U,
                    KC_ASTG, MYTD_L4_SPC4, KC_T,        KC_U),

    [_EXT] = LAYOUT(/* Extra for future usage */
                    _______, _______,
                    KC_M, MYTD_L0_I, KC_E, KC_A,
                    KC_N, MYTD_L2_J, KC_F, KC_B,
                    KC_O, MYTD_L3_K, KC_G, KC_C,
                    KC_P, MYTD_L4_L, KC_H, KC_D),
};

/* RGB Light Layers */
#define HSV_LAYER1 128, 255, 10
#define HSV_LAYER2 191, 128, 10

const rgblight_segment_t PROGMEM my_default_layer[] = RGBLIGHT_LAYER_SEGMENTS({16, 2, HSV_OFF});
/* const rgblight_segment_t PROGMEM my_default_layer[] = RGBLIGHT_LAYER_SEGMENTS({16, 2, HSV_LAYER1}); */
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_LAYER2});
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({4, 4, HSV_LAYER2});
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({8, 4, HSV_LAYER2});
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS({12, 4, HSV_LAYER2});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] =
    RGBLIGHT_LAYERS_LIST(my_default_layer,
                         my_layer1_layer,
                         my_layer2_layer,
                         my_layer3_layer,
                         my_layer4_layer);

void keyboard_post_init_user() {
    rgblight_layers = my_rgb_layers;
    rgblight_set_layer_state(0, true);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
    return state;
}

/* Encoder function */
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Up Encoder */
        if (clockwise) {
            tap_code_delay(KC_WH_U, 10);
        } else {
            tap_code_delay(KC_WH_D, 10);
        }
    } else {                                                    /* Up Encoder */
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

// customize record processing
/* bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { */
/*     return true; */
/* } */
