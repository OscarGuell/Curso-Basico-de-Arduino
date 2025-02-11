#include <Servo.h>
// 'Echo' se encargará de la entrada de información.
int echo = 10;
// 'Trig' funciona para salida de información.
int trig = 11;
int distancia;
int duracion;
int ledR = 9;
int ledB = 5;
int ledG = 6;
int count = 0;
Servo servo;


void setup()
{
  Serial.begin(9600);
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);

  // Acoplar el servo motor al pin '3'.
  servo.attach(3);
  
}

void loop()
{
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);
  
  duracion = pulseIn(echo, HIGH);
  distancia = duracion / 58.2;
  
  Serial.println(distancia);
  delay(200);
  
  if(distancia <= 20 && distancia >  0){    
      digitalWrite(ledR, LOW);
      digitalWrite(ledG, HIGH);
      delay(50);
      digitalWrite(ledG, LOW);
      if(count < 10){
        count += 1;  
      } else{
        servo.write(150);  
      }
  } else{
      digitalWrite(ledR, HIGH);
      if(count > 0){
        count -= 1;
      } else{
        servo.write(0);
      }
  }
}
