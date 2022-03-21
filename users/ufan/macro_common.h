#pragma once

/* Custom Macros */
enum macro_keycodes {
    MY_MACRO_BEGIN = SAFE_RANGE,
    MY_PASS_PC,
    MY_PASS_ROUTER,
    MY_PASS_BITWARDEN,
    MY_PASS_GOOGLE,
    MY_EMAIL_FOX,
    MY_EMAIL_GOOGLE,
    MY_EMAIL_PRIVATE,
    MY_EMAIL_WORK,
    EMACS_SPC_1,
    EMACS_SPC_2,
    EMACS_SPC_3,
    EMACS_SPC_4,
    MY_MACRO_END
};

#define IS_MACRO(keycode) ((keycode < MY_MACRO_END && keycode > MY_MACRO_BEGIN)? 1 : 0)

#define MACRO_STR(keycode, flag, macro_string)     \
    case keycode:                                    \
        if (flag) {                 \
            SEND_STRING(macro_string SS_TAP(X_ENT)); \
        }                                            \
        break;

#define MACRO_ALTM_STRING(keycode, flag, string) \
    case keycode:                                  \
    if (flag) {               \
        SEND_STRING(SS_LALT("m"));             \
        SEND_STRING(string);                   \
    }                                          \
    break;

#define PROCESS_MACRO(keycode, flag)                            \
    switch (keycode) {                                          \
        MACRO_STR(MY_PASS_PC, flag, "ufan2129_zhouyong")      \
        MACRO_STR(MY_PASS_ROUTER, flag, "yong_router405")     \
        MACRO_STR(MY_PASS_BITWARDEN, flag, "Ufan@Bitw_0532")  \
        MACRO_STR(MY_PASS_GOOGLE, flag, "W0L0veZiY0u!_0532")  \
        MACRO_STR(MY_EMAIL_FOX, flag, "zyong06@foxmail.com")  \
        MACRO_STR(MY_EMAIL_GOOGLE, flag, "zyong06@gmail.com") \
        MACRO_STR(MY_EMAIL_PRIVATE, flag, "yong@ufan.site")   \
        MACRO_STR(MY_EMAIL_WORK, flag, "to be filled")        \
        MACRO_ALTM_STRING(EMACS_SPC_1, flag, "1")             \
        MACRO_ALTM_STRING(EMACS_SPC_2, flag, "2")             \
        MACRO_ALTM_STRING(EMACS_SPC_3, flag, "3")             \
        MACRO_ALTM_STRING(EMACS_SPC_4, flag, "4")             \
        }
