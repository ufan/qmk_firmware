#ifndef MACRODEF_H
#define MACRODEF_H

/* Custom Macros */
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKPASS_PC,
    QMKEMAIL_FOX,
};

#define MACRO_STR(keycode, record, macro_string) \
case keycode: \
if(record->event.pressed) { \
    SEND_STRING(macro_string SS_TAP(X_ENT)); \
 } \
return false;

#define PROCESS_MACRO(keycode, record) \
switch(keycode) { \
    MACRO_STR(QMKPASS_PC, record, "ufan2129_zhouyong") \
    MACRO_STR(QMKEMAIL_FOX, record, "zyong06@foxmail.com") \
 }

#endif
