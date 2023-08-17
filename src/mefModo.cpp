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
 * @file mefModo.cpp
 * @brief This is the aplication layer of the implamantation.
 * Must be upgraded!
 */

/*==================[Inclusions]=============================================*/
#include <mefModo.h>

/*==================[External Data Definitions]==============================*/
extern Keypad keypad;
extern LiquidCrystal lcd;

/*==================[Internal Data Definitions]==============================*/
static bool filtering =  false; // ->Flag to indicate the actual state
static bool waiting = false;	// ->Flag to indicate the actual state
static bool wantToControlTemp; // ->Flag to indicate if the temperature control is ON
static int hoursToFilter, hoursToSleep, temperatureToHeat; 	// -> Timers & temperature

/*==================[Internal Data Declarations]=============================*/
static estMefModo_enum est_MefModo;

/*==================[internal function declaration]==========================*/
/**
 * @brief this function is attached to TIMER 1 interruption rutine 
 *
 * You to change from filtering mode to sleep mode when the work is done!
 */static void filteringTimer(void);

/**
 * @brief this function is attached to TIMER 2 interruption rutine 
 *
 * You want to measure temperature periodically 
 */static void temperatureTimer(void);

/*==================[external functions definition]==========================*/

/**
 * @brief Initializes the MEF
 */
void mefModo_init() {
	est_MefModo = EST_INIT_CFG;
}

/**
 * @brief Run the MEF
 */
void mefModo() {
	switch (est_MefModo) {
		case EST_INIT_CFG:

			/*FALTA MEJORAR QUE LA CAPA DE APLICACIÓN NO OPERE DIRECTAMENTE EL HARDWARE !!
			* ES DECIR, HABRÍA QUE HACER EN boardDSE.cpp SUBRUTINAS QUE OPEREN EL DISPLAY,
			* EL TECLADO, ETC Y QUE SEAN CONVOCADAS DESDE AQUÍ */

			lcd.setCursor(0, 0); 	lcd.print("INGRESE LAS HS.");
			lcd.setCursor(0, 1);	lcd.print("ENTRE CICLOS DE");
			delay(2000);			lcd.clear();
			lcd.setCursor(0, 0); 	lcd.print("FILTRADO EN 2 ");
			lcd.setCursor(0, 1);	lcd.print("DIGITOS (1-24)");
			hoursToSleep = keypad.waitForKey() - 48;  		// Ingresa la decena y se castea a int
			hoursToSleep = hoursToSleep * 10 + keypad.waitForKey() - 48;  // Ingresa la unidad y se castea a int acumulando la decena
			lcd.clear(); lcd.print(hoursToSleep); delay(1000); lcd.clear();
			
			lcd.setCursor(0, 0); 	lcd.print("INGRESE LAS HS.");
			lcd.setCursor(0, 1);	lcd.print("DE DURACION DE");
			delay(2000);			lcd.clear();
			lcd.setCursor(0, 0); 	lcd.print("CADA CICLO EN 2");
			lcd.setCursor(0, 1);	lcd.print("DIGITOS (1-24)");
			hoursToFilter = keypad.waitForKey() - 48;  	// Ingresa la decena y se castea a int
			hoursToFilter = hoursToFilter * 10 + keypad.waitForKey() - 48;	// Ingresa la unidad y se castea a int acumulando la decena
			lcd.clear(); lcd.print(hoursToFilter); delay(1000); lcd.clear();

			lcd.setCursor(0, 0); 	lcd.print("DESEA ACTIVAR EL");
			lcd.setCursor(0, 1);	lcd.print("CONTROL DE TEMP?");
			delay(2000);			lcd.clear();
			lcd.setCursor(0, 0); 	lcd.print("INGRESE UN '1'");
			lcd.setCursor(0, 1);	lcd.print("EN CASO DE SI !");
			if ((keypad.waitForKey()-48) == 1){
				wantToControlTemp=true;
				lcd.setCursor(0, 0); 	lcd.print("INGRESE LA TEMP");
				lcd.setCursor(0, 1);	lcd.print("DESEADA EN GRADOS");
				delay(2000);			lcd.clear();
				lcd.setCursor(0, 0); 	lcd.print("HAGALO EN 2 ");
				lcd.setCursor(0, 1);	lcd.print("DIGITOS ");
				//Serial.println("INGRESE A LA TEMPERATURA QUE DESEA MANTENER EL AGUA");
				//Serial.println("HÁGALO EN FORMATO DE 2 DÍGITOS (1-60)");	
				temperatureToHeat = keypad.waitForKey() - 48;  						// Ingresa la decena y se castea a int
				temperatureToHeat = temperatureToHeat * 10 + keypad.waitForKey() - 48;		// Ingresa la unidad y se castea a int acumulando la decena
				//Serial.print("Grados:");
				//Serial.println(temperatureToHeat);
				MsTimer2::set(1000,temperatureTimer);
				MsTimer2::start();
				lcd.clear(); lcd.print(temperatureToHeat); delay(1000); lcd.clear();
			}

			Timer1.initialize(1000000 * hoursToFilter);      //Configura el TIMER en hoursToFilter Segundos
   			Timer1.attachInterrupt(filteringTimer) ; //Configura la interrupción del Timer 1

			filtering = true;

			lcd.clear(); lcd.print("FILTRO:  ON");

			digitalWrite(FILTERING_PORT,HIGH);

			est_MefModo = EST_FILTERING;

			break;

		case EST_FILTERING:
			if(waiting){
				est_MefModo = EST_WAITING;
				lcd.setCursor(0, 0); 	lcd.print("FILTRO: OFF");
				digitalWrite(A4,LOW);
			}

			break;

        case EST_WAITING:
			if(!waiting && filtering){
				est_MefModo = EST_FILTERING;
				lcd.setCursor(0, 0);	lcd.print("FILTRO:  ON");
				digitalWrite(A4,HIGH);
			}
			break;
	}
}


/*==================[internal function definition]==========================*/

void filteringTimer(void){
	if (filtering==true && waiting == false) // we have interrupted because filtering routine is done
	{
		filtering = false ; 
		waiting = true;
		Timer1.stop();
		Timer1.initialize(1000000 * hoursToSleep);      //Configura el TIMER en hoursToFilter Segundos
		Timer1.attachInterrupt(filteringTimer) ; //Configura la interrupción del Timer 1
		return;
	}
	if (filtering==false && waiting == true) // we have interrupted because filtering routine is done
	{
		filtering = true ; 
		waiting = false;
		Timer1.stop();
		Timer1.initialize(1000000 * hoursToFilter);      //Configura el TIMER en hoursToFilter Segundos
		Timer1.attachInterrupt(filteringTimer) ; //Configura la interrupción del Timer 1
		return;
	}
}
void temperatureTimer(void){ // CON HISTÉRESIS DE 5 GRADOS !!
	float tempC = analogRead(TEMPERATURE_SENSOR);
	tempC = (5.0 * tempC * 100.0)/1024.0;
	lcd.setCursor(0, 1); 	lcd.print("Temp: ");
	lcd.setCursor(6, 1); 	lcd.print(tempC);
	lcd.setCursor(12, 1); 	lcd.print("gC");


	if (tempC < temperatureToHeat - 5){
		  digitalWrite(HEATING_PORT,HIGH);
	}else{
		if (tempC > temperatureToHeat + 5){
			digitalWrite(HEATING_PORT, LOW);
		}
	}

}
/*==================[End of file]============================================*/
/**
 * @}
 */

/*==================[File: mefModo.cpp]=======================================*/