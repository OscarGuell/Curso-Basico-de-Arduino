#include <Servo.h>

// Declarar los pines del LED y los pulsadores.
int plsdLeft = 11;
int plsdRight = 12;

// Declarar el servo-motor.
Servo srv;
int pinSrv = 9;
int plsMin = 600;
int plsMax = 2500;

// Variables auxiliares
int angle = 0;
int ledSelect = 4;

void setup()
{
  pinMode(plsdLeft, INPUT);
  pinMode(plsdRight, INPUT);
  digitalWrite(ledB, HIGH);
  srv.attach(pinSrv, plsMin, plsMax);
}

void loop()
{

  delay(50);

  // Mover a la derecha.
  while( digitalRead(plsdRight) == HIGH ){
    if( angle > 0 ){
      angle--;
      srv.write(angle);
      delay(5);
    }
  }

  // Mover a la izquierda.
  while( digitalRead(plsdLeft) == HIGH ){
    if( angle < 179 ){
      angle++;
      srv.write(angle);
      delay(5); 
    }
  }
}
