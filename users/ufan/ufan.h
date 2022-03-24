#pragma once

#include QMK_KEYBOARD_H
#include "version.h"
#include "eeprom.h"
#include "macro_common.h"

enum custom_keycodes {
    MY_ALT_ESC = MY_MACRO_END,
    MY_MAKE,
    MY_SEL_WORD,
    MY_NEXT_SENT,
    MY_PROPERTY,
    MY_COMMENT_SLSH,
    MY_COMMENT_ASTR,
    MY_BRACES,
    MY_PARENS,
    MY_BRACS,
    MY_CBRACS,
    MY_POINTER,
    MY_NAMESPACE,
    NEW_SAFE_RANGE // new safe range to be used in user code
};
