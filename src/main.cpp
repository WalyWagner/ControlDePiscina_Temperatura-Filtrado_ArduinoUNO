/****************************************************************************************************
 ************************** CONTROL DE PISCINA - Temperatura y Filtrado *****************************
 ********************* FACULTAD DE CIENCIAS EXACTAS, INGENIERÍA Y AGRIEMENSURA **********************
 ****************************************************************************************************
 ***************************************************************************WsS**********************
 *************************************************************************Copyright 2023*************
 ****************************************************************************************************
 * La documentación de este proyecto se acompaña en la carpeta raíz de mismo						            *
 * Autor de la presente implementación: WALTER SEBASTIAN WAGNER               					          	*
 * Correo Electrónico: wagner@fceia.unr.edu.ar                           						 	              *
 * Fecha última modificación: 18/08/2023                                                            *
 *                                                                                                  *
 * Institución: UNIVERSIDAD NACIONAL DE ROSARIO                                                     *
 * Dependencia: Facultad de Ciencias Exactas, Ingeniería y Agrimensura   						                *
 * Escuela: Ingeniería Electrónica                                             						          *
 * Departamento: Microelectrónica                                                            				*
 * Cátedra: Diseño de Sistemas Electrónicos                                               					*
 * 																									                                                *
 * Este código está protegido por los derechos de autor y copyright      							              *
 * aplicables. Por favor, consulte el archivo ReadMe.txt que acompaña    							              *
 * a este archivo para ver los términos de la licencia correspondiente.   							            *
 ****************************************************************************************************/

/**
 * @file main.cpp
 * @brief Contains the main program to be uploaded to ARDUINO UNO.
 */

/*==================[Inclusions]=============================================*/
#include <Keypad.h>
#include <Key.h>
#include <mefModo.h>
#include <boardDSE.h>
#include <Arduino.h>
#include <LiquidCrystal.h>

/*==================[Internal Data Definitions]==============================*/
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
    };
byte rowPins[KEYPAD_ROWS] = {5, 4, 3, 2};
byte colPins[KEYPAD_COLS] = {8, 7, 6};

/*==================[Object Instantiations]===================================*/
Keypad keypad = Keypad( makeKeymap(keys), rowPins , colPins , KEYPAD_ROWS, KEYPAD_COLS );
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

/*==================[Setup configurations]===================================*/
/**
 * @brief We need to inicializate the hardware and the aplication
 */
void setup(){
    boardDSE_init();
    mefModo_init();
}

/*==================[Application Layer]=======================================*/
/**
 * @brief Here we are polling our MEF!
 */
void loop(){
    mefModo();
}

/*==================[End of file]============================================*/
/**
 * @}
 */

/*==================[File: main.cpp]=======================================*/