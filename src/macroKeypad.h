#include <Arduino.h>
#include <Keyboard.h>
#include <KeyboardLayout.h>
#include <Key.h>
#include <Keypad.h>

#define A3 21
#define A2 20
#define A1 19
#define A0 18

#define ROWS 3
#define COLS 4

#define KEYPAD_0 234
#define KEYPAD_1 225
#define KEYPAD_2 226
#define KEYPAD_3 227
#define KEYPAD_4 228
#define KEYPAD_5 229
#define KEYPAD_6 230
#define KEYPAD_7 231
#define KEYPAD_8 232
#define KEYPAD_9 233
#define KEYPAD_ASTERIX 221
#define KEYPAD_ENTER 224
#define KEYPAD_MINUS 222
#define KEYPAD_PERIOD 235
#define KEYPAD_PLUS 223
#define KEYPAD_SLASH 220
#define KEY_BACKSLASH 185
#define KEY_BACKSPACE 178
#define KEY_CAPS_LOCK 193
#define KEY_COMMA 190
#define KEY_DELETE 212
#define KEY_DOWN 217
#define KEY_END 213
#define KEY_ENTER 176
#define KEY_EQUAL 182
#define KEY_ESC 177

#define KEY_F1 194
#define KEY_F2 195
#define KEY_F3 196
#define KEY_F4 197
#define KEY_F5 198
#define KEY_F6 199
#define KEY_F7 200
#define KEY_F8 201
#define KEY_F9 202
#define KEY_F10 203
#define KEY_F11 204
#define KEY_F12 205
#define KEY_F13 240
#define KEY_F14 241
#define KEY_F15 242
#define KEY_F16 243
#define KEY_F17 244
#define KEY_F18 245
#define KEY_F19 246
#define KEY_F20 247
#define KEY_F21 248
#define KEY_F22 249
#define KEY_F23 250
#define KEY_F24 251

#define KEY_HOME 210
#define KEY_INSERT 209
#define KEY_LEFT 216
#define KEY_LEFT_BRACE 183
#define KEY_MENU 237
#define KEY_MINUS 181
#define KEY_NON_US_NUM 186
#define KEY_NUM_LOCK 219
#define KEY_PAGE_DOWN 214
#define KEY_PAGE_UP 211
#define KEY_PAUSE 208
#define KEY_PERIOD 191
#define KEY_PRINTSCREEN 206
#define KEY_QUOTE 188
#define KEY_RIGHT 215
#define KEY_RIGHT_BRACE 184
#define KEY_SCROLL_LOCK 207
#define KEY_SEMICOLON 187
#define KEY_SLASH 192
#define KEY_SPACE 180
#define KEY_TAB 179
#define KEY_TILDE 189
#define KEY_UP 218

//reserve op-codes
#define NO_ACTION 0
#define LAYER_UP 1
#define LAYER_DOWN 2

//user defined macros
#define M0 512
#define M1 513
#define M2 514
#define M3 515
#define M4 516

//declarations
void executeUserMacro(int k);
void updateLEDIndicator();
void keypadEvent(KeypadEvent key);
