#include "ufan.h"

/* Customize process function */
static bool     is_alt_esc_active = false;
static uint16_t alt_esc_timer     = 0;

/* new callback to be implemented in keymap-specific code */
__attribute__((weak)) void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
    if (is_alt_esc_active) {
        if (timer_elapsed(alt_esc_timer) > 800) {
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
    switch (keycode) {
        PROCESS_MACRO(keycode, record)
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
    }

    // dispatch to user's keymap implementation
    return process_record_keymap(keycode, record);
};
