#ifndef MEF_MODO_H_
#define MEF_MODO_H_

/*==================[inclusions]=============================================*/
#include <Arduino.h>
#include <Keypad.h>
#include <Key.h>
#include <TimerOne.h>
#include <LiquidCrystal.h>
#include <MsTimer2.h>


/*==================[typedef]================================================*/
typedef enum {
	EST_INIT_CFG = 0,
	EST_FILTERING,
    EST_WAITING,
} estMefModo_enum;

/*==================[external functions definition]==========================*/
void mefModo_init();
void mefModo();
//void mefModo_task1ms();


/*==================[end of file]============================================*/
#endif /* MEF_MODO_H_ */