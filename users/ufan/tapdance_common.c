#include "tapdance_common.h"
#include "macro_common.h"

td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }
    else return TD_UNKNOWN;
}

/* standard */
void mytd_each_tap(qk_tap_dance_state_t *state, void *user_data) {}

void mytd_finished(qk_tap_dance_state_t *state, void *user_data)
{
    mytd_keypair_t *pair = (mytd_keypair_t*)user_data;
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
    case TD_SINGLE_TAP:
        if(IS_MACRO(pair->kc1))
            PROCESS_MACRO(pair->kc1, true)
        else
            tap_code16(pair->kc1);
        break;
    case TD_SINGLE_HOLD:
        if(IS_MACRO(pair->kc2))
            PROCESS_MACRO(pair->kc2, true)
        else if (pair->kc2 != KC_NO) {
            tap_code16(pair->kc2);
        }
        break;
    case TD_DOUBLE_TAP:
        if(IS_MACRO(pair->kc3))
            PROCESS_MACRO(pair->kc3, true)
        else if (pair->kc3 != KC_NO) {
            tap_code16(pair->kc3);
        }
        break;
    default:
        break;
    }

}
void mytd_reset(qk_tap_dance_state_t *state, void *user_data)
{
    /* mytd_keypair_t *pair = (mytd_keypair_t*)user_data; */
    /* xtap_state.state = cur_dance(state); */
    /* switch (xtap_state.state) { */
    /* case TD_SINGLE_TAP: */
    /*     if(!IS_MACRO(pair->kc1)) */
    /*         unregister_code16(pair->kc1); */
    /*     break; */
    /* case TD_SINGLE_HOLD: */
    /*     if (!IS_MACRO(pair->kc2) && pair->kc2 != KC_NO) { */
    /*         unregister_code16(pair->kc2); */
    /*     } */
    /*     break; */
    /* case TD_DOUBLE_TAP: */
    /*     if (!IS_MACRO(pair->kc3) && pair->kc3 != KC_NO) { */
    /*         unregister_code16(pair->kc3); */
    /*     } */
    /*     break; */
    /* default: */
    /*     break; */
    /* } */
    xtap_state.state = TD_NONE;
}


/* Layer switch */
#ifndef NO_LAYERSWICH_TAPDANCE
void mytd_layerswitch_each_tap(qk_tap_dance_state_t *state, void *user_data)
{
}

void mytd_layerswitch_finished(qk_tap_dance_state_t *state, void *user_data)
{
    mytd_layerswitch_keypair_t *pair = (mytd_layerswitch_keypair_t*)user_data;
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
    case TD_SINGLE_TAP:
        if(IS_MACRO(pair->kc1))
            PROCESS_MACRO(pair->kc1, true)
        else
            register_code16(pair->kc1);
        break;
    case TD_SINGLE_HOLD:
        pair->layer_function(pair->layer);
        break;
    case TD_DOUBLE_TAP:
        if(IS_MACRO(pair->kc2))
            PROCESS_MACRO(pair->kc2, true)
        else if (pair->kc2 != KC_NO) {
            register_code16(pair->kc2);
        }
        break;
    default:
        break;
    }
}

void mytd_layerswitch_reset(qk_tap_dance_state_t *state, void *user_data)
{
    mytd_layerswitch_keypair_t *pair = (mytd_layerswitch_keypair_t*)user_data;
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
    case TD_SINGLE_TAP:
        if(!IS_MACRO(pair->kc1))
            unregister_code16(pair->kc1);
        break;
    case TD_DOUBLE_TAP:
        if (!IS_MACRO(pair->kc2) && pair->kc2 != KC_NO) {
            unregister_code16(pair->kc2);
        }
        break;
    default:
        break;
    }
    xtap_state.state = TD_NONE;
}
#endif
