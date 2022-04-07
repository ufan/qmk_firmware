/* Define alias name based on physical position for main 34 keys in base layer  */
/* Note: the row/column indexes are based on the 34 keys, regardless of the actual
         layout. For example, standard corne has one more colume but it is not co-
         unted in the following mapping */

// The mapping to the imagined layout is like this :
//     KL_11 KL_12 KL_13 KL_14 KL_15       KR_15 KR_14 KR_13 KR_12 KR_11
//     KL_21 KL_22 KL_23 KL_24 KL_25       KR_25 KR_24 KR_23 KR_22 KR_21
//     KL_31 KL_32 KL_33 KL_34 KL_35       KR_35 KR_34 KR_33 KR_32 KR_31
//                       KL_41 KL_42       KR_42 KR_41

/* current mapping is based on colemak-dh  */

#define KL_11 KC_Q
#define KL_12 KC_W
#define KL_13 KC_F
#define KL_14 KC_P
#define KL_15 KC_B
#define KL_21 KC_A
#define KL_22 LSFT_T(KC_R)
#define KL_23 LT(3, KC_S)
#define KL_24 LT(2, KC_T)
#define KL_25 KC_G
#define KL_31 KC_Z
#define KL_32 KC_X
#define KL_33 KC_C
#define KL_34 KC_D
#define KL_35 KC_V
#define KL_41 LALT_T(KC_TAB)
#define KL_42 LCTL_T(KC_SPC)

#define KR_15 KC_J
#define KR_14 KC_L
#define KR_13 KC_U
#define KR_12 KC_Y
#define KR_11 KC_QUOT
#define KR_25 KC_M
#define KR_24 LT(2, KC_N)
#define KR_23 LT(3, KC_E)
#define KR_22 RSFT_T(KC_I)
#define KR_21 KC_O
#define KR_35 KC_K
#define KR_34 KC_H
#define KR_33 KC_COMM
#define KR_32 KC_DOT
#define KR_31 KC_SCLN
#define KR_42 RCTL_T(KC_ENT)
#define KR_41 RALT_T(KC_BSPC)

#define COMMON_SHIFT_KEYS {KC_COMM, KC_EXLM},   \
                          {KC_DOT,  KC_TILD},   \
                          {KC_SCLN, KC_QUES},
