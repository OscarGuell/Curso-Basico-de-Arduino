#include <Servo.h>
int ptn = A5;
int led = 11;
// Declaramos un 'Servo'.
Servo srv;
int pinSrv = 3;
// Definir el intervalo de valores para los pulsos.
int plsMin = 600;
int plsMax = 2500;
// Variables auxiliares.
long light;
long angle;

void setup() {
  pinMode(led, OUTPUT);
  //pinMode(ptn, OUTPUT);, no es necesario declarar porque viene con la función preestablecida por defecto. 

  //'attach' pérmite modificar el intervalo predeterminado del Servomotor.
  srv.attach(pinSrv, plsMin, plsMax);
}

void loop() {

  delay(10);
  light = map(analogRead(ptn), 0, 1023, 0, 255);
  angle = map(analogRead(ptn), 0, 1023, 0, 179);
  // Los pines analógicos funcionan con base '1024', mientras que los ángulos con base '180'.
  srv.write( angle );
  analogWrite(led, light );
}
