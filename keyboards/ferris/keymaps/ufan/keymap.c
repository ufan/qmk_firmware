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
#include "baselayer.h"
#include "features/caps_word.h"
#include "features/custom_shift_keys.h"

/* Custom combination of the shifted keys  */
const custom_shift_key_t custom_shift_keys[] = {
    // common for all 34-key mapping
    COMMON_SHIFT_KEYS
    // corne specific
    {KC_MINS, KC_GRV},
    {KC_UNDS, KC_AT},
    {KC_EXLM, KC_LPRN},
    {KC_SLSH, KC_RPRN},
};

uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

#ifdef COMBO_ENABLE
#include "g/keymap_combo.h"
#endif

#ifdef ACHORDION_ENABLED
#include "features/achordion.h"
#endif

#ifdef DYNAMIC_TAPPING_TERM_ENABLE
#define MY_TAPPING_TERM g_tapping_term
#else
#define MY_TAPPING_TERM TAPPING_TERM
#endif

/* Layers of keymap  */
enum layer_names {
    _BASE, // default layout is Colemak-DH
    _QWERT, // backup layer is QWERT
    _NUM, // number pad and utility macros
    _SYM, // symboles and editing-related macros
};

// base layers
#define COLEMAK DF(_BASE)
#define QWERT  DF(_QWERT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x5_2(
                               KL_11,  KL_12,  KL_13,  KL_14,  KL_15,         KR_15,  KR_14,  KR_13,  KR_12,  KR_11,
                               KL_21,  KL_22,  KL_23,  KL_24,  KL_25,         KR_25,  KR_24,  KR_23,  KR_22,  KR_21,
                               KL_31,  KL_32,  KL_33,  KL_34,  KL_35,         KR_35,  KR_34,  KR_33,  KR_32,  KR_31,
                                                       KL_41,  KL_42,         KR_42,  KR_41
  ),
  [_QWERT] = LAYOUT_split_3x5_2(
    KC_Q,  KC_W,         KC_E,        KC_R,        KC_T,             KC_Y,  KC_U,        KC_I,        KC_O,         KC_P,
    KC_A,  LSFT_T(KC_S), LT(3, KC_D), LT(2, KC_F), KC_G,             KC_H,  LT(2, KC_J), LT(3, KC_K), RSFT_T(KC_L), KC_QUOT,
    KC_Z,  KC_X,         KC_C,        KC_V,        KC_B,             KC_N,  KC_M,        KC_COMM,     KC_DOT,       KC_SCLN,
                                     KL_41,       KL_42,             KR_42, KR_41
  ),
  [_NUM] = LAYOUT_split_3x5_2(
      XXXXXXX, LCTL(KC_PLUS), KC_UP,   LCTL(KC_UNDS), EMACS_SPC_1,         KC_PLUS, KC_7, KC_8, KC_9, KC_MINS,
      XXXXXXX, KC_LEFT,       KC_DOWN, KC_RGHT,       EMACS_SPC_2,         KC_ASTR, KC_4, KC_5, KC_6, KC_SLSH,
      XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX,       EMACS_SPC_3,         KC_EQL,  KC_1, KC_2, KC_3, KC_DOT,
                                       EMACS_SPC_4,   KC_BSPC,             KC_ENT,  KC_0
  ),

  [_SYM] = LAYOUT_split_3x5_2(
     QWERT,   MY_COMMENT_SLSH, KC_LABK, KC_RABK, KC_PERC,        KC_AMPR, KC_CIRC, KC_LCBR, KC_RCBR, COLEMAK,
     KC_GRV,  KC_EXLM,         KC_MINS, KC_PLUS, KC_EQL,         KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_AT,
     XXXXXXX, MY_COMMENT_ASTR, KC_SLSH, KC_ASTR, KC_BSLS,        KC_HASH, KC_DLR,  KC_LBRC, KC_RBRC, XXXXXXX,
                               MY_NAMESPACE, MY_POINTER,         MY_NEXT_SENT, MY_PROPERTY
  )
};

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

/* uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) { */
/*     switch (keycode) { */
/*     case LSFT_T(KC_S): */
/*     case RSFT_T(KC_L): */
/*         return MY_TAPPING_TERM + 50; */
/*     default: */
/*         return MY_TAPPING_TERM; */
/*     } */
/* } */
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
  // achordion: better tap-hold decision
#ifdef ACHORDION_ENABLED
    if (!process_achordion(keycode, record)) { return false; }
#endif

  // custom shift
  if (!process_custom_shift_keys(keycode, record)) { return false; }

  // caps word
  if (!process_caps_word(keycode, record)) { return false; }

  switch (keycode) {
  }

  return true;
}

#ifdef LEADER_ENABLE
LEADER_EXTERNS();
#endif

void matrix_scan_keymap(void) {
    // achordion task
#ifdef ACHORDION_ENABLED
    achordion_task();
#endif

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
