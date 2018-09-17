#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define DELAY_TIME  75
static uint16_t key_timer;
static uint16_t tap_timer;
static uint16_t delay_registered_code;
static uint8_t delay_mat_row;
static uint8_t delay_mat_col;
static bool delay_key_stat;
static bool delay_key_pressed;
static bool tapping_key;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _OPT 1
#define _FUNC 2
#define _SYM 3
#define _NUM 4
#define _QWERTY 4
#define _LOWER  5
#define _RAISE  6
#define _ADJUST  7

bool RGBAnimation = false; //Flag for LED Layer color Refresh.

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  EISU,
  KANA,
  RGBRST,
  RGBOFF,
  RGB1,
  RGB2,
  RGB3,
  OPT_TAP_SP,
  DESKTOP,
  MAC,
  WIN,
  LOWER,
  RAISE,
  ADJUST,
  FROGGY
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

#if HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  C+z |   ;  |   [  |   (  |   <  |   {  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | KANA |   P  |   K  |   R  |   A  |   F  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  BS  |   D  |   T  |   H  |   E  |   O  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Y  |   S  |   N  |   I  |   U  |Space |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | Alt  | Gui  | Sym  | Num  | OPT  | Ent  |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_BASE] = LAYOUT( \
      LCTL(KC_Z),    KC_SCLN,       KC_LBRC,       KC_LPRN,   KC_LT,     KC_LCBR,                                _______,  _______,  _______,  _______,  _______,  _______, \
      KANA,          KC_P,          KC_K,          KC_R,      KC_A,      KC_F,                                   _______,  _______,  _______,  _______,  _______,  _______, \
      KC_BSPC,       KC_D,          KC_T,          KC_H,      KC_E,      KC_O,                                   _______,  _______,  _______,  _______,  _______,  _______, \
      OSM(MOD_LSFT), KC_Y,          KC_S,          KC_N,      KC_I,      KC_U,       KC_SPC, _______,  _______,  _______,  _______,  _______,  _______,  _______, \
      OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), MO(_SYM),  MO(_NUM),  OPT_TAP_SP, KC_ENT, _______,  _______,  _______,  _______,  _______,  _______,  _______ \
      ),

  /* Opt
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  Esc |  :   |  ]   |  )   |  >   |  }   |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  EISU|   J  |   M  |   B  |   '  |  Tab |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   .  |   V  |   C  |   L  |   Z  |  Q   |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |   X  |   G  |   W  |   -  |  Del | Esc  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |   ,  | DTOP |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_OPT] = LAYOUT( \
      KC_ESC,  KC_COLN,KC_RBRC, KC_RPRN,KC_GT,     KC_RCBR,                   _______,  _______,  _______,  _______,  _______,  _______, \
      EISU,    KC_J,   KC_M,    KC_B,   KC_QUOT,   KC_TAB,                    _______,  _______,  _______,  _______,  _______,  _______, \
      KC_DOT,  KC_V,   KC_C,    KC_L,   KC_Z,      KC_Q,                      _______,  _______,  _______,  _______,  _______,  _______, \
      _______, KC_X,   KC_G,    KC_W,   KC_MINUS,  KC_DEL,  KC_ESC,  _______, _______,  _______,  _______,  _______,  _______,  _______, \
      _______, _______,_______, KC_COMM,DESKTOP,   _______, _______, _______, _______,  _______,  _______,  _______,  _______,  _______ \
      ),

  /* Func
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |RGBRST|  Hue |      |  RST |  Mac |  Win |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | RGB1 | VAL+ |  F7  |  F8  |  F9  |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | RGB2 | VAL- |  F4  |  F5  |  F6  | F12  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | RGB3 |  F10 |  F1  |  F2  |  F3  | F11  |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |RGBOFF|      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_FUNC] = LAYOUT( \
      RGBRST,RGB_HUI, _______, RESET,   MAC,     WIN,                         _______,  _______,  _______,  _______,  _______,  _______, \
      RGB1,  RGB_VAI, KC_F7,   KC_F8,   KC_F9,   _______,                     _______,  _______,  _______,  _______,  _______,  _______, \
      RGB2,  RGB_VAD, KC_F4,   KC_F5,   KC_F6,   KC_F12,                      _______,  _______,  _______,  _______,  _______,  _______, \
      RGB3,  KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_F11,   _______,  _______, _______,  _______,  _______,  _______,  _______,  _______, \
      RGBOFF,QWERTY, _______, _______, _______, _______,  _______,  _______, _______,  _______,  _______,  _______,  _______,  _______ \
      ),

  /* Sym
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  Ins |  GRV |      |  PU  |  PD  |   ^  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   \  |   #  |   =  |   ?  |   %  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   $  |  upA |   @  |   !  |   |  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |  CL  |  <-  |  dwA |  ->  |   _  |   &  |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |  PS  |      |   ~  |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_SYM] = LAYOUT( \
      KC_INS,  KC_GRV,  _______, KC_PGUP, KC_PGDN, KC_CIRC,                   _______,  _______,  _______,  _______,  _______,  _______, \
      _______, KC_BSLS, KC_HASH, KC_EQL,  KC_QUES, KC_PERC,                   _______,  _______,  _______,  _______,  _______,  _______, \
      _______, KC_DLR,  KC_UP,   KC_AT,   KC_EXLM, KC_PIPE,                   _______,  _______,  _______,  _______,  _______,  _______, \
      KC_CAPS, KC_LEFT, KC_DOWN, KC_RIGHT,KC_UNDS, KC_AMPR, _______, _______, _______,  _______,  _______,  _______,  _______,  _______, \
      _______, _______, KC_PSCR, _______, KC_TILD, _______, _______, _______, _______,  _______,  _______,  _______,  _______,  _______ \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      | Func | home |  End |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   *  |  7   |  8   |  9   |  -   |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  .   |   /  |  4   |  5   |  6   |  +   |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |  LN  |  0   |  1   |  2   |  3   |C+S+F1|      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |  ,   |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_NUM] = LAYOUT( \
      _______,  _______, OSL(_FUNC), KC_HOME, KC_END,  _______,                          _______,  _______,  _______,  _______,  _______,  _______, \
      _______,  KC_ASTR, KC_7,       KC_8,    KC_9,   KC_MINS,                          _______,  _______,  _______,  _______,  _______,  _______, \
      KC_PDOT,  KC_SLSH, KC_4,       KC_5,    KC_6,   KC_PLUS,                          _______,  _______,  _______,  _______,  _______,  _______, \
      KC_NLCK,  KC_0,    KC_1,       KC_2,    KC_3,   LCTL(S(KC_F1)), _______, _______, _______,  _______,  _______,  _______,  _______,  _______, \
      _______,  _______, KC_PDOT,    KC_COMM, _______, _______,        _______, _______, _______,  _______,  _______,  _______,  _______,  _______ \
      ),

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   [  |   ]  |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Adjust| Esc  | Alt  | GUI  | EISU |Lower |Space |Space |Raise | KANA | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
      FROGGY,  KC_ESC,  KC_LALT, KC_LGUI, EISU,    LOWER,   KC_SPC,  KC_SPC,  RAISE,   KANA,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
      ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   _  |   +  |   {  |   }  |  |   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  (   |   )  |  F12 |      |      | Home | End  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
      _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_LPRN, KC_RPRN, KC_F12,  _______, _______, KC_HOME, KC_END,  _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   -  |   =  |   [  |   ]  |  \   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |  F7  |  F8  |  F9  |  F10 |  F11 |      |      |  F12 |      |      |PageDn|PageUp|      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
      _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______, _______, KC_F12,  _______, _______, KC_PGDN, KC_PGUP, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      )
};
#else
#error "undefined keymaps"
#endif


#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool find_mairix(uint16_t keycode, uint8_t *row, uint8_t *col){
  for(uint8_t i=0; i<MATRIX_ROWS; i++){
    for(uint8_t j=0; j<MATRIX_COLS; j++){
      if( pgm_read_word(&(keymaps[_BASE][i][j]))==keycode){
        *row = i;
        *col = j;
        return true;
      }
    }
  }
  return false;
}

void unregister_delay_code(void){
  if(delay_registered_code){
    unregister_code(delay_registered_code);
    if (delay_registered_code & QK_LSFT){
      unregister_code(KC_LSFT);
    }
    if (delay_registered_code & QK_LCTL){
      unregister_code(KC_LCTL);
    }
    if (delay_registered_code & QK_LALT){
      unregister_code(KC_LALT);
    }
    if (delay_registered_code & QK_LGUI){
      unregister_code(KC_LGUI);
    }
    delay_registered_code=0;
  }
}

void register_delay_code(uint8_t layer){
  if(delay_key_stat){
    unregister_delay_code();

    uint16_t code = pgm_read_word(&(keymaps[layer][delay_mat_row][delay_mat_col]));
    if (code & QK_LSFT){
      register_code(KC_LSFT);
    }
    if (code & QK_LCTL){
      register_code(KC_LCTL);
    }
    if (code & QK_LALT){
      register_code(KC_LALT);
    }
    if (code & QK_LGUI){
      register_code(KC_LGUI);
    }
    register_code(code);
    delay_registered_code = code;
    delay_key_stat = false;
    tapping_key = true;
  }
}

#ifdef RGBLIGHT_ENABLE
struct keybuf {
  char col, row;
  char frame;
};
struct keybuf keybufs[256];
unsigned char keybuf_begin, keybuf_end;

int col, row;
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  #ifdef RGBLIGHT_ENABLE
    col = record->event.key.col;
    row = record->event.key.row;
    if (record->event.pressed && ((row < 5 && is_master) || (row >= 5 && !is_master))) {
      int end = keybuf_end;
      keybufs[end].col = col;
      keybufs[end].row = row % 5;
      keybufs[end].frame = 0;
      keybuf_end ++;
    }
  #endif

  if(tap_timer&&keycode!=OPT_TAP_SP){
    tapping_key = true;
  }

  if(keycode==delay_registered_code){
      if (!record->event.pressed){
        unregister_delay_code();
      }
  }

  switch (keycode) {
    case KC_SCLN:
    case KC_LBRC:
    case KC_LPRN:
    case KC_LT:
    case KC_LCBR:
    case KC_P:
    case KC_K:
    case KC_R:
    case KC_A:
    case KC_F:
    case KC_BSPC:
    case KC_D:
    case KC_T:
    case KC_H:
    case KC_E:
    case KC_O:
    case KC_Y:
    case KC_S:
    case KC_N:
    case KC_I:
    case KC_U:
    case LCTL(KC_Z):
    case KC_SPC:
      if (record->event.pressed) {
        register_delay_code(_BASE);
        if(find_mairix(keycode, &delay_mat_row, &delay_mat_col)){
          key_timer = timer_read();
          delay_key_stat = true;
          delay_key_pressed = true;
        }
      }else{
        delay_key_pressed = false;
      }
      return false;
      break;
    case OPT_TAP_SP:
      if (record->event.pressed) {
        tapping_key = false;
        register_delay_code(_OPT);
        layer_on(_OPT);
        tap_timer = timer_read();
      }else{
        layer_off(_OPT);
        if(tapping_key==false && timer_elapsed(tap_timer) < TAPPING_TERM){
          SEND_STRING(" ");
        }
        tap_timer = 0;
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
    case DESKTOP:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_F11);
        }else{
          SEND_STRING(SS_LGUI("d"));
        }
      } else {
        unregister_code(KC_F11);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
          RGBAnimation = false;
        }
      #endif
      break;
    case RGBOFF:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_disable();
        }
      #endif
      break;
    case RGB1:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          RGBAnimation = true;
          rgblight_mode(6);
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case RGB2:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          RGBAnimation = true;
          rgblight_mode(10);
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case RGB3:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          RGBAnimation = true;
          rgblight_mode(21);
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case MAC:
      if (record->event.pressed) {
        keymap_config.swap_lalt_lgui = false;
        keymap_config.swap_ralt_rgui = false;
        #ifdef AUDIO_ENABLE
          PLAY_SONG(ag_norm_song);
        #endif
      }
      break;
    case WIN:
      if (record->event.pressed) {
        keymap_config.swap_lalt_lgui = true;
        keymap_config.swap_ralt_rgui = true;
        #ifdef AUDIO_ENABLE
          PLAY_SONG(ag_swap_song);
        #endif
      }
      break;
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case FROGGY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_BASE);
      }
      return false;
      break;
/*
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
*/
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    }
  return true;
}


