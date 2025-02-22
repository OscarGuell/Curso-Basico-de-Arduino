#include <Servo.h>
// Declaración de LEDs.
int ledG = 12;
int ledY = 11;
int ledR = 10;
// Declarar un servo.
Servo srv;
int pinSrv = 6;
int plsMin = 600;
int plsMax = 2500;

// Variable para almacenar el estado del Bluetooth.
char state;
char reader;
String accum;
int angle;

String receivedValue = "";

void setup() {
  Serial.begin(9600);
  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledR, OUTPUT);
  srv.attach(pinSrv, plsMin, plsMax);
}

void loop() {
  // Comprobar si hay datos disponibles desde el módulo Bluetooth.
  if (Serial.available() > 0) {
    // Leer el comando enviado desde el Bluetooth.
    reader = Serial.read();

    if(reader == '\n'){
      // Una vez se recibe un '\n', se lee el número acumulado a partir de las señales recibidas.
      angle = map(accum.toInt(), 0, 255, 0, 179);
      // Mover el servomotor.
      srv.write(angle);
      // Limpiar la cadena de texto, para evitar choques con el próximo valor.
      accum = "";
    } else if(reader >= 'a' && reader <= 'e'){
      // Introducir los casos de comandos que brindemos al módulo.
      switch(reader){
        case 'a':
         // Alternar el estado del LED verde.
          digitalWrite(ledG, !digitalRead(ledG));
         break;
       case 'b':
         // Alternar el estado del LED amarillo.
         digitalWrite(ledY, !digitalRead(ledY));
         break;
       case 'c':
          // Alternar el estado del LED rojo.
          digitalWrite(ledR, !digitalRead(ledR));
          break;
        default:
         // Si el comando no es reconocido, no hacer nada.
         break;
      }
    } else{
      accum += reader;
    }
  }
}
