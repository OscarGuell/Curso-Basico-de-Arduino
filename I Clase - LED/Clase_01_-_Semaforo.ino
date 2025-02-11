// Definir las variables e importar las bibliotecas al inicio del código.
int ledR = 10;
int ledG = 11;
int ledB = 8;
int intsyG=0;
int intsyB=0;

void setup() { // Iniciar la configuración. Se corre una vez.
  // Establecer el 'led' en modo 'output'.
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop() { // Definir el ciclo a iterar indefinidamente.
  for(int intsyR = 0; intsyR < 255; intsyR++){
    analogWrite(ledR,intsyR);
    intsyG = intsyR-25;
    intsyB = intsyR-50;
    if(intsyR > 25){
      analogWrite(ledG,intsyG);
      analogWrite(ledB,intsyG);
    }
    if(intsyR > 50){
      analogWrite(ledB,intsyG);
    }
    
  delay(50);
  }
  delay(150);
}
