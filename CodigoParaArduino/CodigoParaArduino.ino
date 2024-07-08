
#include <TaskScheduler.h>    //Se carga la librería del Scheduler
Scheduler RealTimeCore;       //Esto crea un objeto del tipo Scheduler (definido por la librería).

#define SatSuperior 820 
#define SatInferior 205

// Pines
int sensorRef = A0;          // Entrada del pote 
int sensorVplanta = A1;         // Salida Vread de la planta 
int source = 3;          // Variable controlada (alimentacion del circuito)

//Ganacia Global
int Uk_0_digital;                  // Valor de sourcing en digital

int Rk_0 = 0;                      // Valor leido sensorRef   
int Yk_0 = 0;                      // Valor leido de la planta

int Uk_0 = 0;                      // Valor a direccionar a sourcing 
int Uk_1 = 0;                      // Valor a direccionar a sourcing - anterior
int Uk_2 = 0;                      // Valor a direccionar a sourcing - anterior - anterior 

int Ek_0 = 0;                       // Valor del error R-Y actual
int Ek_1 = 0;                       // Valor del error R-Y anterior
int Ek_2 = 0;                       // Valor del error R-Y anterior - anterior

// Prototipos de las funciones
void source_control();           // Funcion destinada a muestrear e interpretar la entrada de sensorRef
void printData();                 // Funcion destinada a muestrear e interpretar la salida Vread del circuito


// Objetos de tipo task que se refrescan 10 veces por segundo
Task read_and_sourcing(100, TASK_FOREVER, &source_control, &RealTimeCore, true);      //
Task printing(500, TASK_FOREVER, &printData, &RealTimeCore, true);               //


// Definicion explicita de las funcios
void source_control(){
  Yk_0 = analogRead(sensorVplanta);
  Rk_0 = analogRead(sensorRef);
  Ek_0 = Rk_0 - Yk_0;

  Uk_0 = 31.66*Ek_0 - 61.12*Ek_1 + 29.47*Ek_2 + 1.812*Uk_1 - 0.8122*Uk_2;

  if (Uk_0 > SatSuperior){
    Uk_0 = SatSuperior;
  } else if (Uk_0 < SatInferior) {
    Uk_0 = SatInferior;
  }

  Ek_2 = Ek_1;
  Ek_1 = Ek_0;
  Uk_2 = Uk_1;
  Uk_1 = Uk_0;

  Uk_0_digital = map(Uk_0, 0, 1023, 0, 255);
  
  // Sourcing
  analogWrite(source, Uk_0_digital);  // Escribe el valor convertido al pin PWM

}

void printData(){
  Serial.println(Yk_0 * (5.0/1023) );  // Mostrando el valor de la planta en volts
}


// setup() # Este codigo corre una vez
void setup() {
  // El código que se ponga acá se ejecuta una única vez al inicio:
  Serial.begin(9600); //se inicia la comunicación serial a 9600 bauds
  Serial.println("INICIANDO...");
  pinMode(source, OUTPUT);
}


// --> Loop()  # Este codigo es un ciclo que corre indefinidamente
void loop() {
 // Acá va el código que se repite indefinidamente:
  RealTimeCore.execute(); // Cuando se usa un scheduler, esta instrucción es la única que debería estar en el loop

}

