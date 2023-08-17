#include <mefModo.h>
extern Keypad keypad;
extern LiquidCrystal lcd;

static bool filtering =  false;
static bool waiting = false;
static bool wantToControlTemp; 
int hoursToFilter, hoursToSleep, temperatureToHeat; 

/*==================[internal data declaration]==========================*/
static estMefModo_enum est_MefModo;

/*==================[internal function definition]==========================*/
static void Temporizador(void);
static void temperatureTimer(void);


/*==================[external functions definition]==========================*/
void mefModo_init() {
	est_MefModo = EST_INIT_CFG;

}

void mefModo() {
	switch (est_MefModo) {
		case EST_INIT_CFG:

			lcd.setCursor(0, 0);
			lcd.print("HORAS ENTRE CICLOS");
			lcd.setCursor(0, 1);
			lcd.print("DE FILTRADO? 2 DIG");
			//Serial.println("INGRESE CADA CUANTAS HORAS DESEA REALIZAR UN CICLO DE FLITRADO");
            //Serial.println("HÁGALO EN FORMATO DE 2 DÍGITOS (1-48)");
			hoursToSleep = keypad.waitForKey() - 48;  						// Ingresa la decena y se castea a int
			hoursToSleep = hoursToSleep * 10 + keypad.waitForKey() - 48;		// Ingresa la unidad y se castea a int acumulando la decena
			//Serial.print("Horas:");
            //Serial.println(hoursToSleep);
			lcd.clear(); lcd.print(hoursToSleep); delay(1000); lcd.clear();
			
			lcd.setCursor(0, 0);
			lcd.print("HORAS POR CICLO?");
			lcd.setCursor(0, 1);
			lcd.print("DE FILTRADO? 2 DIG");
			//Serial.println("INGRESE CADA CUANTAS HORAS DESEA MANTENER ENCENDIDO EL FILTRO EN CADA CICLO");
            //Serial.println("HÁGALO EN FORMATO DE 2 DÍGITOS (1-48)");
			hoursToFilter = keypad.waitForKey() - 48;  						// Ingresa la decena y se castea a int
			hoursToFilter = hoursToFilter * 10 + keypad.waitForKey() - 48;		// Ingresa la unidad y se castea a int acumulando la decena
			//Serial.print("Horas:");
            //Serial.println(hoursToFilter);
			lcd.clear(); lcd.print(hoursToFilter); delay(1000); lcd.clear();

			lcd.setCursor(0, 0);
			lcd.print("ACTIVA CONTROL DE");
			lcd.setCursor(0, 1);
			lcd.print("TEMPERATURA? 1=SI");
			if ((keypad.waitForKey()-48) == 1){
				wantToControlTemp=true;
				lcd.setCursor(0, 0);
				lcd.print("TEMPERATURA DESEADA");
				lcd.setCursor(0, 1);
				lcd.print("EN GRADOS? 2 DIG");
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
   			Timer1.attachInterrupt(Temporizador) ; //Configura la interrupción del Timer 1

			filtering = true;
			//Serial.println("Im going to filter");
			lcd.clear(); lcd.print("FILTRANDO");
			digitalWrite(A4,HIGH);
			est_MefModo = EST_FILTERING;

			break;

		case EST_FILTERING:
			if(waiting){
				est_MefModo = EST_WAITING;
				//Serial.println("Im going to sleep");
				lcd.clear(); lcd.print("DURMIENDO");
				digitalWrite(A4,LOW);


			}

			break;

        case EST_WAITING:
			if(!waiting && filtering){
				est_MefModo = EST_FILTERING;
				lcd.clear(); lcd.print("FILTRANDO");
				digitalWrite(A4,HIGH);

			}


			break;
	}
}

void Temporizador(void){
	if (filtering==true && waiting == false) // we have interrupted because filtering routine is done
	{
		filtering = false ; 
		waiting = true;
		Timer1.stop();
		Timer1.initialize(1000000 * hoursToSleep);      //Configura el TIMER en hoursToFilter Segundos
		Timer1.attachInterrupt(Temporizador) ; //Configura la interrupción del Timer 1
		return;
	}
	if (filtering==false && waiting == true) // we have interrupted because filtering routine is done
	{
		filtering = true ; 
		waiting = false;
		Timer1.stop();
		Timer1.initialize(1000000 * hoursToFilter);      //Configura el TIMER en hoursToFilter Segundos
		Timer1.attachInterrupt(Temporizador) ; //Configura la interrupción del Timer 1
		return;
	}
}
void temperatureTimer(void){
	float tempC = analogRead(A0);
	tempC = (5.0 * tempC * 100.0)/1024.0;
	lcd.setCursor(0, 1);
	lcd.print(tempC);
	if (tempC < temperatureToHeat - 5){
		  digitalWrite(A5,HIGH);
	}else{
		if (tempC > temperatureToHeat + 5){
			digitalWrite(A5, LOW);
		}
	}

}


/*==================[end of file]============================================*/