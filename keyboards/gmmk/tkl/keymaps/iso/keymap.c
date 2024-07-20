#include QMK_KEYBOARD_H
#include "rgb_matrix.h"
#include "../layers.h"

//Custom keys and macroed keys
#define _______    KC_TRNS
#define C_SCRL     LT(_FN, KC_SCROLLLOCK)
#define C_LSL      LT(_LS, KC_LSFT)
#define C_LSR      LT(_LS, KC_RSFT)
#define C_LG       LT(_LG, KC_RALT)
#define RA(kc)     RALT(kc)

enum custom_keycodes {
    CL_BKTK = SAFE_RANGE,
    CL_CARET,
    CL_TILDE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //Base layer
    [_BL] = KEYMAP(     KC_ESC,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,        KC_F7,      KC_F8,         KC_F9,          KC_F10,         KC_F11,         KC_F12,
                        KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,         KC_7,       KC_8,          KC_9,           KC_0,           KC_MINS,        KC_EQL,
                        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,         KC_U,       KC_I,          KC_O,           KC_P,           KC_LBRC,        KC_RBRC,
                        KC_CAPS,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,         KC_J,       KC_K,          KC_L,           KC_SCLN,        KC_QUOT,        KC_BSLS,
                        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,         KC_M,       KC_COMM,       KC_DOT,         KC_SLSH,        KC_RSFT,        KC_ENT,
                        KC_LCTL,    KC_LGUI,    KC_LALT,    KC_SPC,     KC_RALT,    KC_RGUI,    KC_APP,       KC_RCTL,    KC_LEFT,       KC_DOWN,        KC_UP,          KC_RGHT,        KC_BSPC,
                        KC_NUBS,    KC_PSCR,    C_SCRL,     KC_PAUS,    KC_INS,     KC_HOME,    KC_PGUP,      KC_DEL,     KC_END,        KC_PGDN)

    //Custom layout base layer
    , [_LB] = KEYMAP(   _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        CL_BKTK,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        KC_SLSH,        S(KC_0),
                        _______,    KC_Q,       KC_W,       KC_L,       KC_P,       KC_G,       KC_J,         KC_F,       KC_U,          KC_Y,           KC_SCLN,        RA(KC_LBRC),    RA(KC_RBRC),
                        _______,    KC_A,       KC_S,       KC_D,       KC_T,       KC_E,       KC_R,         KC_N,       KC_O,          KC_I,           KC_H,           S(KC_COMM),     KC_MINS,
                        C_LSL,      KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_K,         KC_M,       _______,       _______,        S(KC_7),        C_LSR,          _______,
                        _______,    _______,    _______,    _______,    C_LG,       _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        RA(KC_GRV), _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______)

    //Custom layout with shift layer
    , [_LS] = KEYMAP(   S(KC_ESC),  S(KC_F1),   S(KC_F2),   S(KC_F3),   S(KC_F4),   S(KC_F5),   S(KC_F6),     S(KC_F7),   S(KC_F8),      S(KC_F9),       S(KC_F10),      S(KC_F11),      S(KC_F12),
                        CL_TILDE,   S(KC_1),    RA(KC_2),   RA(KC_3),   S(KC_4),    S(KC_5),    CL_CARET,     S(KC_6),    S(KC_RBRC),   S(KC_8),         S(KC_9),        S(KC_SLSH),     KC_RBRC,
                        S(KC_TAB),  S(KC_Q),    S(KC_W),    S(KC_L),    S(KC_P),    S(KC_G),    S(KC_J),      S(KC_F),    S(KC_U),       S(KC_Y),        S(KC_SCLN),     RA(KC_QUOT),    RA(KC_BSLS),
                        S(KC_CAPS), S(KC_A),    S(KC_S),    S(KC_D),    S(KC_T),    S(KC_E),    S(KC_R),      S(KC_N),    S(KC_O),       S(KC_I),        S(KC_H),        S(KC_DOT),      S(KC_2),
                        _______,    S(KC_Z),    S(KC_X),    S(KC_C),    S(KC_V),    S(KC_B),    S(KC_K),      S(KC_M),    KC_NUBS,       S(KC_NUBS),     S(KC_MINS),     _______,        S(KC_ENT),
                        S(KC_LCTL), S(KC_LGUI), S(KC_LALT), S(KC_SPC),  S(KC_RALT), S(KC_RGUI), S(KC_APP),    S(KC_RCTL), S(KC_LEFT),    S(KC_DOWN),     S(KC_UP),       S(KC_RGHT),     S(KC_BSPC),
                        RA(KC_1),   S(KC_PSCR), _______,    S(KC_PAUS), S(KC_INS),  S(KC_HOME), S(KC_PGUP),   S(KC_DEL),  S(KC_END),     S(KC_PGDN))

    //Custom layout with altgr layer
    , [_LG] = KEYMAP(   _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        S(KC_QUOT),     RA(KC_SCLN),
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        KC_QUOT,        KC_LBRC,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        S(KC_EQL),      _______,        _______,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______)


    //FN - Special keys, control keys, RGB control, layer switches, etc
    , [_FN] = KEYMAP(   RESET,      KC_BRID,    KC_BRIU,    _______,    _______,    RGB_VAD,    RGB_VAI,      KC_MPRV,    KC_MPLY,       KC_MNXT,        KC_MUTE,        KC_VOLD,        KC_VOLU,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        TG(_LB),    _______,    _______,    EEP_RST,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        _______,    _______,    _______,    _______,    _______,    _______,    NK_TOGG,      _______,    _______,       _______,        _______,        _______,        _______,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        _______,    TG(_LB),    _______,    _______,    RGB_M_P,    RGB_TOG,    RGB_MOD,      RGB_HUI,    RGB_SAI,       RGB_VAI)
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

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        default:
            break;
        case CL_BKTK: {
            handle_diacritic_key(&record->event, KC_LBRC);
            return false;
        }
        case CL_CARET: {
            handle_diacritic_key(&record->event, S(KC_LBRC));
            return false;
        }
        case CL_TILDE: {
            handle_diacritic_key(&record->event, RA(KC_4));
            return false;
        }
    }

    return true;
}
