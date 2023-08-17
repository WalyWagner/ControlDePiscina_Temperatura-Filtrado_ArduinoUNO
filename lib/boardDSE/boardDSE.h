#ifndef boardDSE_H_
#define boardDSE_H_

/*==================[inclusions]=============================================*/
#include <Arduino.h>
#include <Keypad.h>
#include <Key.h>
#include <TimerOne.h>
#include <LiquidCrystal.h>
#include <MsTimer2.h>

#define LCD_RS A3
#define LCD_EN 9
#define LCD_D4 10
#define LCD_D5 11
#define LCD_D6 12
#define LCD_D7 13

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 3

#define HEATING_PORT A5
#define FILTERING_PORT A4

#define LCD_ROWS 16
#define LCD_COLS 2

/*==================[external functions definition]==========================*/
void boardDSE_init();

/*==================[end of file]============================================*/
#endif /* boardDSE_H_ */