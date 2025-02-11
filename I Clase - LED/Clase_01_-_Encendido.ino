// Definir las variables e importar las bibliotecas al inicio del código.
  // Definir el número de puerto para 'led'.
int ledG = 12;
int ledY = 11;
int ledR = 10;

void setup() { // Iniciar la configuración. Se corre una vez.
  // Establecer el 'led' en modo 'output'.
  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledR, OUTPUT);
}

void loop() { // Definir el ciclo a iterar indefinidamente.
  // Leer 'ledG' digitalmente. 'HIGH': Enviar un '1' (envío de señal).
  digitalWrite(ledG,HIGH);
  // Establecer un delay de 1000 (ms).
  delay(2500);
  // 'LOW': Enviar un '0' (cortar la señal).
  digitalWrite(ledG,LOW);
  delay(250);
  digitalWrite(ledY,HIGH);
  delay(250);
  digitalWrite(ledY,LOW);
  delay(250);
  digitalWrite(ledY,HIGH);
  delay(250);
  digitalWrite(ledY,LOW);
  delay(250);
  digitalWrite(ledY,HIGH);
  delay(250);
  digitalWrite(ledY,LOW);
  delay(250);
  digitalWrite(ledR,HIGH);
  delay(2500);
  digitalWrite(ledR,LOW);
  delay(500);
}
