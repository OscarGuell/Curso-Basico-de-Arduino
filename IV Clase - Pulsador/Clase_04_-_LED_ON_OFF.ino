// Declarar los pines del LED y el pulsador.
int ledR = 2;
int ledG = 3;
int ledB = 4;
int plsd = 6;
int ledSelect = 1;

void setup()
{
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(plsd, INPUT);
}

void loop()
{
  // Función a ejecutar cuando el botón esté presionado.
  if( digitalRead(plsd) == HIGH ){
    // Se requiere presionar el pulsador al menos 50ms para cambiar el estado del LED.
    delay(100);
    // Segunda verificación.
    if( digitalRead(plsd) == HIGH ){
      // Alternar entre los tres colores del LED RGB.
      ledSelect++;
      if(ledSelect == 5){
        ledSelect = 2;  
      }
      digitalWrite(ledSelect, HIGH);
      // Esperar a que sea soltado el pulsador.
      while( digitalRead(plsd) == HIGH );
      delay(200);
      digitalWrite(ledR, LOW);
      digitalWrite(ledG, LOW);
      digitalWrite(ledB, LOW);
    }
  }
}
