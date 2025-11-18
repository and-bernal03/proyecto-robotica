
# proyecto-robotica
Codigo de movimiento de los servomotores 

// C++ code para Arduino - Inicia la secuencia al detectar movimiento (PIR)
// Conecte el OUT del sensor PIR al pin digital 2 (interrupt-capable)

#include <Servo.h>

const static int PUNTOS = 111;

// NOTA: he declarado como float para soportar valores decimales.
// Reemplace los [...] por el contenido completo de sus trayectorias si están recortadas.
static const float trayectorias[][PUNTOS] = {
//{0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3,3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,4,4.1,4.2,4.3,4.4,4.5,4.6,4.7,4.8,4.9,5,5.1,5[...]
{90,85,80,75,70,74,78,82,86,90,94,98,102,106,110,106.6666667,103.3333333,100,96.66666667,93.33333333,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,[...]
{90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,94,98,102,106,110,114,118,122,126,130,133,136,139,142,145,148,151,154,157,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,16[...]
{90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,94.5,99,103.5,108,112.5,117,121.5,126,130.5,135,142,149,156,163,170,163,158.[...]
{90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,92,94,96,98,100,102,104,106,108,110,106,102,98,94,90,86,82,78,74,70,72,74,76[...]
{90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,9[...]
};

/*---------------Variables globales-----------*/
int PIN_SOMBRERO = 3, 
    PIN_BRAZODERECHO = 5, 
    PIN_BRAZOIZQUIERDO = 6, 
    PIN_MUNECA = 9, 
    PIN_COLA = 10;

// Pin del sensor PIR (usar pin 2 en Arduino UNO/Nano para interrupción)
const int PIN_SENSOR = 2;

const int PERIODO = 100; // ms por punto

int iterador = 0;

Servo sombrero, cola, brazoizquierdo, brazoderecho, muneca; 

volatile bool motionDetected = false; // marcado por la ISR
unsigned long detectionTime = 0;      // timestamp opcional de la detección

// ISR simple: marca que se detectó movimiento
void IRAM_ATTR motionISR() {
  motionDetected = true;
  detectionTime = millis();
}

void setup()
{
  Serial.begin(9600);
  while(!Serial) { /* esperar monitor serie si hace falta */ }
  Serial.println("Iniciando configuracion");

  // Configurar servos
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

  // Configurar pin sensor y la interrupcion en flanco RISING (cuando el PIR pone HIGH)
  pinMode(PIN_SENSOR, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR), motionISR, RISING);

  Serial.println("Sensor PIR configurado. Esperando detecciones...");
}

void loop()
{
  // Si no hubo detección, salimos rápido y dejamos la ISR esperar nuevos eventos
  if (!motionDetected) {
    // Puedes hacer aquí otras tareas no bloqueantes si hace falta
    return;
  }

  // Entramos aquí cuando motionDetected == true
  // Desactivar la interrupción para evitar múltiples triggers mientras ejecutamos la secuencia
  detachInterrupt(digitalPinToInterrupt(PIN_SENSOR));

  Serial.print("Movimiento detectado en ms=");
  Serial.println(detectionTime);
  Serial.println("Iniciando secuencia de movimientos...");

  // Ejecutar la secuencia completa (bloqueante). Esto empieza inmediatamente tras la detección.
  playSequence();

  Serial.println("Secuencia terminada. Volviendo a modo espera.");

  // Limpiar bandera y volver a activar la interrupción para la próxima detección
  motionDetected = false;
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR), motionISR, RISING);
}

// Función que reproduce la secuencia completa punto por punto
void playSequence() {
  for (int i = 0; i < PUNTOS; i++) {
    // Imprimir algunos datos para depuración
    Serial.print("Ciclo ");
    Serial.print(i);
    Serial.print(" / ");
    Serial.println(PUNTOS);

    // Tomar los valores de las trayectorias (asegurarse de que la matriz está bien poblada)
    sombrero.write((int)trayectorias[0][i]);
    cola.write((int)trayectorias[1][i]);
    brazoizquierdo.write((int)trayectorias[2][i]);
    brazoderecho.write((int)trayectorias[3][i]);
    muneca.write((int)trayectorias[4][i]);

    // Esperar el periodo entre puntos
    delay(PERIODO);
  }
}
```
}
