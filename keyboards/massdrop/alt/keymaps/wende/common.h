#    define foreach(item, array)                                                                                            \
        for (int keep = 1, count = 0, size = sizeof(array) / sizeof *(array); keep && count != size; keep = !keep, count++) \
            for (item = (array) + count; keep; keep = !keep)

enum keyboard_led { KL_ESC = 0, KL_1, KL_2, KL_3, KL_4, KL_5, KL_6, KL_7, KL_8, KL_9, KL_0, KL_HYPHEN, KL_EQL, KL_BSP, KL_DEL, KL_TAB, KL_Q, KL_W, KL_E, KL_R, KL_T, KL_Y, KL_U, KL_I, KL_O, KL_P, KL_LBRACKET, KL_RBRACKET, KL_BACKSLASH, KL_HOME, KL_CPSL, KL_A, KL_S, KL_D, KL_F, KL_G, KL_H, KL_J, KL_K, KL_L, KL_SEMICOLON, KL_GRAVE, KL_RET, KL_PGUP, KL_L_SHIFT, KL_Z, KL_X, KL_C, KL_V, KL_B, KL_N, KL_M, KL_COMMA, KL_DOT, KL_SLASH, KL_R_SHIFT, KL_ARROW_UP, KL_PGDN, KL_L_CTRL, KL_L_ALT, KL_L_META, KL_SPC, KL_R_ALT, KL_FN, KL_ARROW_LEFT, KL_ARROW_DOWN, KL_ARROW_RIGHT, FIRST_LED } ;
#define LAST_LED FIRST_LED + 37

#define KEYBOARD_LED_INNER KL_Q, KL_W, KL_E, KL_R, KL_T, KL_Y, KL_U, KL_I, KL_O, KL_P, KL_LBRACKET, KL_RBRACKET, KL_A, KL_S, KL_D, KL_F, KL_G, KL_H, KL_J, KL_K, KL_L, KL_SEMICOLON, KL_GRAVE, KL_Z, KL_X, KL_C, KL_V, KL_B, KL_N, KL_M, KL_COMMA, KL_DOT, KL_SLASH

