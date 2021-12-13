#include "macroKeypad.h"

/**
 * @brief Execute user defined macros
 *
 * @param k Macro identifier as per defined in
 *          'user defined macros' section of header.
 */
void executeUserMacro(int k)
{
  switch (k)
  {
  case M0:
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEYPAD_7);
    Keyboard.releaseAll();
    break;
  case M1:
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEYPAD_1);
    Keyboard.releaseAll();
    break;
  case M2:
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEYPAD_3);
    Keyboard.releaseAll();
    break;
  case M3:
  case M4:
    break;
  }
}

//holds current layer
char current_layer = 0;

//register signals
char signals[ROWS][COLS] = {
    {0x0, 0x1, 0x2, 0x3},
    {0x4, 0x5, 0x6, 0x7},
    {0x8, 0x9, 0xA, 0xB}};

//how many layers do you have
#define LAYERS_AMOUNT 4

//define layers here
/*

int layer0[ROWS * COLS] = {
    0, 1, 2, 3,
    4, 5, 6, 7,
    8, 9, 10, 11
};

Layout is:
|  3  |  7  |  11 |
|  2  |  6  |  10 |
|  1  |  5  |  9  |
|  0  |  4  |  8  |
*/
int layer0[ROWS * COLS] = {
    LAYER_DOWN, 0, M0, KEYPAD_7,
    KEYPAD_PERIOD, KEYPAD_0, M1, KEYPAD_1,
    LAYER_UP, 0, M2, KEYPAD_3};

int layer1[ROWS * COLS] = {
    LAYER_DOWN, 0, 0, KEY_F5,
    0, 0, 0, KEY_F6,
    LAYER_UP, 0, 0, 0};

int layer2[ROWS * COLS] = {
    LAYER_DOWN, 0, 0, 0,
    0, 0, 0, 0,
    LAYER_UP, 0, 0, 0};

int layer3[ROWS * COLS] = {
    LAYER_DOWN, 0, 0, 0,
    0, 0, 0, 0,
    LAYER_UP, 0, 0, 0};

//array of pointers to layers
int *layers[LAYERS_AMOUNT] = {layer0, layer1, layer2, layer3};

//uint8_t rowPins[ROWS] = {2, 3, 4};
uint8_t rowPins[ROWS] = {4, 3, 2};
uint8_t colPins[COLS] = {9, 8, 7, 6};

Keypad keypad = Keypad(makeKeymap(signals), rowPins, colPins, ROWS, COLS);

/**
 * @brief Updates the layer LED indicator.
 *
 */
void updateLEDIndicatior()
{
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  switch (current_layer)
  {
  case 0:
    digitalWrite(A0, HIGH);
    break;
  case 1:
    digitalWrite(A1, HIGH);
    break;
  case 2:
    digitalWrite(A2, HIGH);
    break;
  case 3:
    digitalWrite(A3, HIGH);
    break;
  }
}

/**
 * @brief Main keystroke event for the keypad.
 *        Here every keystroke is handled
 *
 * @param key Key passed by the Keypad
 */
void keypadEvent(KeypadEvent key)
{
  switch (keypad.getState())
  {
  case PRESSED:
    if (layers[current_layer][key] == NO_ACTION)
    {
      //nothing
    }
    else if (layers[current_layer][key] == LAYER_DOWN)
    {
      //implement switching to layers down
      current_layer = current_layer - 1;
      if (current_layer < 0)
      {
        current_layer = LAYERS_AMOUNT - 1;
      }
      updateLEDIndicatior();
    }
    else if (layers[current_layer][key] == LAYER_UP)
    {
      //implement switching to layers up
      current_layer = current_layer + 1;
      if (current_layer > LAYERS_AMOUNT - 1)
      {
        current_layer = 0;
      }
      updateLEDIndicatior();
    }
    //user defined macros are above 512, which is M0
    else if (layers[current_layer][key] >= M0)
    {
      //execute the macro if available
      executeUserMacro(layers[current_layer][key]);
    }
    else
    {
      //otherwise press the key
      Keyboard.press((char)layers[current_layer][key]);
    }
    break;
  case RELEASED:
    if ((layers[current_layer][key] != NO_ACTION) || (layers[current_layer][key] == LAYER_DOWN) || (layers[current_layer][key] == LAYER_UP))
    {
      //release the key
      Keyboard.release((char)layers[current_layer][key]);
    }
    break;
  case IDLE:
  case HOLD:
    //donno, haven't had a use of it
    break;
  }
}

/**
 * @brief Arduino setup
 *
 */
void setup()
{
  Keyboard.begin();

  //disable the annoying TX and RX LEDs, which light up every stroke sent
  pinMode(LED_BUILTIN_TX, INPUT);
  pinMode(LED_BUILTIN_RX, INPUT);

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  //since we have 4 bools, we can represent 2**4 = 16 combinations
  //no need for that though, we'll use "only" 4 layers

  //we need to press the Numlock key in order for the Numpad keys to work
  Keyboard.press(219);
  delay(10);
  Keyboard.releaseAll();

  //update the layer indicator
  updateLEDIndicatior();

  //add the keystroke listener
  keypad.addEventListener(keypadEvent);
}

/**
 * @brief Arduino main loop
 *
 */
void loop()
{
  //has to be here, otherwise can't get the state
  char key = keypad.getKey();
}
