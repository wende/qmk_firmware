#include QMK_KEYBOARD_H
#include "process_unicode.h"
#include <print.h>
# include "rgblight.h"
#include "common.h"
# define array_eq(a, b) (memcmp(a, b, sizeof(a)) == 0)

enum alt_keycodes {

    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout

    C_OR_NORM,
    WIDETXT, // w i d e t e x t   f o r   a   w i d e   b o y
    TAUNTXT, // FoR ThE UlTiMaTe sHiTpOsTiNg eXpErIeNcE

    UC_HELP, // URL for QMK unicode help
    UC_SHRG,              // shrug       - ¯\_(ツ)_/¯
#define UC_100  X(E_100)  // hundo       - 💯
#define UC_BBB  X(E_BBB)  // dat B       - 🅱️
#define UC_CLAP X(E_CLAP) // clap        - 👏
#define UC_EYES X(E_EYES) // shifty eyes - 👀
#define UC_GRIM X(E_GRIM) // grimmace    - 😬
#define UC_THNK X(E_THNK) // thinking    - 🤔
#define UC_UGHH X(E_UGHH) // UGHHHHH     - 😩
};


#define MODS_SHIFT (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL)   || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT   (get_mods() & MOD_BIT(KC_LALT)   || get_mods() & MOD_BIT(KC_RALT))
#define SET_INSERT_MODE_COLOR() rgb_matrix_sethsv(HSV_CYAN)
#define SET_NORMAL_MODE_COLOR() rgb_matrix_sethsv(HSV_ORANGE)
#define SET_LEAD_MODE_COLOR() rgb_matrix_sethsv(HSV_PURPLE)

enum unicode_names {
    E_100,
    E_BBB,
    E_CLAP,
    E_EYES,
    E_GRIM,
    E_THNK,
    E_UGHH,
};
const uint32_t PROGMEM unicode_map[] = {
    [E_BBB]  = 0x1F171,
    [E_100]  = 0x1F4AF,
    [E_EYES] = 0x1F440,
    [E_CLAP] = 0x1f44f,
    [E_GRIM] = 0x1f62c,
    [E_THNK] = 0x1f914,
    [E_UGHH] = 0x1f629,
};

enum alt_layers {
    _QWERTY,
    _VIM_BASE,
    _ACTIONS,
    _MEMES,
};

#define KEY_COLOR_TEXTUAL RGB_WHITE
#define KEY_COLOR_SPECIAL RGB_YELLOW
#define KEY_COLOR_APP RGB_MAGENTA

#define TG_NKRO MAGIC_TOGGLE_NKRO //Toggle 6KRO / NKRO mode
#define ___X___ XXXXXXX // KC_NO

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_ESC,               KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,                KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        C_OR_NORM,             KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        LSFT_T(KC_GRV),        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
        KC_LCTL,               KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RALT, MO(_ACTIONS),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [_VIM_BASE] = LAYOUT(
        KC_ESC,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, TG(_VIM_BASE), _______, _______, _______, _______, _______, _______, \
        KC_TRNS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            KC_LEAD,                            _______, MO(_ACTIONS), _______, _______, _______  \
    ),
    [_ACTIONS] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_MUTE, \
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, KC_PSCR, KC_SLCK, KC_PAUS, DBG_KBD, KC_END,  \
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU, \
        _______, RGB_TOG, _______, _______, _______, MD_BOOT, TG_NKRO, DBG_TOG, KC_MPRV, KC_MNXT, KC_MPLY, _______,          _______, KC_VOLD, \
        _______, _______, _______,                            KC_MPLY,                            MO(2),   _______, _______, _______, _______  \
    ),
    [_MEMES] = LAYOUT(
        ___X___, UC_100,  ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, \
        ___X___, ___X___, ___X___, UC_EYES, ___X___, UC_THNK, ___X___, UC_UGHH, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, \
        TAUNTXT, ___X___, UC_SHRG, ___X___, ___X___, UC_GRIM, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___,          ___X___, ___X___, \
        ___X___, ___X___, ___X___, UC_CLAP, ___X___, UC_BBB,  ___X___, ___X___, ___X___, ___X___, UC_HELP, ___X___,          ___X___, ___X___, \
        UC_M_OS, UC_M_WC, UC_M_LN,                            WIDETXT,                            ___X___, ___X___, ___X___, ___X___, ___X___  \
    ),

    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};

