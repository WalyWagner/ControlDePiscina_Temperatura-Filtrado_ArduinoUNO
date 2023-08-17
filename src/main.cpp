#include <Keypad.h>
#include <Key.h>
#include <mefModo.h>
#include <boardDSE.h>
#include <Arduino.h>
#include <LiquidCrystal.h>

char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
    };
byte rowPins[KEYPAD_ROWS] = {5, 4, 3, 2};
byte colPins[KEYPAD_COLS] = {8, 7, 6};

Keypad keypad = Keypad( makeKeymap(keys), rowPins , colPins , KEYPAD_ROWS, KEYPAD_COLS );
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);


void setup(){
    boardDSE_init();
    mefModo_init();
}

void loop(){
    mefModo();
}

