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
 * @file boardDSE.cpp
 * @brief Contains Middleware layer - connect the drivers whith the aplication
 * This LAYER must be upgraded !!
 */

/*==================[Inclusions]=============================================*/
#include <Keypad.h>
#include<boardDSE.h>

/*==================[External Functions]======================================*/
/**
 * @brief Initializes the hardware.
 */
void boardDSE_init(void){
  pinMode(HEATING_PORT,OUTPUT);
  pinMode(FILTERING_PORT,OUTPUT);
  extern LiquidCrystal lcd;
  lcd.begin(LCD_ROWS, LCD_COLS);
}
/*==================[End of file]============================================*/
/**
 * @}
 */

/*==================[File: main.cpp]=======================================*/