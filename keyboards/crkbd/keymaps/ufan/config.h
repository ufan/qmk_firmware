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

#pragma once

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

#define NO_LAYERSWICH_TAPDANCE

#define COMBO_ONLY_FROM_LAYER 0

#ifdef AUTO_SHIFT_ENABLE
/* #define AUTO_SHIFT_DISABLED_AT_STARTUP */
#define AUTO_SHIFT_TIMEOUT    135
#endif

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
#define DYNAMIC_TAPPING_TERM_INCREMENT 15

#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD_PER_KEY

#define UNICODE_SELECTED_MODES UC_LNX

// When idle, turn off Caps Word after 5 seconds.
#define CAPS_WORD_IDLE_TIMEOUT 5000

// leader key configuration
#define LEADER_TIMEOUT 300
#define LEADER_PER_KEY_TIMING
#define LEADER_NO_TIMEOUT

// oled animation, must enable wpm in rules.mk
// if not defined, only logo show on the right side panel
/* #define OLED_ANIMATION_ENABLE */
