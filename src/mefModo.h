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
 * 																									*                                               *
 * Este código está protegido por los derechos de autor y copyright      							*
 * aplicables. Por favor, consulte el archivo ReadMe.txt que acompaña    							*
 * a este archivo para ver los términos de la licencia correspondiente.   							*
 ****************************************************************************************************/

#ifndef MEF_MODO_H_
#define MEF_MODO_H_

/**
 * @file mefModo.h
 * @brief Contains internal data definitions and declarations.
 */

/*==================[Inclusions]=============================================*/
#include <Arduino.h>
#include <Keypad.h>
#include <Key.h>
#include <TimerOne.h>
#include <LiquidCrystal.h>
#include <MsTimer2.h>
#include <boardDSE.h> // DEBERÍA QUEDAR SOLO ESTA EN EL IDEAL QUE APLICACIÓN NO INTERACTÚA DIRECTAMENTE CON DRIVERS


/*==================[Typedefs]================================================*/
/**
 * @brief Defines Finite State Machine.
 */
typedef enum {
	EST_INIT_CFG = 0,
	EST_FILTERING,
    EST_WAITING,
} estMefModo_enum;

/*==================[external functions definition]==========================*/
/**
 * @brief Initializes the MEF
 */
void mefModo_init();

/**
 * @brief Run the MEF
 */
void mefModo();


/*==================[End of file]============================================*/
#endif /* MEF_MODO_H_ */
/**
 * @}
 */

/*==================[File: mefModo.h]=======================================*/