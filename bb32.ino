/* 
 * Simple 32 button game controller (button box)
 *
 * Key Matrix;
 *  Rows pin : A0,A1,A2,A3
 *  Cols pin : 5,6,7,8,9,10,11,12
 * 
 * Required Librarys; 
 *    Keypad    : https://playground.arduino.cc/Code/Keypad/
 *    Joystick  : https://github.com/MHeironimus/ArduinoJoystickLibrary
 * 
 * Developed & tested on ATmega32u4 compatible Arduino clone
 * 
 */

#include <Key.h>
#include <Keypad.h>
#include <Joystick.h>

#define ENABLE_PULLUPS

#define BUTTONS 32
#define KMROWS 4
#define KMCOLS 8

byte rowPins[KMROWS] = {18,19,20,21}; 
byte colPins[KMCOLS] = {5,6,7,8,9,10,11,12};

byte keyMatrix[KMROWS][KMCOLS] = {
  {0,1,2,3,4,5,6,7},
  {8,9,10,11,12,13,14,15},
  {16,17,18,19,20,21,22,23},
  {24,25,26,27,28,29,30,31},
};

Keypad bb32 = Keypad(makeKeymap(keyMatrix), rowPins, colPins, KMROWS, KMCOLS); 
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK, BUTTONS, 0, 
  false, false, false, false, false, false, 
  false, false, false, false, false);

void scanButtons(void)  {
  if (bb32.getKeys()) {
    for (int n=0; n<LIST_MAX; n++)  {
      if (bb32.key[n].stateChanged) {
        switch (bb32.key[n].kstate) {
          case HOLD:
            Joystick.setButton(bb32.key[n].kchar, 1);
            break;
          case IDLE:
            Joystick.setButton(bb32.key[n].kchar, 0);
            break;
        }
      }
    }
  }
}

void setup()  {
  Joystick.begin();
}

void loop() { 
  scanButtons();
}

/*
 * Right on, commander!
 * @=X
 */
