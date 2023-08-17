#include<boardDSE.h>

void boardDSE_init(void){
  pinMode(HEATING_PORT,OUTPUT);
  pinMode(FILTERING_PORT,OUTPUT);
  extern LiquidCrystal lcd;
  lcd.begin(LCD_ROWS, LCD_COLS);
}