//keyboard start-up code. Runs once when the firmware starts up.
void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_OPT 2
#define L_FUNC 4
#define L_SYM 8
#define L_NUM 16
#define L_FNLAYER 64
#define L_NUMLAY 128
#define L_NLOWER 136
#define L_NFNLAYER 192
#define L_MOUSECURSOR 256

// LED Effect
#ifdef RGBLIGHT_ENABLE
unsigned char rgb[7][5][3];
void led_ripple_effect(char r, char g, char b) {
    static int scan_count = -10;
    static int keys[] = { 6, 6, 6, 7, 7 };
    static int keys_sum[] = { 0, 6, 12, 18, 25 };

    if (scan_count == -1) {
      rgblight_enable_noeeprom();
      rgblight_mode(0);
    } else if (scan_count >= 0 && scan_count < 5) {
      for (unsigned char c=keybuf_begin; c!=keybuf_end; c++) {
        int i = c;
        // FIXME:

        int y = scan_count;
        int dist_y = abs(y - keybufs[i].row);
        for (int x=0; x<keys[y]; x++) {
          int dist = abs(x - keybufs[i].col) + dist_y;
          if (dist <= keybufs[i].frame) {
            int elevation = MAX(0, (8 + dist - keybufs[i].frame)) << 2;
            if (elevation) {
              if ((rgb[x][y][0] != 255) && r) { rgb[x][y][0] = MIN(255, elevation + rgb[x][y][0]); }
              if ((rgb[x][y][1] != 255) && g) { rgb[x][y][1] = MIN(255, elevation + rgb[x][y][1]); }
              if ((rgb[x][y][2] != 255) && b) { rgb[x][y][2] = MIN(255, elevation + rgb[x][y][2]); }
            }
          }
        }
      }
    } else if (scan_count == 5) {
      for (unsigned char c=keybuf_begin; c!=keybuf_end; c++) {
        int i = c;
        if (keybufs[i].frame < 18) {
          keybufs[i].frame ++;
        } else {
          keybuf_begin ++;
        }
      }
    } else if (scan_count >= 6 && scan_count <= 10) {
      int y = scan_count - 6;
      for (int x=0; x<keys[y]; x++) {
        int at = keys_sum[y] + ((y & 1) ? x : (keys[y] - x - 1));
        led[at].r = rgb[x][y][0];
        led[at].g = rgb[x][y][1];
        led[at].b = rgb[x][y][2];
      }
      rgblight_set();
    } else if (scan_count == 11) {
      memset(rgb, 0, sizeof(rgb));
    }
    scan_count++;
    if (scan_count >= 12) { scan_count = 0; }
}
#endif