int last_non_vim_hue;
uint32_t layer_state_set_user(uint32_t state) {

    switch (biton32(state)) {
        case _VIM_BASE:
            SET_NORMAL_MODE_COLOR();
            break;

    // case _RAISE:
    //     rgblight_setrgb (0x00,  0x00, 0xFF);
    //     break;
    // case _LOWER:
    //     rgblight_setrgb (0xFF,  0x00, 0x00);
    //     break;
    // case _PLOVER:
    //     rgblight_setrgb (0x00,  0xFF, 0x00);
    //     break;
    // case _ADJUST:
    //     rgblight_setrgb (0x7A,  0x00, 0xFF);
    //     break;
        default:
            SET_INSERT_MODE_COLOR();
            break;
    }
  return state;
}


void keyboard_post_init_user(void) {
  SET_INSERT_MODE_COLOR();
}

LEADER_EXTERNS();
void matrix_scan_user(void) {
    LEADER_LOOP();
}



int default_rgb_mode;
void leader_start(void) {
  SET_LEAD_MODE_COLOR();
  //rgb_matrix_set_mode(RGB_MATRIX_CUSTOM_vim_mode)
}
void leader_end(void) {
   if (IS_LAYER_ON(_VIM_BASE)) {
       SET_NORMAL_MODE_COLOR();
   } else {
       SET_INSERT_MODE_COLOR();
   }
  // Add your code to run when a leader key sequence ends here
}

#define ALFRED_TIMEOUT() wait_ms(20);
bool on_leader(uint16_t keys[]) {
    switch (keys[0]) {
        case KC_A:
            // Apps
            switch (keys[1]) {
                case KC_T:
                    SEND_STRING(SS_LSFT(SS_LCMD("g")));
                    return true;
                case KC_S:
                    register_code(KC_LGUI);
                    tap_code(KC_GRV);
                    tap_code(KC_S);
                    unregister_code(KC_LGUI);
                    return true;
                case KC_D:
                    register_code(KC_LGUI);
                    tap_code(KC_SPACE);
                    unregister_code(KC_LGUI);
                    ALFRED_TIMEOUT();
                    SEND_STRING("slack");
                    tap_code(KC_ENT);
                    return true;
                case KC_C:
                    register_code(KC_LGUI);
                    tap_code(KC_SPACE);
                    unregister_code(KC_LGUI);
                    ALFRED_TIMEOUT();
                    SEND_STRING("code");
                    tap_code(KC_ENT);
                    return true;

                default: return false;
            }
        case KC_SPC:
            register_code(KC_LGUI);
            tap_code(KC_SPACE);
            unregister_code(KC_LGUI);
            return true;
        default:
            return false;
    }
}

bool cmd_down = false;
bool shift_down = false;
bool ctrl_down = false;

// Keys for C_OR_NORM
bool nothing_after_ctl = true;
int c_or_norm_time = 0;

