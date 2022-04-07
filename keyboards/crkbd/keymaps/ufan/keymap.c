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

#ifdef COMBO_ENABLE
#include "g/keymap_combo.h"
#endif

uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);
#ifdef ACHORDION_ENABLED
#include "features/achordion.h"
#endif

#ifdef OLED_ENABLE
#include <stdio.h>
char wpm_str[10];

#ifdef OLED_ANIMATION_ENABLE
#define ANIM_INVERT false
#define ANIM_RENDER_WPM true
#define FAST_TYPE_WPM 45
#include "oled/bongocat.c"
#else
#include "oled/logo.c"
#endif
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
  [_BASE] = LAYOUT_split_3x6_3(
                               KC_MINS,  KL_11,  KL_12,  KL_13,  KL_14,  KL_15,         KR_15,  KR_14,  KR_13,  KR_12,  KR_11,  KC_UNDS,
                               KC_EXLM,  KL_21,  KL_22,  KL_23,  KL_24,  KL_25,         KR_25,  KR_24,  KR_23,  KR_22,  KR_21,  KC_SLSH,
                               MY_BRACS, KL_31,  KL_32,  KL_33,  KL_34,  KL_35,         KR_35,  KR_34,  KR_33,  KR_32,  KR_31,  MY_CBRACS,
                                                       KC_LGUI,  KL_41,  KL_42,         KR_42,  KR_41,  MY_ALT_ESC
  ),
  [_QWERT] = LAYOUT_split_3x6_3(
    KC_MINS,  KC_Q,  KC_W,         KC_E,        KC_R,        KC_T,             KC_Y,  KC_U,        KC_I,        KC_O,         KC_P,     KC_UNDS,
    KC_EXLM,  KC_A,  LSFT_T(KC_S), LT(3, KC_D), LT(2, KC_F), KC_G,             KC_H,  LT(2, KC_J), LT(3, KC_K), RSFT_T(KC_L), KC_QUOT,  KC_SLSH,
    MY_BRACS, KC_Z,  KC_X,         KC_C,        KC_V,        KC_B,             KC_N,  KC_M,        KC_COMM,     KC_DOT,       KC_SCLN,  MY_CBRACS,
                                   KC_LGUI,     KL_41,       KL_42,            KR_42, KR_41,       MY_ALT_ESC
  ),
  [_NUM] = LAYOUT_split_3x6_3(
      XXXXXXX, XXXXXXX, LCTL(KC_PLUS), KC_UP,   LCTL(KC_UNDS), EMACS_SPC_1,         KC_PLUS, KC_7, KC_8, KC_9, KC_MINS, XXXXXXX,
      XXXXXXX, XXXXXXX, KC_LEFT,       KC_DOWN, KC_RGHT,       EMACS_SPC_2,         KC_ASTR, KC_4, KC_5, KC_6, KC_SLSH, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX,       EMACS_SPC_3,         KC_EQL,  KC_1, KC_2, KC_3, KC_DOT,  XXXXXXX,
                                       _______, EMACS_SPC_4,   KC_BSPC,             KC_ENT,  KC_0, _______
  ),

  [_SYM] = LAYOUT_split_3x6_3(
     XXXXXXX, QWERT,   MY_COMMENT_SLSH, KC_LABK, KC_RABK, KC_PERC,        KC_AMPR, KC_CIRC, KC_LCBR, KC_RCBR, COLEMAK, XXXXXXX,
     XXXXXXX, KC_GRV,  KC_EXLM,         KC_MINS, KC_PLUS, KC_EQL,         KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_AT,   XXXXXXX,
     XXXXXXX, XXXXXXX, MY_COMMENT_ASTR, KC_SLSH, KC_ASTR, KC_BSLS,        KC_HASH, KC_DLR,  KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX,
                               _______, MY_NAMESPACE, MY_POINTER,         MY_NEXT_SENT, MY_PROPERTY, _______
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return OLED_ROTATION_270;
}

void render_crkbd_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

void render_status(void) {
    // oled_write_P(PSTR("Layout: "), false);
    switch (get_highest_layer(default_layer_state)) {
        case _QWERT:
            oled_write_P(PSTR("QWERT "), false);
            break;
        case _BASE:
            oled_write_P(PSTR("PRGAM "), false);
            break;
    }

    oled_write_P(PSTR("\n"), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("     "), false);
            break;
        case _SYM:
            oled_write_P(PSTR("Sym  "), false);
            break;
        case _NUM:
            oled_write_P(PSTR("Num  "), false);
            break;
        default:
            oled_write_P(PSTR("Unkn "), false);
            break;
    }
    oled_write_P(PSTR("\n"), false);

    uint8_t modifiers = get_mods();

    oled_write_P(((modifiers & MOD_MASK_SHIFT) || (caps_word_get()))? PSTR("SHIFT") : PSTR("\n"), false);
    oled_write_P((modifiers & MOD_MASK_CTRL) ? PSTR("CTRL ") : PSTR("\n"), false);
    oled_write_P((modifiers & MOD_MASK_ALT) ? PSTR("ALT  ") : PSTR("\n"), false);
    oled_write_P((modifiers & MOD_MASK_GUI) ? PSTR("SUPER") : PSTR("\n"), false);

    oled_write_P(PSTR("\n"), false);

    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(PSTR("Mode:\n"), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR(" NUM ") : PSTR("\n"), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR(" CAPS") : PSTR("\n"), false);

#ifdef WPM_ENABLE
    oled_write_P(PSTR("\n"), false);
    sprintf(wpm_str, "WPM:\n%03d", get_current_wpm());
    oled_write(wpm_str, false);
#endif
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();
    } else {
#ifdef OLED_ANIMATION_ENABLE
        render_anim();
        oled_set_cursor(0, 0);
        sprintf(wpm_str, "WPM:%03d", get_current_wpm());
        oled_write(wpm_str, false);
#else
        render_crkbd_logo();
#endif
    }
    return false;
}
#endif

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
  /* case LSFT_T(KC_PLUS): */
  /*     if (record->tap.count && record->event.pressed) { */
  /*         tap_code16(KC_PLUS); */
  /*         return false; */
  /*     } */
  /*     break; */
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
