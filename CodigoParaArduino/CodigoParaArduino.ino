
#include <TaskScheduler.h>    //Se carga la librería del Scheduler
Scheduler RealTimeCore;       //Esto crea un objeto del tipo Scheduler (definido por la librería).


// Pines
int sensorRef = A0;          // Entrada del pote 
int sensorVplanta = A1;         // Salida Vread de la planta 
int source = 3;          // Variable controlada (alimentacion del circuito)


//Ganacia Global
float error = 0;                  // Error actual
float error_ant = 0;              // Error anterior
float error_acum = 0;             // Error acumulado
int analogRef;                       // Valor de sensorRef
int digitalRefSat;
int analogPlanta = 0;                // Salida de la planta
int varVs = 0;                  // Señal de control


// Prototipos de las funciones
void func_sensorRef();           // Funcion destinada a muestrear e interpretar la entrada de sensorRef
void func_Vread();                 // Funcion destinada a muestrear e interpretar la salida Vread del circuito
void func_Vs();                   // Funcion destianada a controlar la alimentacion de la planta


// Objetos de tipo task que se refrescan 10 veces por segundo
Task tarea_ref(500, TASK_FOREVER, &func_sensorRef, &RealTimeCore, true);      //
Task tarea_vs(100, TASK_FOREVER, &func_Vs, &RealTimeCore, true);               //
Task tarea_Vread(500, TASK_FOREVER, &func_Vread, &RealTimeCore, true);           //


// Definicion explicita de las funcios
void func_sensorRef(){
  analogRef = analogRead(sensorRef);
  digitalRefSat = map(analogRef, 0, 1023, 54, 206);
}

void func_Vs(){
  analogWrite(source, digitalRefSat);  // Escribe el valor convertido al pin PWM
}

void func_Vread(){
  analogPlanta = analogRead(sensorVplanta);
  Serial.println(analogPlanta);
}

// setup() # Este codigo corre una vez
void setup() {
  // El código que se ponga acá se ejecuta una única vez al inicio:
  Serial.begin(9600); //se inicia la comunicación serial a 9600 bauds
  Serial.println("Se inicializo el Scheduler");
  pinMode(3, OUTPUT);
}


// --> Loop()  # Este codigo es un ciclo que corre indefinidamente
void loop() {
 // Acá va el código que se repite indefinidamente:
  RealTimeCore.execute(); // Cuando se usa un scheduler, esta instrucción es la única que debería estar en el loop

}


//-------------------------------------------------------


//// Librerías utilizadas
//#include <TaskScheduler.h>
//Scheduler RealTimeCore;
//
//// Pines utilizados en el Arduino
//int source = 3;
//int sensorRef = A0;
//int Planta = A1;
//
//// Variables globales
//float error = 0; // Error actual
//float error_ant = 0; // Error anterior
//float error_acum = 0; // Error acumulado
//float ref = 0; // Valor de sensorRef
//float val = 0; // Salida de la planta
//float u = 0; // Señal de control
//
//// Se definen los parámetros del source
//#define KP 6000 // Ganancia proporcional
//#define KI 6.19355 // Ganancia integral
//#define KD 60.366 // Ganancia derivativa
//#define TS 0.1 // Tiempo de muestreo en segundos
//
//// Se definen los prototipos de las funciones de cada una de las tareas
//void tarea01Fun();
//void tarea02Fun();
//void tarea03Fun();
//void tarea04Fun();
//bool state = false;
//bool laststate = false;
//
//// Se crean las tareas
//// Tareas que se repiten cada 500 milisegundos indefinidamente
//Task tarea01(500, TASK_FOREVER, &tarea01Fun, &RealTimeCore, true);
//Task tarea02(500, TASK_FOREVER, &tarea02Fun, &RealTimeCore, true);
//Task tarea03(500, TASK_FOREVER, &tarea03Fun, &RealTimeCore, true);
//Task tarea04(1000, TASK_FOREVER, &tarea04Fun, &RealTimeCore, true);
//
//// Ahora se definen explícitamente las funciones
//
//void tarea01Fun(){
//    ref = analogRead(sensorRef); // leer el valor de la entrada de sensorRef del potenciómetro
//    val = analogRead(Planta); // leer el valor de la salida de la planta
//}
//
//void tarea02Fun(){
//    error = ref - val; // Calcular el error actual
//    error_acum = error_acum + error * TS; // Calcular el error acumulado (integral)
//}
//
//void tarea03Fun(){
//    // Se calcula la señal de control usando el source PID
//    u = KP * error + KI * error_acum + KD * (error - error_ant) / TS;
//    
//    // Se limita la señal de control a un rango específico (0-255)
//    u = constrain(u, 0, 255);
//    
//    // Se escribe la señal de control en el pin PWM
//    analogWrite(source, u);
//}
//
//void tarea04Fun(){
//    // Se envían los valores ya normalizados de la sensorRef y la salida de la planta por el puerto serie
//    Serial.print("sensorRef: ");
//    Serial.print(ref);
//    Serial.print(" - Salida de la planta: ");
//    Serial.println(val);
//}
//
//void setup() {
//    // Inicializar la comunicación serie
//    Serial.begin(9600);
//    
//    // Inicializar los pines
//    pinMode(source, OUTPUT);
//    pinMode(sensorRef, INPUT);
//    pinMode(Planta, INPUT);
//    
//    // Iniciar el scheduler
////    RealTimeCore.startNow();
//}
//
//void loop() {
//    // Ejecutar el scheduler
//    RealTimeCore.execute();
//}
//
//
//
//
//
//