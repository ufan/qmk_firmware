#include "tapdance_common.h"
#include "tapdance.h"
#include "macro_common.h"

qk_tap_dance_action_t tap_dance_actions[] = {
    /* Utility */
    [L_CBR_BRC_PRN] = MY_TD_ACTION(KC_LCBR, KC_LBRC, KC_LPRN),
    [R_CBR_BRC_PRN] = MY_TD_ACTION(KC_RCBR, KC_RBRC, KC_RPRN),
    [ASTR_AT_TILD] = MY_TD_ACTION(KC_ASTR, KC_AT, KC_TILD),
    [UNDS_HASH_PIPE] = MY_TD_ACTION(S(KC_MINS), KC_HASH, KC_PIPE),
};
