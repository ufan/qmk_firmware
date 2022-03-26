#pragma once

#include "quantum.h"

enum {
    /* Layer switch row */
    TD_L0_P1,
    TD_L0_CDN,
    TD_L0_SPC1,
    TD_L0_A,
    TD_L0_I,

    TD_L2_P2,
    TD_L2_SWDN_SWRGHT,
    TD_L2_SPC2,
    TD_L2_B,
    TD_L2_J,

    TD_L3_P3,
    TD_L3_PGDN,
    TD_L3_SPC3,
    TD_L3_C,
    TD_L3_K,

    TD_L4_PMNS,
    TD_L4_CW,
    TD_L4_SPC4,
    TD_L4_D,
    TD_L4_L,

    /* Numpad */
    TD_PSLS_NLCK,
    TD_PLUS_EQL,
    TD_PAST_PERC,
    TD_ENT_ESC,

    /* Utility */
    TD_FOX_PC,
    TD_GOOGLES,
    TD_PRIVATE_ROUTER,
    TD_WORK_BITWARDEN,

    /* Navigation */
    TD_CR_CK_CW, // brower: reload, search, close
    TD_CPGUP_MBTN4, // brower: previous tab, backward page
    TD_CPGDN_MBTN5, // brower: next tab, forward page
    TD_SWUP_SWLEFT, // move window: up, left
    TD_LWIN_ESC,
    TD_ZOOM_BROWER,

    TD_END
};

/* Layer switch row */
#define MYTD_L0_P1       TD(TD_L0_P1)
#define MYTD_L0_CDN      TD(TD_L0_CDN)
#define MYTD_L0_SPC1     TD(TD_L0_SPC1)
#define MYTD_L0_A        TD(TD_L0_A)
#define MYTD_L0_I        TD(TD_L0_I)

#define MYTD_L2_P2       TD(TD_L2_P2)
#define MYTD_L2_SWDN_SWRGHT     TD(TD_L2_SWDN_SWRGHT)
#define MYTD_L2_SPC2     TD(TD_L2_SPC2)
#define MYTD_L2_B        TD(TD_L2_B)
#define MYTD_L2_J        TD(TD_L2_J)

#define MYTD_L3_P3       TD(TD_L3_P3)
#define MYTD_L3_PGDN     TD(TD_L3_PGDN)
#define MYTD_L3_SPC3     TD(TD_L3_SPC3)
#define MYTD_L3_C        TD(TD_L3_C)
#define MYTD_L3_K        TD(TD_L3_K)

#define MYTD_L4_PMNS     TD(TD_L4_PMNS)
#define MYTD_L4_CW       TD(TD_L4_CW)
#define MYTD_L4_SPC4     TD(TD_L4_SPC4)
#define MYTD_L4_D        TD(TD_L4_D)
#define MYTD_L4_L        TD(TD_L4_L)

/* Numpad */
#define MYTD_PSLS_NLCK   TD(TD_PSLS_NLCK)
#define MYTD_PLUS_EQL    TD(TD_PLUS_EQL)
#define MYTD_PAST_PERC   TD(TD_PAST_PERC)
#define MYTD_ENT_ESC     TD(TD_ENT_ESC)

/* Utility */
#define MYTD_FOX_PC      TD(TD_FOX_PC)
#define MYTD_GOOGLES     TD(TD_GOOGLES)
#define MYTD_PRIVATE_ROUTER      TD(TD_PRIVATE_ROUTER)
#define MYTD_WORK_BITWARDEN      TD(TD_WORK_BITWARDEN)

/* Navigation */
#define MYTD_CR_CK_CW TD(TD_CR_CK_CW) // brower: reload, search, close
#define MYTD_CPGUP_MBTN4 TD(TD_CPGUP_MBTN4) // brower: previous tab, backward page
#define MYTD_CPGDN_MBTN5 TD(TD_CPGDN_MBTN5) // brower: next tab, forward page
#define MYTD_SWUP_SWLEFT TD(TD_SWUP_SWLEFT) // move window: up, left
#define MYTD_LWIN_ESC TD(TD_LWIN_ESC)
#define MYTD_ZOOM_BROWER TD(TD_ZOOM_BROWER)
