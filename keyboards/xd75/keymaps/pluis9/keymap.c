/* Copyright 2017 Wunder
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "xd75.h"

// Layer shorthand
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _EUCALYN 3
#define _LOWER 4
#define _RAISE 5
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  EUCALYN,
  LOWER,
  RAISE,
  EISU,
  KANA
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | 7      | 8      | 9      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | 4      | 5      | 6      | Y      | U      | I      | O      | P      | |      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | LCTRL  | A      | S      | D      | F      | G      | 1      | 2      | 3      | H      | J      | K      | L      | ;      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | [      | 0      | ]      | N      | M      | ,      | .      | /      | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | ADJUST | `      | LALT   | GUI    | EISU   | LOWER  | ENTER  | .      | SPACE  | RAISE  | KANA   | LEFT   | DOWN   | UP     | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_QWERTY] = {
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_KP_7, KC_KP_8, KC_KP_9, KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC },
  { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_KP_4, KC_KP_5, KC_KP_6, KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_BSLS },
  { KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_KP_1, KC_KP_2, KC_KP_3, KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_ENT },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_KP_0, KC_RBRC, KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT },
  { MO(_ADJUST), KC_GRV, KC_LALT, KC_LGUI, EISU, LOWER,   KC_PENT, KC_PDOT, KC_SPC,  RAISE,  KANA,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT },
 },

 /* EUCALYN
  * .--------------------------------------------------------------------------------------------------------------------------------------.
  * | ESC    | 1      | 2      | 3      | 4      | 5      | 7      | 8      | 9      | 6      | 7      | 8      | 9      | 0      | BACKSP |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
  * | TAB    | /      | ,      | .      | F      | Q      | 4      | 5      | 6      | M      | R      | D      | Y      | P      | \      |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
  * | LCTRL  | A      | O      | E      | I      | U      | 1      | 2      | 3      | G      | T      | K      | S      | N      | ENTER  |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
  * | LSHIFT | Z      | X      | C      | V      | W      | [      | 0      | ]      | B      | H      | J      | L      | ;      | RSHIFT |
  * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
  * | ADJUST | `      | LALT   | GUI    | EISU   | LOWER  | ENTER  | .      | SPACE  | RAISE  | KANA   | LEFT   | DOWN   | UP     | RIGHT  |
  * '--------------------------------------------------------------------------------------------------------------------------------------'
  */

 [_EUCALYN] = {
   { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_KP_7, KC_KP_8, KC_KP_9, KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC },
   { KC_TAB,  KC_BSLS, KC_BSLS, KC_DOT,  KC_F,    KC_Q,    KC_KP_4, KC_KP_5, KC_KP_6, KC_M,   KC_R,   KC_D,    KC_Y,    KC_P,    KC_BSLS },
   { KC_LCTL, KC_A,    KC_O,    KC_E,    KC_I,    KC_U,    KC_KP_1, KC_KP_2, KC_KP_3, KC_G,   KC_T,   KC_K,    KC_S,    KC_N,    KC_ENT },
   { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_W,    KC_LBRC, KC_KP_0, KC_RBRC, KC_B,   KC_H,   KC_J,    KC_L,    KC_SCLN, KC_RSFT },
   { MO(_ADJUST), KC_GRV, KC_LALT, KC_LGUI, EISU, LOWER,   KC_PENT, KC_PDOT, KC_SPC,  RAISE,  KANA,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT },
  },

/* LOWER
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        | INSERT | HOME   | PGUP   |        |        |        |        |        | DELETE |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | BS     | 7      | 8      | 9      |        | DELETE | END    | PGDOWN |        |        | -      | =      | '      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        | 4      | 5      | 6      | -      | PRSCRN | NUMLOCK| SCLOCK |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | 0      | 1      | 2      | 3      | +      |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | .      |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_LOWER] = {
  { _______, _______, _______, _______, _______, _______, KC_INS,  KC_HOME, KC_PGUP, _______, _______, _______, _______, _______, KC_DEL },
  { _______, KC_BSPC, KC_KP_7, KC_KP_8, KC_KP_9, _______, KC_DEL,  KC_END,  KC_PGDN, _______, _______, KC_MINS, KC_EQL,  KC_QUOTE, _______ },
  { _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_PMNS, KC_PSCR, KC_NLCK, KC_SLCK, _______, _______, _______, _______, _______, _______ },
  { _______, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_PPLS, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  { _______, KC_PDOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
},

/* RAISE
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        | INSERT | HOME   | PGUP   |        |        |        |        |        | DELETE |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | !      | @      | #      | $      | %      | DELETE | END    | PGDOWN | ^      | &      | *      | (      | )      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | F1     | F2     | F3     | F4     | F5     | PRSCRN | NUMLOCK| SCLOCK | F6     |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | F7     | F8     | F9     | F10    | F11    |        |        |        | F12    |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        | NEXT   | VOL-   | VOL+   | PLAY   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_RAISE] = {
  { _______, _______, _______, _______, _______, _______, KC_INS,  KC_HOME, KC_PGUP, _______, _______, _______, _______, _______, KC_DEL },
  { _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_DEL,  KC_END,  KC_PGDN, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______ },
  { _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_PSCR, KC_NLCK, KC_SLCK, KC_F6,   _______, _______, _______, _______, _______ },
  { _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______, _______, _______, KC_F12,  _______, _______, _______, _______, _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
},

/* ADJUST
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        | DELETE |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | RESET  |        |        |        |        |        |        |        | QWERTY |EUCALYN |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        | Mac    |        |        |        | Win    |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        | RGB ON | HUE+   | SAT+   | VAL+   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        | MODE   | HUE-   | SAT-   | VAL-   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_ADJUST] = {
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL },
  { _______, RESET,   _______, _______, _______, _______, _______, _______, _______, QWERTY,  EUCALYN, _______, _______, _______, _______ },
  { _______, _______, _______, _______, _______, AG_NORM, _______, _______, _______, AG_SWAP, _______, _______, _______, _______, _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SMOD, RGB_HUD, RGB_SAD, RGB_VAD },
},

};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_DVORAK);
          }
          return false;
          break;
        case EUCALYN:
            if (record->event.pressed) {
              set_single_persistent_default_layer(_EUCALYN);
            }
            return false;
            break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case EISU:
          if (record->event.pressed) {
            if(keymap_config.swap_lalt_lgui==false){
              register_code(KC_LANG2);
            }else{
              SEND_STRING(SS_LALT("`"));
            }
          } else {
            unregister_code(KC_LANG2);
          }
          return false;
          break;
        case KANA:
          if (record->event.pressed) {
            if(keymap_config.swap_lalt_lgui==false){
              register_code(KC_LANG1);
            }else{
              SEND_STRING(SS_LALT("`"));
            }
          } else {
            unregister_code(KC_LANG1);
          }
          return false;
          break;
      }
    return true;
};

void matrix_scan_user(void) {
#ifdef RGBLIGHT_ENABLE
#ifdef PROTOCOL_LUFA
  switch (USB_DeviceState) {
    case DEVICE_STATE_Configured:
      rgblight_mode(rgblight_get_mode());
      break;
    case DEVICE_STATE_Unattached:
    case DEVICE_STATE_Suspended:
    case DEVICE_STATE_Powered:
    case DEVICE_STATE_Default:
    case DEVICE_STATE_Addressed:
      rgblight_effect_breathing(100);
      //rgblight_setrgb(0,0,0);
  }
#endif
#endif
}
