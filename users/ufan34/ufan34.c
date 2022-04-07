#include "ufan34.h"

#ifdef COMBO_ENABLE
#include "g/keymap_combo.h"
#endif

#ifdef ACHORDION_ENABLED
#include "features/achordion.h"
#endif

#ifdef SELECT_WORD_ENABLED
#include "features/select_word.h"
#endif

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

/* Customize process function */
static bool     is_alt_esc_active = false;
static uint16_t alt_esc_timer     = 0;

/* new callback to be implemented in keymap-specific code */
__attribute__((weak)) void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
    if (is_alt_esc_active) {
        if (timer_elapsed(alt_esc_timer) > ALT_ESC_TERM) {
            unregister_code(KC_LALT);
            is_alt_esc_active = false;
        }
    }

    // achordion task
#ifdef ACHORDION_ENABLED
    achordion_task();
#endif

    // caps word update timer
    caps_word_task();

    //dispatch to user's keymap implementation
    matrix_scan_keymap();
}

//
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();

    // achordion: better tap-hold decision
#ifdef ACHORDION_ENABLED
    if (!process_achordion(keycode, record)) { return false; }
#endif

    // custom shift
    if (!process_custom_shift_keys(keycode, record)) { return false; }

    // caps word
    if (!process_caps_word(keycode, record)) { return false; }

    // select word macro
#ifdef SELECT_WORD_ENABLED
    if (!process_select_word(keycode, record, MY_SEL_WORD)) { return false; }
#endif

    // macros send as string (defined in macro_common.h)
    PROCESS_MACRO(keycode, record->event.pressed)

    // other complicated macros
    switch (keycode) {
    case MY_NEXT_SENT:
        if (record->event.pressed) {
            SEND_STRING(". ");
            add_oneshot_mods(MOD_BIT(KC_LSFT));
        }
        return false;
    case MY_PROPERTY:
        if (record->event.pressed) {
            SEND_STRING("#+:");
            tap_code(KC_LEFT);
        }
        return false;
    case MY_COMMENT_ASTR:
        if (record->event.pressed) {
            SEND_STRING("/*  ");
            tap_code(KC_LEFT);
        }
        return false;
    case MY_COMMENT_SLSH:
        if (record->event.pressed) {
            SEND_STRING("// ");
        }
        return false;
    case MY_BRACES:
        if (record->event.pressed) {
            clear_mods();
            clear_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
                SEND_STRING("{}");
            }
            else if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                SEND_STRING("<>");
            }
            else {
                SEND_STRING("[]");
            }
            tap_code(KC_LEFT);
            set_mods(mods);
        }
        return false;
    case MY_PARENS:
        if (record->event.pressed) {
            SEND_STRING("()");
            tap_code(KC_LEFT);
        }
        return false;
    case MY_BRACS:
        if (record->event.pressed) {
            SEND_STRING("[]");
            tap_code(KC_LEFT);
        }
        return false;
    case MY_CBRACS :
        if (record->event.pressed) {
            SEND_STRING("{}");
            tap_code(KC_LEFT);
        }
        return false;
    case MY_POINTER:
        if (record->event.pressed) {
            if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
                del_oneshot_mods(MOD_MASK_SHIFT);
                SEND_STRING("=>");
                set_mods(mods);
            }
            else {
                SEND_STRING("->");
            }
        }
        return false;
    case MY_NAMESPACE:
        if (record->event.pressed) {
            SEND_STRING("::");
        }
        return false;
    case MY_ALT_ESC: // super ALT+ESC
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
        return false;
    case MY_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
        if (!record->event.pressed) {
            uint8_t temp_mod = get_mods();
            uint8_t temp_osm = get_oneshot_mods();
            clear_mods(); clear_oneshot_mods();
            SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP);
#ifndef FLASH_BOOTLOADER
            if ((temp_mod | temp_osm) & MOD_MASK_SHIFT)
#endif
                {
                    SEND_STRING(":flash");
                }
            if ((temp_mod | temp_osm) & MOD_MASK_CTRL) {
                SEND_STRING(" -j8 --output-sync");
            }
            tap_code(KC_ENT);
            set_mods(temp_mod);
        }
        break;
    }

    // dispatch to user's keymap implementation
    return process_record_keymap(keycode, record);
};
