// Definir los puertos de los leds.
int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int led5 = 6;

// Hasta qué número evaluar primos.
int end = 500;
// Velocidad de visualización (speed: 1 - 10).
int speed = 5;
int time = 100*(11-speed);

// Lista que representa los números a evaluar
#define end 500
bool numList[end];

// Número de LEDs (en este caso, 5).
int size = 5;

// Recursos.
int max = 0;
int ledN = 1;

// Iniciar la configuración. Se corre una vez.
void setup(){
  // Establecer los 'led' en modo 'output'.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  
  // Llenar la lista de 'true'.
  for(int i = 0; i < end; i++){
  	numList[i] = true;
  }
}

// Definir el ciclo a iterar indefinidamente.
void loop(){
  // Evaluar todos los números hasta 'end'.
  for(int X = 1; X < end; X++){
    // Calcular si X es primo, buscando hasta X/2.
    for(int E = 2; E <= X/2; E++){
      // Detectar divisores de 'X'.
      if(X % E == 0){
        numList[X] = false;
      }
    }
    // Encender números primos.
    if(numList[X] == true){
    	digitalWrite(ledN+1,HIGH);
    }
    // Avanzar al siguiente led.
    ledN++;
    // Cambiar de ronda cada 'size' (5 leds) iteraciones.
    if(X%size == 0){
      // Tiempo entre rondas.
      delay(time*2);
      // Volver al primer led.
      ledN = 1;
      // Apagar todos los led.
      for(int i = 2; i < size+2; i++){
      	digitalWrite(i, LOW);
      }
    }
    // Tiempo entre leds.
    delay(time);
  }
}