uint8_t layer_state_old;

//runs every scan cycle (a lot)
void matrix_scan_user(void) {
  #ifdef SSD1306OLED
    iota_gfx_task();  // this is what updates the display continuously
  #endif

  if(delay_key_stat && (timer_elapsed(key_timer) > DELAY_TIME)){
    register_delay_code(_BASE);
    if(!delay_key_pressed){
      unregister_delay_code();
    }
  }

  if(layer_state_old != layer_state){
    switch (layer_state) {
      case L_BASE:
        break;
      case L_OPT:
        register_delay_code(_OPT);
        break;
      case L_NUM:
        register_delay_code(_NUM);
        break;
      case L_SYM:
        register_delay_code(_SYM);
        break;
      case L_FUNC:
        register_delay_code(_FUNC);
        break;
    }
    layer_state_old = layer_state;
  }

  #ifdef RGBLIGHT_ENABLE
    if(!RGBAnimation){
      switch (layer_state) {
        case L_BASE:
          led_ripple_effect(0,112,127);
          break;
        case L_OPT:
          led_ripple_effect(127,0,100);
          break;
        case L_NUM:
          led_ripple_effect(127,23,0);
          break;
        case L_SYM:
          led_ripple_effect(0,127,0);
          break;
        case L_FUNC:
          led_ripple_effect(127,0,61);
          break;
        }
    }
  #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

// Render to OLED
void render_status(struct CharacterMatrix *matrix) {

  // froggy logo
  static char logo[4][1][17]=
  {
    {
      {0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0}
    },
    {
      {0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,0}
    },
    {
      {0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,0}
    },
    {
      {0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0}
    }
  };

  static char indctr[8][2][4]=
  {
    // white icon
    {
      {0x60,0x61,0x62,0},
      {0x63,0x64,0}
    },
    {
      {0x80,0x81,0x82,0},
      {0x83,0x84,0}
    },
    {
      {0xa0,0xa1,0xa2,0},
      {0xa3,0xa4,0}
    },
    {
      {0xc0,0xc1,0xc2,0},
      {0xc3,0xc4,0}
    },
    // Black icon
    {
      {0x75,0x76,0x77,0},
      {0x78,0x79,0}
    },
    {
      {0x95,0x96,0x97,0},
      {0x98,0x99,0}
    },
    {
      {0xb5,0xb6,0xb7,0},
      {0xb8,0xb9,0}
    },
    {
      {0xd5,0xd6,0xd7,0},
      {0xd8,0xd9,0}
    },
  };

  int rown = 0;
  int rowf = 0;
  int rowa = 0;
  int rows = 0;

  //Set Indicator icon
  if (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) { rown = 4; } else { rown = 0; }
  if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) { rowa = 4; } else { rowa = 0; }
  if (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) { rows = 4; } else { rows = 0; }
  if (layer_state == L_FUNC) { rowf = 4; }

  matrix_write(matrix, indctr[rown]  [0]);
  matrix_write(matrix, indctr[rowf]  [1]);
  matrix_write(matrix, logo  [0]     [0]);
  matrix_write(matrix, indctr[rown+1][0]);
  matrix_write(matrix, indctr[rowf+1][1]);
  matrix_write(matrix, logo  [1]     [0]);
  matrix_write(matrix, indctr[rowa+2][0]);
  matrix_write(matrix, indctr[rows+2][1]);
  matrix_write(matrix, logo  [2]     [0]);
  matrix_write(matrix, indctr[rowa+3][0]);
  matrix_write(matrix, indctr[rows+3][1]);
  matrix_write(matrix, logo  [3]     [0]);

}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
