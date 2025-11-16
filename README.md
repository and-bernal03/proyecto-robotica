# proyecto-robotica
Codigo de movimiento de los servomotores 

// C++ code
//

#include <Servo.h>

const static int PUNTOS = 111;

static const uint8_t trayectorias[][PUNTOS] = {
//{0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3,3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,4,4.1,4.2,4.3,4.4,4.5,4.6,4.7,4.8,4.9,5,5.1,5.2,5.3,5.4,5.5,5.6,5.7,5.8,5.9,6,6.1,6.2,6.3,6.4,6.5,6.6,6.7,6.8,6.9,7,7.1,7.2,7.3,7.4,7.5,7.6,7.7,7.8,7.9,8,8.1,8.2,8.3,8.4,8.5,8.6,8.7,8.8,8.9,9,9.1,9.2,9.3,9.4,9.5,9.6,9.7,9.8,9.9,10,10.1,10.2,10.3,10.4,10.5,10.6,10.7,10.8,10.9,11}
{90,85,80,75,70,74,78,82,86,90,94,98,102,106,110,106.6666667,103.3333333,100,96.66666667,93.33333333,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90}
{90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,94,98,102,106,110,114,118,122,126,130,133,136,139,142,145,148,151,154,157,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,157,154,151,148,145,142,139,136,133,130,126,122,118,114,110,106,102,98,94,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90}
{90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,94.5,99,103.5,108,112.5,117,121.5,126,130.5,135,142,149,156,163,170,163,158.3333333,155,152.5,135,130.5,126,121.5,117,112.5,108,103.5,99,94.5,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90}
{90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,92,94,96,98,100,102,104,106,108,110,106,102,98,94,90,86,82,78,74,70,72,74,76,78,80,82,84,86,88,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90}
{90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,94,98,102,106,110,106,102,98,94,90,86,82,78,74,70,74,78,82,86,90}
};

/*---------------Variables globales-----------*/
int PIN_SOMBRERO = 3, 
	PIN_BRAZODERECHO = 5, 
	PIN_BRAZOIZQUIERDO = 6, 
	PIN_MUNECA = 9, 
	PIN_COLA = 10;

const int PERIODO = 100;

int iterador = 0;
unsigned long tiempo_transcurrido = 0; 

Servo sombrero, cola, brazoizquierdo, brazoderecho, muneca; 

void setup()
{
  Serial.begin(9600);
  while(!Serial){
  }
  Serial.println("Iniciando configuracion");
  
  sombrero.attach(PIN_SOMBRERO);
  cola.attach(PIN_BRAZODERECHO);
  brazoizquierdo.attach(PIN_BRAZOIZQUIERDO);
  brazoderecho.attach(PIN_MUNECA);
  muneca.attach(PIN_COLA);
  
  Serial.println("Servos configurados");
  
  sombrero.write(90);
  cola.write(90);
  brazoizquierdo.write(90);
  brazoderecho.write(90);
  muneca.write(90);
  
  Serial.println("Servos en posicion inicial");
  
  tiempo_transcurrido = millis();
}

void loop()
{
  unsigned long tiempo_actual = millis();
  if (tiempo_actual - tiempo_transcurrido < PERIODO){
    return;
  }
  
  
  Serial.print("Iniciando ciclo ");
  Serial.print(iterador);
  Serial.print(" total ");
  Serial.println(PUNTOS);
  
  Serial.print("Puntos: ");
  Serial.print(trayectorias[0][iterador]);
  Serial.print(", ");
  Serial.print(trayectorias[1][iterador]);
  Serial.print(", ");
  Serial.print(trayectorias[2][iterador]);
  Serial.print(", ");
  Serial.print(trayectorias[3][iterador]);
  Serial.print(", ");
  Serial.print(trayectorias[4][iterador]);
  Serial.println();
  
  sombrero.write(trayectorias[0][iterador]);
  cola.write(trayectorias[1][iterador]);
  brazoizquierdo.write(trayectorias[2][iterador]);
  brazoderecho.write(trayectorias[3][iterador]);
  muneca.write(trayectorias[4][iterador]);
      
  iterador++;
  if (iterador >= PUNTOS) {
    iterador = 0;
  }
  tiempo_transcurrido = millis();
}
