/****************************************************************************************************
 ************************** CONTROL DE PISCINA - Temperatura y Filtrado *****************************
 ********************* FACULTAD DE CIENCIAS EXACTAS, INGENIERÍA Y AGRIEMENSURA **********************
 ****************************************************************************************************
 ***************************************************************************WsS**********************
 *************************************************************************Copyright 2023*************
 ****************************************************************************************************
 * La documentación de este proyecto se acompaña en la carpeta raíz de mismo						*
 * Autor de la presente implementación: WALTER SEBASTIAN WAGNER               					    *
 * Correo Electrónico: wagner@fceia.unr.edu.ar                           						 	*
 * Fecha última modificación: 18/08/2023                                                            *
 *                                                                                                  *
 * Institución: UNIVERSIDAD NACIONAL DE ROSARIO                                                     *
 * Dependencia: Facultad de Ciencias Exactas, Ingeniería y Agrimensura   						    *
 * Escuela: Ingeniería Electrónica                                             						*
 * Departamento: Microelectrónica                                                            		*
 * Cátedra: Diseño de Sistemas Electrónicos                                               			*
 * 																									* 
 * Este código está protegido por los derechos de autor y copyright      							*
 * aplicables. Por favor, consulte el archivo ReadMe.txt que acompaña    							*
 * a este archivo para ver los términos de la licencia correspondiente.   							*
 ****************************************************************************************************/

/**
 * @file boardDSE.H
 * @brief Contains internal data definitions and declarations.
 */


#ifndef boardDSE_H_
#define boardDSE_H_

/*==================[Inclusions]=============================================*/
#include <Arduino.h>
#include <Keypad.h>
#include <Key.h>
#include <TimerOne.h>
#include <LiquidCrystal.h>
#include <MsTimer2.h>

/*==================[Defines]================================================*/

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

#define TEMPERATURE_SENSOR A0

/*==================[External Functions]======================================*/

/**
 * @brief Initializes the module.
 *
 * This function initializes the module by setting up necessary resources.
 */
    void boardDSE_init();

/*==================[End of file]============================================*/
#endif /* boardDSE_H_ */
/**
 * @}
 */

/*==================[File: boardDSE.h]=======================================*/