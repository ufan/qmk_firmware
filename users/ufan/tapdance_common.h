#pragma once

#include "quantum.h"

// In most cases, three different keycode supported:
// - single tap: k1
// - double single-tap: k1 k1
// - single hold: k2 (usually modifier or layer switch)
// - double tap:  k3
// Other tap states are rarely used
typedef enum {
    TD_NONE,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_DOUBLE_HOLD,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD,
    TD_UNKNOWN
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

/* Checking the tap state */
extern td_state_t cur_dance(qk_tap_dance_state_t *state);

/* Gloval tap-state keeper */
extern td_tap_t xtap_state;

/* Add support of custom macro keycode for single-tap, single-hold and double-tap */
typedef struct {
    uint16_t kc1; // single-tap
    uint16_t kc2; // single-hold
    uint16_t kc3; // double-tap
} mytd_keypair_t;

void mytd_each_tap(qk_tap_dance_state_t *state, void *user_data);
void mytd_finished(qk_tap_dance_state_t *state, void *user_data);
void mytd_reset(qk_tap_dance_state_t *state, void *user_data);

#define MY_TD_ACTION(kc1, kc2, kc3)                                     \
    {.fn = {mytd_each_tap, mytd_finished, mytd_reset}                   \
            , .user_data = (void*)&((mytd_keypair_t){kc1, kc2, kc3})}

/* NEW TEST */
typedef struct {
    uint16_t kc1; // single-tap
    uint16_t kc2;
    uint8_t  layer;
    void (*layer_function)(uint8_t);
} mytd_layerswitch_keypair_t;

void mytd_layerswitch_each_tap(qk_tap_dance_state_t *state, void *user_data);
void mytd_layerswitch_finished(qk_tap_dance_state_t *state, void *user_data);
void mytd_layerswitch_reset(qk_tap_dance_state_t *state, void *user_data);

#define MY_TDLAYER_MOVE_ACTION(kc1, kc2, layer)                          \
    {.fn = {mytd_layerswitch_each_tap, mytd_layerswitch_finished, mytd_layerswitch_reset}\
            , .user_data = (void*)&((mytd_layerswitch_keypair_t){kc1, kc2, layer, layer_move})}

/* Layer switch for macro keycode */
