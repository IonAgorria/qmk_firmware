/* Copyright 2024 @ Ion Agorria
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation,  either version 2 of the License,  or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not,  see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#define C_LSCU     LT(LA_CU_SHIFT, KC_LSFT)
#define C_RSCU     LT(LA_CU_SHIFT, KC_RSFT)
#define C_RACU     LT(LA_CU_ALTGR, KC_RALT)
#define C_SCRL     LT(LA_FN, KC_SCRL)
#define C_TGCU     TG(LA_CU_BASE)
#define C_TGKP     TG(LA_KEYPAD)
#define RA(kc)     RALT(kc)

// clang-format off
enum layers {
    LA_BASE,
    LA_CU_BASE,
    LA_CU_SHIFT,
    LA_CU_ALTGR,
    LA_KEYPAD,
    LA_FN
};

enum custom_keycodes {
    CL_BKTK = SAFE_RANGE,
    CL_CARET,
    CL_TILDE,
    C_M4_FN,
    C_KNOB_SW,
    C_KNOB_BTN,
    C_RGB_TOG,
};

enum rgb_led_indexes {
    LED_PRINT_SCR = 13,
    LED_SCROLL_LOCK,
    LED_PAUSE,
    LED_8 = 24,
    LED_MC1 = 33,
    LED_MC2 = 50,
    LED_CAPS_LOCK,
    LED_MC3 = 65,
    LED_MC4 = 80,
};

enum knob_mode_t {
    KNOB_MODE_JOY_X = 0,
    KNOB_MODE_JOY_Y,
    KNOB_MODE_JOY_T,
    KNOB_MODE_MAX
} knob_mode;

static int16_t joy_val[JOYSTICK_AXIS_COUNT] = { 0, 0, 0 };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LA_BASE] = LAYOUT_93_iso(
        C_KNOB_BTN,  KC_ESC,                   KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       KC_F6,       KC_F7,       KC_F8,       KC_F9,       KC_F10,      KC_F11,        KC_F12,      KC_PSCR,     C_SCRL,      KC_PAUS,
                     KC_GRV,      KC_1,        KC_2,        KC_3,        KC_4,        KC_5,        KC_6,        KC_7,        KC_8,        KC_9,        KC_0,        KC_MINS,     KC_EQL,        KC_BSPC,     KC_INS,      KC_HOME,     KC_PGUP,
        JS_1,        KC_TAB,      KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,        KC_Y,        KC_U,        KC_I,        KC_O,        KC_P,        KC_LBRC,     KC_RBRC,                    KC_DEL,      KC_END,      KC_PGDN,
        JS_2,        KC_CAPS,     KC_A,        KC_S,        KC_D,        KC_F,        KC_G,        KC_H,        KC_J,        KC_K,        KC_L,        KC_SCLN,     KC_QUOT,     KC_NUHS,       KC_ENT,
        JS_3,        KC_LSFT,     KC_NUBS,     KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,        KC_N,        KC_M,        KC_COMM,     KC_DOT,      KC_SLSH,                    KC_RSFT,                  KC_UP,
        C_M4_FN,     KC_LCTL,     KC_LGUI,     KC_LALT,                                            KC_SPC,                                             KC_RALT,     KC_RGUI,     KC_APP,        KC_RCTL,     KC_LEFT,     KC_DOWN,     KC_RGHT
    ),

    [LA_CU_BASE] = LAYOUT_93_iso(
        _______,     _______,                  _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,       _______,     _______,     _______,     _______,
                     CL_BKTK,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     KC_SLSH,     S(KC_0),       _______,     _______,     _______,     _______,
        _______,     _______,     KC_Q,        KC_W,        KC_L,        KC_P,        KC_G,        KC_J,        KC_F,        KC_U,        KC_Y,        KC_SCLN,     RA(KC_LBRC), RA(KC_RBRC),                _______,     _______,     _______,
        _______,     _______,     KC_A,        KC_S,        KC_D,        KC_T,        KC_E,        KC_R,        KC_N,        KC_O,        KC_I,        KC_H,        S(KC_COMM),  KC_MINS,       _______,
        _______,     C_LSCU,      RA(KC_GRV),  KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,        KC_K,        KC_M,        _______,     _______,     S(KC_7),                    C_RSCU,                   _______,
        _______,     _______,     _______,     _______,                                            _______,                                            _______,     _______,     _______,       _______,     _______,     _______,     _______
    ),

    [LA_CU_SHIFT] = LAYOUT_93_iso(
        _______,     S(KC_ESC),                S(KC_F1),    S(KC_F2),    S(KC_F3),    S(KC_F4),    S(KC_F5),    S(KC_F6),    S(KC_F7),    S(KC_F8),    S(KC_F9),    S(KC_F10),   S(KC_F11),     S(KC_F12),   S(KC_PSCR),  _______,     S(KC_PAUS),
                     CL_TILDE,    S(KC_1),     RA(KC_2),    RA(KC_3),    S(KC_4),     S(KC_5),     CL_CARET,    S(KC_6),     S(KC_RBRC),  S(KC_8),     S(KC_9),     S(KC_SLSH),  KC_RBRC,       S(KC_BSPC),  S(KC_INS),   S(KC_HOME),  S(KC_PGUP),
        _______,     S(KC_TAB),   S(KC_Q),     S(KC_W),     S(KC_L),     S(KC_P),     S(KC_G),     S(KC_J),     S(KC_F),     S(KC_U),     S(KC_Y),     S(KC_SCLN),  RA(KC_QUOT), RA(KC_BSLS),                S(KC_DEL),   S(KC_END),   S(KC_PGDN),
        _______,     S(KC_CAPS),  S(KC_A),     S(KC_S),     S(KC_D),     S(KC_T),     S(KC_E),     S(KC_R),     S(KC_N),     S(KC_O),     S(KC_I),     S(KC_H),     S(KC_DOT),   S(KC_2),       S(KC_ENT),
        _______,     _______,     RA(KC_1),    S(KC_Z),     S(KC_X),     S(KC_C),     S(KC_V),     S(KC_B),     S(KC_K),     S(KC_M),     KC_NUBS,     S(KC_NUBS),  S(KC_MINS),                 _______,                  S(KC_UP),
        _______,     S(KC_LCTL),  S(KC_LGUI),  S(KC_LALT),                                         S(KC_SPC),                                          S(KC_RALT),  S(KC_RGUI),  S(KC_APP),     S(KC_RCTL),  S(KC_LEFT),  S(KC_DOWN),  S(KC_RGHT)
    ),

    [LA_CU_ALTGR] = LAYOUT_93_iso(
        _______,     _______,                  _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,       _______,     _______,     _______,     _______,
                     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,       _______,     _______,     _______,     _______,
        _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     S(KC_QUOT),  RA(KC_SCLN),                _______,     _______,     _______,
        _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     KC_QUOT,     KC_LBRC,       _______,
        _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     S(KC_EQL),                  _______,                  _______,
        _______,     _______,     _______,     _______,                                            _______,                                            _______,     _______,     _______,       _______,     _______,     _______,     _______
    ),


    [LA_KEYPAD] = LAYOUT_93_iso(
        _______,     _______,                  _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,       _______,     _______,     _______,     _______,
                     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     KC_NUM,      KC_PSLS,     KC_PAST,     KC_PMNS,     _______,       _______,     _______,     _______,     _______,
        _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     KC_KP_7,     KC_KP_8,     KC_KP_9,     KC_PPLS,     _______,                    _______,     _______,     _______,
        _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     KC_KP_4,     KC_KP_5,     KC_KP_6,     KC_PENT,     _______,       _______,
        _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     KC_KP_1,     KC_KP_2,     KC_KP_3,                    _______,                  _______,
        _______,     _______,     _______,     _______,                                            _______,                                            KC_KP_0,     KC_KP_DOT,   KC_KP_ENTER,   _______,     _______,     _______,     _______
    ),

    [LA_FN] = LAYOUT_93_iso(
        _______,     QK_RBT,                   KC_BRID,     KC_BRIU,     KC_TASK,     KC_FILE,     RGB_VAD,     RGB_VAI,     KC_MPRV,     KC_MPLY,     KC_MNXT,     KC_MUTE,     KC_VOLD,       KC_VOLU,     C_TGCU,      _______,     C_TGKP,
                     _______,     BT_HST1,     BT_HST2,     BT_HST3,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,       QK_BOOT,     RGB_M_P,     C_RGB_TOG,   RGB_MOD,
        C_TGCU,      _______,     _______,     _______,     EE_CLR,      _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,                    RGB_HUI,     RGB_SAI,     RGB_SPI,
        C_TGKP,      _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,       _______,
        C_KNOB_SW,   _______,     _______,     _______,     _______,     _______,     _______,     BAT_LVL,     NK_TOGG,     _______,     _______,     _______,     _______,                    _______,                  _______,
        C_M4_FN,     _______,     _______,     _______,                                            _______,                                            _______,     _______,     _______,       _______,     _______,     _______,     _______
    )
};

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_VIRTUAL, //x
    JOYSTICK_AXIS_VIRTUAL, //y
    JOYSTICK_AXIS_VIRTUAL
};

void handle_diacritic_key(keyevent_t* event, uint16_t kc) {
    static unsigned int last_time = 0;
    if (event->pressed) {
        last_time = event->time;
        register_code16(kc);
    } else {
        unregister_code16(kc);
        //Send space to terminate special key
        //Only send space when not keeping pressed as windows will not ignore it otherwise
        if (timer_elapsed(last_time) <= 500) {
            tap_code(KC_SPC);
        }
    }
}

bool process_record_user(uint16_t keycode,  keyrecord_t *record)
{
    switch (keycode) {
        default:
            break;
        case C_RGB_TOG: {
            if (!record->event.pressed) {
                if (!rgb_matrix_is_enabled()) {
                    rgb_matrix_enable();
                }
                HSV hsv = rgb_matrix_get_hsv();
                hsv.v = hsv.v != 0 ? 0 : RGB_MATRIX_MAXIMUM_BRIGHTNESS;
                rgb_matrix_sethsv(hsv.h, hsv.s, hsv.v);
            }
            return false;
        }
        case C_M4_FN: {
            static unsigned int last_time = 0;
            if (record->event.pressed) {
                last_time = record->event.time;
                layer_on(LA_FN);
            } else {
                if (timer_elapsed(last_time) <= TAPPING_TERM) {
                    register_joystick_button(4);
                    unregister_joystick_button(4);
                }
                layer_off(LA_FN);
            }
            return false;
        }
        case C_KNOB_BTN: {
            static int knob_mode_pressed = KNOB_MODE_MAX;
            if (record->event.pressed) {
                //Knob pressed
                if (layer_state_is(LA_FN)) {
                    int joy_index = -1;
                    switch (knob_mode) {
                        case KNOB_MODE_JOY_X:
                            joy_index = 0;
                            break;
                        case KNOB_MODE_JOY_Y:
                            joy_index = 1;
                            break;
                        case KNOB_MODE_JOY_T:
                            joy_index = 2;
                            break;
                        default:
                            break;
                    }
                    if (0 <= joy_index) {
                        joy_val[joy_index] = 0;
                        joystick_set_axis(joy_index, 0);
                    }
                } else {
                    knob_mode_pressed = knob_mode;
                    register_joystick_button(0);
                }
            } else if (knob_mode_pressed != KNOB_MODE_MAX) {
                //Knob unpressed
                unregister_joystick_button(0);
                knob_mode_pressed = KNOB_MODE_MAX;
            }
            return false;
        }
        case C_KNOB_SW: {
            if (record->event.pressed) {
                knob_mode++;
                if (knob_mode >= KNOB_MODE_MAX) {
                    knob_mode = 0;
                }
            }
            return false;
        }
        case CL_BKTK: {
            handle_diacritic_key(&record->event,  KC_LBRC);
            return false;
        }
        case CL_CARET: {
            handle_diacritic_key(&record->event,  S(KC_LBRC));
            return false;
        }
        case CL_TILDE: {
            handle_diacritic_key(&record->event,  RA(KC_4));
            return false;
        }
    }

    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    if (index != 0) {
        return true;
    }
    //Set custom layout ON/OFF according to switch
    if (layer_state_is(LA_CU_BASE) != active) {
        if (active) {
            layer_on(LA_CU_BASE);
        } else {
            layer_off(LA_CU_BASE);
        }
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    //Only for first encoder
    if (index != 0) {
        return true;
    }
    bool is_fn = IS_LAYER_ON(LA_FN);
    int joy_index = -1;
    switch (knob_mode) {
        case KNOB_MODE_JOY_X:
        case KNOB_MODE_JOY_Y: {
            joy_index = knob_mode == KNOB_MODE_JOY_X ? 0 : 1;
            int16_t change = is_fn ? 4 : 16;
            if (!clockwise) change = -change;
            joy_val[joy_index] += change;
            break;
        }

        case KNOB_MODE_JOY_T: {
            joy_index = 2;
            int16_t change = is_fn ? 2 : 8;
            if (!clockwise) change = -change;
            joy_val[joy_index] += change;

            if (joy_val[joy_index] < 0) joy_val[joy_index] = 0;

            break;
        }

        default:
            return true;
    }
    if (0 <= joy_index) {
        //Keep internal joystick value consistent so it can be set 0 back
        const int16_t joy_max = 128;
        if (joy_val[joy_index] < -joy_max) joy_val[joy_index] = -joy_max;
        else if (joy_val[joy_index] > joy_max) joy_val[joy_index] = joy_max;

        //Device reports values as 8 bits, so need to limit it
        const int16_t axis_max = 127;
        int16_t axis_val = joy_val[joy_index];
        if (axis_val < -axis_max) axis_val = -axis_max;
        else if (axis_val > axis_max) axis_val = axis_max;

        joystick_set_axis(joy_index, axis_val);
    }


    return false;
}

void rgb_matrix_set_indicator(HSV hsv, uint8_t led) {
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(led, rgb.r, rgb.g, rgb.b);
}

#define RGB_MATRIX_SET_INDICATOR(hsv, led, enabled) \
    if ((enabled) && led >= led_min && led < led_max) { \
        rgb_matrix_set_indicator(hsv, led); \
    }


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    HSV hsv = rgb_matrix_get_hsv();
    hsv.v = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    hsv.s = 192 <= hsv.s ? 0 : 255;
    led_t led_state = host_keyboard_led_state();
    bool is_fn = IS_LAYER_ON(LA_FN);
    bool is_kp = IS_LAYER_ON(LA_KEYPAD);

    HSV hsv_mc3 = hsv;
    hsv_mc3.s = 255;
    bool led_mc3_on = true;
    switch (knob_mode) {
        case KNOB_MODE_JOY_X:
            led_mc3_on = false;
            break;
        case KNOB_MODE_JOY_Y:
            hsv_mc3.h = 0;
            break;
        case KNOB_MODE_JOY_T:
            hsv_mc3.h = 85;
            break;
        default:
            break;
    }

    RGB_MATRIX_SET_INDICATOR(hsv, LED_PRINT_SCR, is_fn);
    RGB_MATRIX_SET_INDICATOR(hsv, LED_SCROLL_LOCK, led_state.scroll_lock);
    RGB_MATRIX_SET_INDICATOR(hsv, LED_PAUSE, is_kp);

    RGB_MATRIX_SET_INDICATOR(hsv, LED_CAPS_LOCK, led_state.caps_lock);
    RGB_MATRIX_SET_INDICATOR(hsv, LED_8, is_kp && led_state.num_lock);

    RGB_MATRIX_SET_INDICATOR(hsv, LED_MC1, IS_LAYER_ON(LA_CU_BASE));
    RGB_MATRIX_SET_INDICATOR(hsv, LED_MC2, is_kp);
    RGB_MATRIX_SET_INDICATOR(hsv_mc3, LED_MC3, led_mc3_on);
    RGB_MATRIX_SET_INDICATOR(hsv, LED_MC4, is_fn);

    return false;
}

void rgb_matrix_enable_set_invisible(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}

void keyboard_post_init_user(void) {
    rgb_matrix_enable_set_invisible();
}

void housekeeping_task_user(void) {
    if (!rgb_matrix_is_enabled() && !rgb_matrix_get_suspend_state()) {
        rgb_matrix_enable_set_invisible();
    }
}

#ifdef FACTORY_RESET_TASK
#error FACTORY_RESET_TASK is set
#endif
