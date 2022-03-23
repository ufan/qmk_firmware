#include "ufan.h"

#ifdef SELECT_WORD_ENABLED
#include "features/select_word.h"
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

    //dispatch to user's keymap implementation
    matrix_scan_keymap();
}

//
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // select word macro
    #ifdef SELECT_WORD_ENABLED
    if (!process_select_word(keycode, record, MY_SEL_WORD)) { return false; }
    #endif

    // macros send as string (defined in macro_common.h)
    PROCESS_MACRO(keycode, record->event.pressed)

    // other complicated macros
    switch (keycode) {
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
