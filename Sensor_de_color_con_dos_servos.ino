// Incluir Librerias
#include "Servo.h"
#include "Wire.h"
#include "Adafruit_TCS34725.h"
 
// Posiciones del servo en grados para los distintos colores
const int redPos = 160;
const int orangePos = 130;
const int yellowPos = 100;
const int greenPos = 70;
const int bluePos = 30;
const int nonePos = 0; // ningun objeto reconocido
 
// Inicializar el servo
Servo myservo;
Servo myservo2;
 
// Inicializar el sensor de color
// Parametros: https://learn.adafruit.com/adafruit-color-sensors/program-it
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);
 
// setup() Ejecucion de arduino al iniciar
void setup() {
 
 // Comunicacion serial para dar salida al valor en el monitor
 Serial.begin(9600);
 Serial.println("Inicializacion");
 
 // Comprobacion del sensor
 if (tcs.begin()) {
 // Todo bien
 Serial.println("Sensor encontrado");
 } else {
 // No se encontro ningun sensor. REVISAR
 Serial.println("TCS34725 No encontrado, verificar conexion");
 while (1); // Parada
 } 
 
 // Servo 1 conectado al pin 3 (PWM) 
 myservo.attach(3);
 // Servo se mueve a la posicion base
 myservo.write(0);
 delay(1000);
 //Servo 2 conectado al pin 4
 myservo2.attach (4);
 
}
 
// loop() 
void loop() {
  
  
  myservo2.write(80);    //posición reposo para el servo 2
  delay(2000);
  myservo2.write(22);    //cae la bola y la lleva al agujero servo 2
  delay(5000);
  myservo2.write(0);     
  delay(1000);
 
 // El sensor devuelve valores para R,G,B y un valor claro
 uint16_t clearcol, red, green, blue;
 float average, r, g, b;
 delay(100); // La medicion tomada es en 50 mili segundos
 tcs.getRawData(&red, &green, &blue, &clearcol);
 
 // Determinacion de colores
 
 // Obtener el promedio de RGB
 average = (red+green+blue)/3;
 // Aproximacion de los colores en 1 
 r = red/average;
 g = green/average;
 b = blue/average;
 
 // Valor claro de salida y rgb en serie para el control
 // R, G, B debe estar entre 0,5 y 1,5
 // Si el sensor ve rojo, entonces R debe estar por encima de 1, y G, B entre 0,5 y 1
 Serial.print("\tClear:"); Serial.print(clearcol);
 Serial.print("\tRed:"); Serial.print(r);
 Serial.print("\tGreen:"); Serial.print(g);
 Serial.print("\tBlue:"); Serial.print(b);
 
 // Determinacion de color
 if ((r > 1.2) && (g < 0.9) && (b < 0.9)) {
 Serial.print("\tRED");
 myservo.write(redPos);
 }
 else if ((r < 0.95) && (g > 1.3) && (b < 1.1)) {
 Serial.print("\tGREEN");
 myservo.write(greenPos);
 }
 else if ((r < 0.8) && (g < 1.2) && (b > 1.2)) {
 Serial.print("\tBLUE");
 myservo.write(bluePos);
 }
 else if ((r > 1.05) && (g > 1.15) && (b < 0.8)) {
 Serial.print("\tYellow");
 myservo.write(yellowPos);
 }
 //else if ((r > 1.3) && (g < 1.0) && (b < 0.8)) {
 //Serial.print("\tORANGE");
 //myservo.write(orangePos);
 //}// 
 else {
 Serial.print("\tNo Reconocido"); 
 // myservo.write(nonePos);
 }
 
 
 Serial.println("");
 
 delay(1500);
 
}
