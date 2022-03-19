// Copyright 2022 ufan (@ufan)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0x6a6a
#define PRODUCT_ID 0x1000
#define DEVICE_VER 0x0001
#define MANUFACTURER ufan.site
#define PRODUCT YongPad

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

// last row is Encoder Row
#define MATRIX_ROW_PINS \
    { F4, F5, F6, F7, B1 }
#define MATRIX_COL_PINS \
    { D4, C6, D7, E6 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* RGB light */
#define RGB_DI_PIN D3
#define RGBLED_NUM 18
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 128 /* The maximum brightness level */
#define RGBLIGHT_SLEEP         /* If defined, the RGB lighting will be switched off when the host goes to sleep */
#define RGBLIGHT_LAYERS
/* #define RGBLIGHT_ANNIMATION */
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF

/* ENCODER THINGS */
#define ENCODERS_PAD_A \
    { B4, B5 }
#define ENCODERS_PAD_B \
    { B2, B6 }

/* Bootmagic lite key */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
