#include <Keypad.h>
#include <Key.h>
#include <TimerOne.h>
#include <mefModo.h>
#include <boardDSE.h>
#include <Arduino.h>

// include the library code:
#include <LiquidCrystal.h>


const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = A3, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){
  pinMode(A5,OUTPUT);
  pinMode(A4,OUTPUT);
  
  lcd.begin(16, 2);
 // Serial.begin(9600);
  mefModo_init();
}

void loop(){
  mefModo();
}

