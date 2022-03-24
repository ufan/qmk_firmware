/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "ufan.h"
#include "features/caps_word.h"
#include "features/custom_shift_keys.h"

#ifdef ACHORDION_ENABLED
#include "features/achordion.h"
#endif

#ifdef COMBO_ENABLE
#include "g/keymap_combo.h"
#endif

#ifdef DYNAMIC_TAPPING_TERM_ENABLE
#define MY_TAPPING_TERM g_tapping_term
#else
#define MY_TAPPING_TERM TAPPING_TERM
#endif

const custom_shift_key_t custom_shift_keys[] = {
    {KC_MINS, KC_GRV},
    {KC_LPRN, KC_RPRN},
    {KC_LBRC, KC_RBRC},
    {KC_LCBR, KC_RCBR},
    {KC_COMM, KC_PIPE},
    {KC_DOT,  KC_BSLS},
    {KC_SLSH, KC_TILD},
    /* {KC_COLN, KC_SCLN}, */
    {KC_UNDS, KC_AT}
};

uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    KC_MINS,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_UNDS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    MY_PARENS,  KC_DOT, LSFT_T(KC_S), LT(3, KC_D), LT(2, KC_F), KC_G,             KC_H, LT(2, KC_J), LT(3, KC_K), RSFT_T(KC_L), KC_QUOT, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    MY_BRACS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                        KC_N,    KC_M, KC_COMM,  KC_A, KC_SLSH,  MY_CBRACS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                  KC_LEAD, LALT_T(KC_TAB), LCTL_T(KC_SPC),        RCTL_T(KC_ENT), RALT_T(KC_BSPC), MY_ALT_ESC
                                      //`--------------------------'  `--------------------------'

  ),
  [1] = LAYOUT_split_3x6_3(
       XXXXXXX, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, XXXXXXX,
       XXXXXXX, XXXXXXX, _______, _______, _______, _______,          _______, _______, _______, _______, XXXXXXX, XXXXXXX,
       XXXXXXX, XXXXXXX, _______, _______, _______, _______,          _______, _______, _______, _______, XXXXXXX, XXXXXXX,
                                  _______, _______, _______,          _______, _______, _______
  ),

  [2] = LAYOUT_split_3x6_3(
      MY_MAKE,         XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX, EMACS_SPC_1,         KC_PLUS, KC_7, KC_8, KC_9, KC_MINS, KC_ESC,
      QK_BOOTLOADER,   XXXXXXX, XXXXXXX, KC_PGDN, XXXXXXX, EMACS_SPC_2,         KC_ASTR, KC_4, KC_5, KC_6, KC_SLSH, KC_UP,
      QK_CLEAR_EEPROM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EMACS_SPC_3,         KC_EQL,  KC_1, KC_2, KC_3, KC_DOT,  KC_DOWN,
                                         _______, EMACS_SPC_4, MY_ALT_ESC,         KC_ENT,  KC_0, KC_BSPC
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
                           XXXXXXX, XXXXXXX, MY_COMMENT_SLSH, KC_LABK, KC_RABK, KC_DQUO,                     KC_AMPR, KC_CIRC, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                           XXXXXXX, XXXXXXX, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL,                      KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                           XXXXXXX, XXXXXXX, MY_COMMENT_ASTR, KC_SLSH, KC_ASTR, KC_BSLS,                     KC_TILD, KC_DLR, KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, MY_NAMESPACE, MY_POINTER,    MY_NEXT_SENT, MY_PROPERTY, _______
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef OLED_ENABLE
#include <stdio.h>

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_ADJUST 2
#define L_LOWER 4
#define L_RAISE 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("QWERT"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Dvorak"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

// tap force hold per key
#ifdef TAPPING_FORCE_HOLD_PER_KEY
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
    case LT(2, KC_F):
    case LT(2, KC_J):
    case LT(3, KC_D):
    case LT(3, KC_K):
    case LSFT_T(KC_S):
    case RSFT_T(KC_L):
        return true;
    default:
        return false;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case LSFT_T(KC_S):
    case RSFT_T(KC_L):
        return MY_TAPPING_TERM + 50;
    default:
        return MY_TAPPING_TERM;
    }
}
#endif

#ifdef ACHORDION_ENABLED
bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t *tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t *other_record) {
    switch (tap_hold_keycode) {
    case RCTL_T(KC_ENT):
        if (other_keycode == RSFT_T(KC_L)) { return true; }
        break;
    }

    return achordion_opposite_hands(tap_hold_record, other_record);
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
  switch (tap_hold_keycode) {
  /*   case HOME_SC: */
  /*   case HOME_Z: */
  /*     return 0;  // Bypass Achordion for these keys. */
  }

  return 800;  // Otherwise use a timeout of 800 ms.
}
#endif

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }

  // achordion: better tap-hold decision
#ifdef ACHORDION_ENABLED
    if (!process_achordion(keycode, record)) { return false; }
#endif

  // custom shift
  if (!process_custom_shift_keys(keycode, record)) { return false; }

  // caps word
  if (!process_caps_word(keycode, record)) { return false; }

  switch (keycode) {
  /* case LSFT_T(KC_LPRN): */
  /*     if (record->tap.count && record->event.pressed) { */
  /*         tap_code16(KC_LPRN); */
  /*         return false; */
  /*     } */
  /*     break; */
  /* case RSFT_T(KC_RPRN): */
  /*     if (record->tap.count && record->event.pressed) { */
  /*         tap_code16(KC_RPRN); */
  /*         return false; */
  /*     } */
  /*     break; */
  case LSFT_T(KC_PLUS):
      if (record->tap.count && record->event.pressed) {
          tap_code16(KC_PLUS);
          return false;
      }
      break;
    }
  return true;
}
#endif // OLED_ENABLE

#ifdef LEADER_ENABLE
LEADER_EXTERNS();
#endif

void matrix_scan_keymap(void) {
    // achordion task
    achordion_task();

    // caps word update timer
    caps_word_task();

    // leader key process
    #ifdef LEADER_ENABLE
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY (KC_I) {
            SEND_STRING("QMK is awsome");
        }
    }
    #endif
}
