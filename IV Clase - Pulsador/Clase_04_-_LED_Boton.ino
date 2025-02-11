// Declarar los pines del LED y el pulsador.
int led = 2;
int plsd = 10;

void setup()
{
  pinMode(led, OUTPUT);
  
  pinMode(plsd, INPUT);
}

void loop()
{
  // Cuando el pulsador esté presionado, se enciende el LED.
  if (digitalRead(plsd) == HIGH){
    digitalWrite(led, HIGH);    
  // Caso contrario, se mantendrá apagado.
  } else{
    digitalWrite(led, LOW);
  }
}