// TODO  Add colouring after each tap
bool process_vim_keypress(uint16_t keycode, keyrecord_t *record) {
    if(IS_LAYER_OFF(_VIM_BASE)) return true;
    switch (keycode) {
        case KC_E:
            // TODO extract this line outside
            if (record->event.pressed) {
                register_code(KC_LALT);
                tap_code(KC_RGHT);
                unregister_code(KC_LALT);
            }
            return false;
        default:
            return true;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if(!process_vim_keypress(keycode, record)) return false;
    static uint32_t key_timer;
    if(record->event.pressed) nothing_after_ctl = false;

    switch (keycode) {
        case C_OR_NORM:
        case KC_LCTRL:
            ctrl_down = record->event.pressed;
            break;

        case KC_LGUI:
            cmd_down = record->event.pressed;
            break;

        case LSFT_T(KC_GRV):
        case KC_LSHIFT:
            shift_down = record->event.pressed;
            break;

        default:
            break;
    }

    // Highlight the keys for shortcuts
    rgb_matrix_clear_overlay();

    if (cmd_down && shift_down) {
        uint8_t keys_app[] = {KL_G, KL_H, KL_V, KL_H};
        foreach (uint8_t* key, keys_app) {
            rgb_matrix_set_color_overlay(*key, KEY_COLOR_APP, 255);
        };
        uint8_t keys_special[] = {KL_R, KL_T, KL_F};
        foreach (uint8_t* key, keys_special) {
            rgb_matrix_set_color_overlay(*key, KEY_COLOR_SPECIAL, 255);
        };

    } else if (cmd_down) {
        uint8_t keys_app[] = {KL_SPC};
        foreach (uint8_t* key, keys_app) {
            rgb_matrix_set_color_overlay(*key, KEY_COLOR_APP, 255);
        };
        uint8_t keys_txt[] = {KL_A, KL_C, KL_V, KL_X};
        foreach (uint8_t* key, keys_txt) {
            rgb_matrix_set_color_overlay(*key, KEY_COLOR_TEXTUAL, 255);
        };
        uint8_t keys_special[] = {KL_S, KL_F, KL_W, KL_R, KL_B, KL_Y};
        foreach (uint8_t* key, keys_special) {
            rgb_matrix_set_color_overlay(*key, KEY_COLOR_SPECIAL, 255);
        };
    } else if (ctrl_down) {
        uint8_t keys_txt[] = {KL_E, KL_A, KL_D, KL_H, KL_W};
        foreach (uint8_t* key, keys_txt) {
            rgb_matrix_set_color_overlay(*key, KEY_COLOR_TEXTUAL, 255);
        };
        uint8_t keys_special[] = {KL_SPC, KL_G, KL_C, KL_S};
        foreach (uint8_t* key, keys_special) {
            rgb_matrix_set_color_overlay(*key, KEY_COLOR_SPECIAL, 255);
        };
    }

    static struct {
        bool on;
        bool first;
    } w_i_d_e_t_e_x_t = {false, false};

    if (w_i_d_e_t_e_x_t.on) {
        if (record->event.pressed) {
            switch (keycode) {
                case KC_A...KC_0:
                case KC_SPC:
                    if (w_i_d_e_t_e_x_t.first) {
                        w_i_d_e_t_e_x_t.first = false;
                    } else {
                        send_char(' ');
                    }
                    break;
                case KC_ENT:
                    w_i_d_e_t_e_x_t.first = true;
                    break;
                case KC_BSPC:
                    send_char('\b'); // backspace
                    break;
            }
        }
    }

    static bool tAuNtTeXt = false;

    if (tAuNtTeXt) {
        if (record->event.pressed) {
            if (keycode != KC_SPC)
                tap_code(KC_CAPS);
        }
    }

    switch (keycode) {
        case KC_G:
            if(MODS_CTRL && record->event.pressed) {
                unregister_code(KC_LCTL);
                tap_code(KC_ESC);
                register_code(KC_LCTL);
                return false;
            }
        case KC_SPC:
            if(MODS_CTRL && record->event.pressed) {
                process_leader(KC_LEAD, record);
                return false;
            }
            return true;

        case C_OR_NORM:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                nothing_after_ctl = true;
                c_or_norm_time = timer_read();

            } else {
                if(nothing_after_ctl && timer_elapsed(c_or_norm_time) < C_OR_NORM_DELAY) {
                    layer_invert(_VIM_BASE);
                }
                unregister_code(KC_LCTL);
            }
            return false;
        /* z e s t y   m e m e s */
        case WIDETXT:
            if (record->event.pressed) {
                w_i_d_e_t_e_x_t.on = !w_i_d_e_t_e_x_t.on;
                w_i_d_e_t_e_x_t.first = true;
            }
            return false;
        case TAUNTXT:
            if (record->event.pressed) {
                tAuNtTeXt = !tAuNtTeXt;
            }
            return false;

        /* Unicode */
        case UC_HELP:
            if (record->event.pressed) {
                SEND_STRING("https://beta.docs.qmk.fm/features/feature_unicode#input-modes");
            }
            return false;
        case UC_SHRG: // ¯\_(ツ)_/¯
            if (record->event.pressed) {
                send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
            }
            return false;
        case RGB_RMOD:
            if (record->event.pressed) {
                default_rgb_mode = rgb_matrix_get_mode() - 1;
            }
            return true;
        case RGB_MOD:
            if (record->event.pressed) {
                default_rgb_mode = rgb_matrix_get_mode() + 1;
            }
            return true;
        /* Massdrop debug */
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}

