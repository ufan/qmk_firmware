#ifndef MACRODEF_H
#define MACRODEF_H

/* Custom Macros */
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    MY_PASS_PC,
    MY_PASS_ROUTER,
    MY_PASS_BITWARDEN,
    MY_PASS_GOOGLE,
    MY_EMAIL_FOX,
    MY_EMAIL_GOOGLE,
    MY_EMAIL_PRIVATE,
    MY_EMAIL_WORK,
    MY_ALT_ESC
};

#define MACRO_STR(keycode, record, macro_string) \
case keycode: \
if(record->event.pressed) { \
    SEND_STRING(macro_string SS_TAP(X_ENT)); \
 } \
return false;

#define PROCESS_MACRO(keycode, record)                         \
    switch (keycode) {                                         \
        MACRO_STR(MY_PASS_PC, record, "ufan2129_zhouyong")     \
        MACRO_STR(MY_PASS_ROUTER, record, "yong_router405")    \
        MACRO_STR(MY_PASS_BITWARDEN, record, "Ufan@Bitw_0532") \
        MACRO_STR(MY_PASS_GOOGLE, record, "W0L0veZiY0u!_0532") \
        MACRO_STR(MY_EMAIL_FOX, record, "zyong06@foxmail.com") \
        MACRO_STR(MY_EMAIL_GOOGLE, record, "zyong06@gmail.com") \
        MACRO_STR(MY_EMAIL_PRIVATE, record, "yong@ufan.site") \
        MACRO_STR(MY_EMAIL_WORK, record, "to be filled") \
    }

#endif
