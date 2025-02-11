// 'Echo' se encargará de la entrada de información.
int echo = 10;
// 'Trig' funciona para salida de información.
int trig = 11;
int distancia;
int duracion;
int ledR = 9;
int ledG = 6;
int ledB = 5;
int buzzer = 3;


void setup()
{
  // 'Trig', por definición, estará en modo de salida.
  pinMode(trig, OUTPUT);
  // 'Echo' estará configurado para la entrada.
  pinMode(echo, INPUT);
  // Cantidad de información con la que trabaja el monitor Serial.
  // Esta frecuencia debe concordar con la configurada en el monitor (lupa, arriba derecha).
  Serial.begin(9600);
  // Activar los pines. 
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  
  // Emisor de sonido.
  pinMode(buzzer, OUTPUT);
}

void loop()
{

// Generar los pulsos.
  // Activar la emisión de frecuencia.
  digitalWrite(trig, HIGH);
  // Un pequeño delay para permitir una oscilación del sensor.
  delay(1);
  digitalWrite(trig, LOW);
  
// Traducir los pulsos a información.
  duracion = pulseIn(echo, HIGH); 
  // '58.2' es un valor único dado por el fabricante.
  // Funciona como un factor de conversión para las unidades propias de Arduino (baudio).
  distancia = duracion / 58.2;
  
  // println: "Print line".
  Serial.println(distancia);
  delay(200);

  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  
  if(distancia <= 50){
      // La velocidad de parpadeo del LED será en función de la distancia.
      digitalWrite(buzzer, HIGH);
      delay( distancia * 10);
      digitalWrite(buzzer, LOW);
    }

  if( distancia <= 50 && distancia > 30){
      digitalWrite(ledG, HIGH);
    } else if( distancia <= 30 && distancia > 10){
      digitalWrite(ledG, HIGH);
      digitalWrite(ledR, HIGH);
    } else if( distancia <= 10){
      digitalWrite(ledR, HIGH);
    }
}
