// Copyright 2022 ufan (@ufan)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Platform defined

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
/* #define LOCKING_SUPPORT_ENABLE */
/* Locking resynchronize hack */
/* #define LOCKING_RESYNC_ENABLE */


// Userspace specific
#define ALT_ESC_TERM 600

#define COMBO_ONLY_FROM_LAYER 0

#define TAPPING_TERM 180
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD

#define UNICODE_SELECTED_MODES UC_LNX

// When idle, turn off Caps Word after 5 seconds.
#define CAPS_WORD_IDLE_TIMEOUT 5000
