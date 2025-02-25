// Incluir funcionalidad de Servo-motor.
#include <Servo.h>
// Declarar variables y pin del botón.
Servo srv;
int btn = 3;
bool dir = false;
int led = 7;

void setup() {
  // Acoplar el motor al pin 10.
  srv.attach(11);
  // El pin 03 leerá entradas de señal por parte del botón.
  pinMode(btn, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  // Botón presionado.
  if( digitalRead(btn) == LOW ){
    // Verificar si después de 75ms sigue presionado.
    delay(100);
    if(digitalRead(btn) == LOW){
      // Alternar el valor de dirección.
      dir = !dir;
      // False -> 180. True -> 0.
      srv.write( dir ? 180 : 0 );
      digitalWrite(led, HIGH);
      delay(315);
      srv.write(90);
      digitalWrite(led, LOWh);
      // "Atrapar" la iteración para que sólo se ejecute una vez.
      while( digitalRead(btn) == LOW );
    }
  }

  // Botón sin presionar.
  //if( digitalRead(btn) == HIGH ){
    // Verificar si después de 75ms sigue presionado.
    //delay(75);
    //if(digitalRead(btn) == HIGH){
      //srv.write(90);
      // "Atrapar" la iteración para que sólo se ejecute una vez.
      //while( digitalRead(btn) == HIGH );
    //}
  //}
} 
