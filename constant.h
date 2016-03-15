#ifndef CONSTANT_H
#define CONSTANT_H
#include "QDebug"

enum EDLT_RED_BALL {
    E_R_1 = 1,E_R_2,E_R_3,E_R_4,E_R_5,E_R_6,E_R_7,E_R_8,E_R_9,E_R_10,
    E_R_11,E_R_12,E_R_13,E_R_14,E_R_15,E_R_16,E_R_17,E_R_18,E_R_19,E_R_20,
    E_R_21,E_R_22,E_R_23,E_R_24,E_R_25,E_R_26,E_R_27,E_R_28,E_R_29,E_R_30,
    E_R_31,E_R_32,E_R_33,E_R_34,E_R_35
};

enum EDLT_BLUE_BALL {
    E_B_1 = 1,E_B_2,E_B_3,E_B_4,E_B_5,E_B_6,E_B_7,E_B_8,E_B_9,E_B_10,
    E_B_11,E_B_12
};


struct DLT_WIN_BALL{
    enum EDLT_RED_BALL m_red[5];
    enum EDLT_BLUE_BALL m_blue[2];
};

const int RECENT_NUMBER = 20;

#endif // CONSTANT_H

