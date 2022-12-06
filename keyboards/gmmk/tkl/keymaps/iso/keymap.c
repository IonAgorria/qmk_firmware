#include QMK_KEYBOARD_H
#include "rgb_matrix.h"

//Layers
#define _BL 0
#define _FN 1
#define _ME 2
#define _KP 3

//Custom keys and macroed keys
#ifndef _______
#define _______    KC_TRNS
#endif
#define C_CADEL    LCTL(LALT(KC_DEL))
#define C_FNKEY    0x1688
#define C_LOCKG    0x1689
#define C_MEKEY    0x168A

static uint8_t media_keys_on = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //Base layer
    [_BL] = KEYMAP(     KC_ESC,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,        KC_F7,      KC_F8,         KC_F9,          KC_F10,         KC_F11,         KC_F12,
                        KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,         KC_7,       KC_8,          KC_9,           KC_0,           KC_MINS,        KC_EQL,
                        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,         KC_U,       KC_I,          KC_O,           KC_P,           KC_LBRC,        KC_RBRC,
                        KC_CAPS,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,         KC_J,       KC_K,          KC_L,           KC_SCLN,        KC_QUOT,        KC_BSLS,
                        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,         KC_M,       KC_COMM,       KC_DOT,         KC_SLSH,        KC_RSFT,        KC_ENT,
                        KC_LCTL,    KC_LGUI,    KC_LALT,    KC_SPC,     KC_RALT,    KC_RGUI,    KC_APP,       KC_RCTL,    KC_LEFT,       KC_DOWN,        KC_UP,          KC_RGHT,        KC_BSPC,
                        KC_NUBS,    KC_PSCR,    C_FNKEY,    KC_PAUS,    KC_INS,     KC_HOME,    KC_PGUP,      KC_DEL,     KC_END,        KC_PGDN),

    //FN - Special keys, control keys, RGB control, layer switches, etc
    [_FN] = KEYMAP(     RESET,      _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        _______,    _______,    _______,    EEP_RST,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        KC_LOCK,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        C_CADEL,
                        C_LOCKG,    C_MEKEY,    _______,    TG(_KP),    RGB_M_P,    RGB_TOG,    RGB_MOD,      RGB_HUI,    RGB_SAI,       RGB_VAI),

    //Media keys
    [_ME] = KEYMAP(     _______,    KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_MSTP,    KC_MSEL,    KC_MYCM,      KC_CALC,    KC_WSCH,       KC_SLCK,        KC_MUTE,        KC_VOLD,        KC_VOLU,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        _______,    C_MEKEY,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______),

    //Numpad layer
    [_KP] = KEYMAP(     _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    _______,       _______,        _______,        _______,        _______,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    KC_NUMLOCK,    KC_KP_SLASH,    KC_KP_ASTERISK, KC_KP_MINUS,    _______,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    KC_KP_7,       KC_KP_8,        KC_KP_9,        KC_KP_PLUS,     _______,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    KC_KP_4,       KC_KP_5,        KC_KP_6,        KC_KP_ENTER,    _______,
                        _______,    _______,    _______,    _______,    _______,    _______,    _______,      _______,    KC_KP_1,       KC_KP_2,        KC_KP_3,        _______,        _______,
                        _______,    _______,    _______,    _______,    KC_KP_0,    KC_KP_DOT,  KC_KP_ENTER,  _______,    _______,       _______,        _______,        _______,        _______,
                        _______,    _______,    _______,    TG(_KP),    _______,    _______,    _______,      _______,    _______,       _______)
};

void matrix_init_user(void) {
    setPinOutput(LED_LEFT_PIN);
    setPinOutput(LED_RIGHT_PIN);
    writePin(LED_LEFT_PIN, !LED_PIN_ON_STATE);
    writePin(LED_RIGHT_PIN, !LED_PIN_ON_STATE);
}

void matrix_scan_user(void)
{
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case C_FNKEY: {
            // Only unset media keys if layer wasn't already enabled before pressing FN key
            if (record->event.pressed) {
                layer_on(_FN);
                if (!media_keys_on) {
                    layer_on(_ME);
                }
            } else {
                layer_off(_FN);
                if (!media_keys_on) {
                    layer_off(_ME);
                    //Manually set color when off as set_color wont be called
                    /*
                    if (!rgb_matrix_is_enabled()) {
                        rgb_matrix_set_color(13, 0, 0, 0);
                    }
                    */
                }
            }
            return false;
        }
        case C_MEKEY: {
            //Toggle media key
            if (record->event.pressed) {
                media_keys_on = !media_keys_on;
            }
            //Set layer state if FN is not active
            if (!layer_state_is(_FN)) {
                if (media_keys_on) {
                    layer_on(_ME);
                } else {
                    layer_off(_ME);
                }
            }
            return false;
        }
        case C_LOCKG: {
            //Win key lock
            if (record->event.pressed) {
                keymap_config.raw = eeconfig_read_keymap();
                keymap_config.no_gui = !keymap_config.no_gui;
                eeconfig_update_keymap(keymap_config.raw);
                clear_keyboard();
            }

            return false;
        }
    }

    return true;
}

bool led_update_user(led_t led_state) {
    bool left_state = led_state.caps_lock;
    bool right_state = layer_state_is(_KP) ? led_state.num_lock : led_state.scroll_lock;
    writePin(LED_LEFT_PIN, left_state ? LED_PIN_ON_STATE : !LED_PIN_ON_STATE);
    writePin(LED_RIGHT_PIN, right_state ? LED_PIN_ON_STATE : !LED_PIN_ON_STATE);
    return false;
}
