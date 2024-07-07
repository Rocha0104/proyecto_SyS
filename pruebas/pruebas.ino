int sensorPin = A0;    // Pin analógico donde está conectado el sensor
int outputPin = 9;     // Pin PWM donde quieres la salida analógica

void setup() {
  Serial.begin(9600);  // Inicializa la comunicación serie a 9600 baudios
  pinMode(outputPin, OUTPUT);  // Configura el pin de salida como salida
}

void loop() {
  int sensorValue = analogRead(sensorPin);  // Lee el valor del pin analógico A0 (valor entre 0 y 1023)
  int outputValue = map(sensorValue, 277, 1023, 58, 206);  // Convierte el valor al rango 0-255
  
  analogWrite(outputPin, outputValue);  // Escribe el valor convertido al pin PWM
  
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);  // Imprime el valor del sensor
  Serial.print("\tOutput Value: ");
  Serial.println(outputValue);  // Imprime el valor convertido
  
  delay(1000);  // Espera 1 segundo antes de la siguiente lectura
}
