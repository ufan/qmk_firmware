#include "tap_dance.h"

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_PLUS_NUMLCK] = ACTION_TAP_DANCE_DOUBLE(KC_PSLS, KC_NLCK),
    [TD_PLUS_EQL]    = ACTION_TAP_DANCE_DOUBLE(KC_PPLS, KC_EQL),
};
