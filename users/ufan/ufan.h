#pragma once

#include QMK_KEYBOARD_H
#include "version.h"
#include "eeprom.h"
#include "macro_common.h"
#include "tapdance.h"

enum custom_keycodes {
    MY_ALT_ESC = MY_MACRO_END,
    MY_MAKE,
    NEW_SAFE_RANGE // new safe range to be used in user code
};
