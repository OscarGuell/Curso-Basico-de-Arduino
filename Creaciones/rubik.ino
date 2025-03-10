/*
 * Notación del cubo de Rubik:
 *
 * - Caras (y colores):
 *   0: Rojo
 *   1: Azul
 *   2: Blanco
 *   3: Verde
 *   4: Amarillo
 *   5: Naranja
 *
 * - Posiciones dentro de cada cara (3x3):
 *   [0]: Esquina superior izquierda
 *   [1]: Arista superior
 *   [2]: Esquina superior derecha
 *   [3]: Arista izquierda
 *   [4]: Centro
 *   [5]: Arista derecha
 *   [6]: Esquina inferior izquierda
 *   [7]: Arista inferior
 *   [8]: Esquina inferior derecha
 *
 * - Conexiones entre caras:
 *   - Cara Roja (0):
 *     - Lado superior conectado a cara Blanca (2)
 *     - Lado derecho conectado a cara Azul (1)
 *   - Cara Azul (1):
 *     - Lado superior conectado a cara Roja (0)
 *     - Lado derecho conectado a cara Blanca (2)
 *   - Cara Blanca (2):
 *     - Lado superior conectado a cara Roja (0)
 *     - Lado derecho conectado a cara Verde (3)
 *   - Cara Verde (3):
 *     - Lado superior conectado a cara Roja (0)
 *     - Lado derecho conectado a cara Amarilla (4)
 *   - Cara Amarilla (4):
 *     - Lado superior conectado a cara Roja (0)
 *     - Lado derecho conectado a cara Amarilla (4)
 *   - Cara Naranja (5):
 *     - Lado superior conectado a cara Blanca (2)
 *     - Lado derecho conectado a cara Verde (3)
 */

#include <math.h>
#include <SoftwareSerial.h>
#include <Servo.h>

// Pines para la comunicación con el módulo Bluetooth | (RX, TX).
SoftwareSerial Bluetooth(10, 11);

// Declaración de pines.
byte srvP0 = 2;
byte srvP1 = 3;
byte srvP2 = 4;
byte srvP3 = 5;
byte srvP4 = 6;
byte srvP5 = 7;
byte plsd = 9;

// Declaración de Servomotores.
Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servos[6];

// Punteros auxiliares.
byte *grid_ptr;
byte *pos_ptr;
byte *servos_ptr;

// Variables para la lectura de comandos por Bluetooth.
bool selec;
char reader;

// Función para realizar un giro horario.
void giro_horario(byte* grid,  byte* p, byte eje) {

  byte aux[3];
  
  // Parte A: Caras laterales.
  	byte L, M, c1, c2;
	// Caso #1: Cara roja (0) o naranja (5).
	if (eje == 0 || eje == 5) {
		L = ((eje == 0) ? 1 : 4);
		// Respaldar los valores de la primera cara (1 o 4) en un array auxiliar.
		for (byte i = 0; i < 3; i++) {
			aux[i] = grid[L*9 + ((eje == 0) ? i : 8-i)];
		}
		// Sobreescribir la cara actual con los valores de la siguiente cara.
		for (byte c = 1; c < 4; c++) {
			M = ((eje == 0) ? c : 5-c);
			for (byte i = 0; i < 3; i++) {
				grid[M*9 + ((eje == 0) ? i : 8-i)] = grid[ (M + ((eje == 0) ? 1 : -1) )*9 + ((eje == 0) ? i : 8-i) ];
			}
		}
		// Asignar los valores guardados a la última cara (4 o 1).
		for (byte i = 0; i < 3; i++) {
			grid[ (5-L)*9 + ((eje == 0) ? i : 8-i) ] = aux[i];
		}

	// Caso #2: Azul (1), Blanco (2), Verde(3) o Amarillo (4).
	} else {
		// c1: Primera cara lateral.
		c1 = (eje + 2) % 4 + 1;
		// c2: Segunda cara lateral.
		c2 = eje % 4 + 1;

		// Paso 1: Respaldar los valores de la cara inicial (0) en 'aux'.
		for (byte i = 0; i < 3; i++) {
			aux[i] = grid[ p[ (eje - 1) * 12 + i] ];
		}

		// Paso 2: Actualizar '0'.
		for (byte i = 0; i < 3; i++) {
			// [0 <- c1].
			grid[ p[ (eje - 1) * 12 + i + 3 * 0 ] ] = grid[ c1 * 9 + p[ (eje - 1) * 12 + i + 3 * 1 ] ];
		}

		// Paso 3: Actualizar 'C1'.
		for (byte i = 0; i < 3; i++) {
			// [c1 <- 5].
			grid[ c1 * 9 + p[ (eje - 1) * 12 + ((eje == 3 || eje == 4) ? (2 - i) : i) + 3 * 1 ] ] = grid[ 5 * 9 + p[ (eje - 1) * 12 + i + 3 * 2 ] ];
		}

		// Paso 4: Actualizar '5'.
		for (byte i = 0; i < 3; i++) {
			// [5 <- c2].
			grid[ 5 * 9 + p[ (eje - 1) * 12 + ((eje == 1 || eje == 4) ? (2 - i) : i) + 3 * 2] ] = grid[c2 * 9 + p[ (eje - 1) * 12 + i + 3 * 3] ];
		}

		// Paso 5: Usar 'aux' para actualizar la cara final (C2).
		for (byte i = 0; i < 3; i++) {
			// [c2 <- aux].
			// Última ronda, empleando los valores auxiliares.
			grid[ c2 * 9 + p[ (eje - 1) * 12 + ((eje == 2 || eje == 3) ? (2 - i) : i) + 3 * 3 ] ] = aux[ ((eje == 1 || eje == 2) ? (2 - i) : i) ];
		}
	}

  // Parte B: Rotación de la cara seleccionada.

	// Respaldar los valores originales de la cara a rotar en un array temporal.
	byte temp[9];
	for (byte i = 0; i < 9; i++) {
		temp[i] = grid[eje * 9 + i];
	}

	// Aplicar la rotación A[i][j] -> A[j][2-i].
	for (byte j = 0; j < 3; j++) {
		for (byte i = 0; i < 3; i++) {
			grid[eje * 9 + j * 3 + (2 - i)] = temp[i * 3 + j];
		}
	}

	// Imprimir en la pantalla Serial el movimiento realizado.
  	Serial.print(F("Giro horario. Cara "));
  	Serial.print(eje);
  	Serial.println(F("."));

	// Realizar el giro en el servomotor correspondiente.
	servos[eje].attach(140);
	// Girar durante 150ms.
	delay(150);
	// Detener el giro.
	servos[eje].attach(90);
}



// Función para realizar un giro antihorario.
void giro_antihorario(byte* grid, byte* p, byte eje) {

	byte aux[3];
  
	// Parte A: Caras laterales.
	byte L, M, c1, c2;
	// Caso #1: Cara roja (0) o naranja (5).
	if (eje == 0 || eje == 5) {
		L = ((eje == 0) ? 1 : 4);
		// Respaldar los valores de la última cara (4 o 1) en un array auxiliar.
		for (byte i = 0; i < 3; i++) {
			aux[i] = grid[(5 - L) * 9 + ((eje == 0) ? i : 8 - i)];
		}
		// Sobreescribir la cara actual con los valores de la cara anterior.
		for (byte c = 4; c > 1; c--) {
			M = ((eje == 0) ? c : 5 - c);
			for (byte i = 0; i < 3; i++) {
				grid[M * 9 + ((eje == 0) ? i : 8 - i)] = grid[(M - ((eje == 0) ? 1 : -1)) * 9 + ((eje == 0) ? i : 8 - i)];
			}
		}
		// Asignar los valores guardados a la primera cara (1 o 4).
		for (byte i = 0; i < 3; i++) {
			grid[L * 9 + ((eje == 0) ? i : 8 - i)] = aux[i];
		}

	// Caso #2: Azul (1), Blanco (2), Verde(3) o Amarillo (4).
	} else {
		// c1: Primera cara lateral.
		c1 = (eje + 2) % 4 + 1;
		// c2: Segunda cara lateral.
		c2 = eje % 4 + 1;

		// Paso 1: Respaldar los valores de la cara final (C2) en 'aux'.
		for (byte i = 0; i < 3; i++) {
			aux[i] = grid[c2 * 9 + p[(eje - 1) * 12 + ((eje == 2 || eje == 3) ? (2 - i) : i) + 3 * 3]];
		}

		// Paso 2: Actualizar 'C2'.
		for (byte i = 0; i < 3; i++) {
			// [c2 <- 5].
			grid[c2 * 9 + p[(eje - 1) * 12 + ((eje == 1 || eje == 4) ? (2 - i) : i) + 3 * 3]] = grid[5 * 9 + p[(eje - 1) * 12 + i + 3 * 2]];
		}

		// Paso 3: Actualizar '5'.
		for (byte i = 0; i < 3; i++) {
			// [5 <- C1].
			grid[5 * 9 + p[(eje - 1) * 12 + ((eje == 3 || eje == 4) ? (2 - i) : i) + 3 * 2]] = grid[c1 * 9 + p[(eje - 1) * 12 + i + 3 * 1]];
		}

		// Paso 4: Actualizar 'C1'.
		for (byte i = 0; i < 3; i++) {
			// [C1 <- 0].
			grid[c1 * 9 + p[(eje - 1) * 12 + i + 3 * 1]] = grid[p[(eje - 1) * 12 + i + 3 * 0]];
		}

		// Paso 5: Usar 'aux' para actualizar la cara inicial (0).
		for (byte i = 0; i < 3; i++) {
			// [0 <- aux].
			grid[p[(eje - 1) * 12 + i + 3 * 0]] = aux[((eje == 1 || eje == 2) ? (2 - i) : i)];
		}
	}

	// Parte B: Rotación de la cara seleccionada.

	// Respaldar los valores originales de la cara a rotar en un array temporal.
	byte temp[9];
	for (byte i = 0; i < 9; i++) {
		temp[i] = grid[eje * 9 + i];
	}

	// Aplicar la rotación A[i][j] -> A[2-j][i].
	for (byte j = 0; j < 3; j++) {
		for (byte i = 0; i < 3; i++) {
			grid[eje * 9 + (2 - j) * 3 + i] = temp[i * 3 + j];
		}
	}

	// Imprimir en la pantalla Serial el movimiento realizado.
	Serial.print(F("Giro antihorario. Cara "));
	Serial.print(eje);
	Serial.println(F("."));

	// Realizar el giro en el servomotor correspondiente.
	servos[eje].attach(40);
	// Girar durante 150ms.
	delay(150);
	// Detener el giro.
	servos[eje].attach(90);
}



void hilera_superior_cara_lateral(byte* grid, byte* pos, byte c){
	// Detectar si hay una arista roja en la hilera superior de la cara 'c'.
	if( grid[c*9 + 1] == 0 ){
		// En caso de haber, asegura que un giro horario sobre la cara no retire una arista roja de la cara Naranja (5).
		while( grid[ 5*9 + ((c<3) ? 5-2*c : 2*c-1) ] == 0 ){
			giro_horario(grid, pos, 5);
		}
		// Giro horario en la cara donde se encontró una arista roja.
		// La arista roja encontrada se ubicará en la posición '5' de la misma cara después del giro.
		giro_horario(grid, pos, c);
		// Aprovechar el espacio encontrado previamente en la cara Naranja (5) para el próximo giro antihorario.
		giro_horario(grid, pos, 5);
		// Se coloca la arista roja en la cara Naranja (5) mediante un giro antihorario en la siguiente cara lateral.
		giro_antihorario(grid, pos, c%4+1);
		// Comprobar que regresar la cara actual a su estado original no retirará una arista roja.
		if( grid[ 5*9 + ((c<3) ? 5-2*c : 2*c-1) ] == 0 ){
			byte rec = 0;
			while( grid[ 5*9 + ((c<3) ? 5-2*c : 2*c-1) ] == 0 ){
				// 'rec' se utiliza para detener el ciclo 'while' en caso de que se detecten todas las aristas rojas en la cara Naranja.
				// Para la comprobación, un máximo de tres giros es suficiente.
				if(rec == 2){
					break;
				}
				giro_horario(grid, pos, 5);
				rec++;
			}
			if(rec < 2){
				// Regresar la cara actual a su estado original.
				giro_antihorario(grid, pos, c);
			}
		}
	}
}



void lado_izquierdo_cara_lateral(byte* grid, byte* pos, byte c){
	// K: Cara lateral anterior.
	byte K = (c+2) % 4 + 1;
	// Detectar si hay una arista roja en el lado izquierdo de la cara 'c'.
	if( grid[c*9 + 3] == 0 ){
		// En caso de haber, comprobar que un giro horario en la cara anterior (K) no retire una arista roja de la cara Naranja (5).
		while( grid[ 5*9 + ((K<3) ? 5-2*K : 2*K-1) ] == 0 ){
			giro_horario(grid, pos, 5);
		}
		// Colocar la arista roja encontrada en la cara Naranja (5).
		giro_horario(grid, pos, K);
		// Comprobar si el movimiento colocó una arista roja en la cara Roja (0).
		if( grid[ (4*K-9)*((K<3) ? -1 : 1) ] == 0 ){
			// En caso de haberse colocado, comprobar que el envío no reemplace a otra arista roja en la cara Naranja (5).
			while( grid[ 5*9 + ((K<3) ? 5-2*K : 2*K-1) ] == 0 ){
				// En caso de encontrar conflicto, girar la cara Naranja (5) hasta resolverlo.
				giro_horario(grid, pos, 5);
			}
			// Colocar la arista "del conflicto" en la cara Naranja (5).
			giro_horario(grid, pos, K);
			giro_horario(grid, pos, K);
		}
		// Comprobar si el movimiento colocó una arista roja en la hilera superior de la cara 'K'.
		if( grid[K*9 + 1] == 0 ){
			hilera_superior_cara_lateral(grid, pos, K);
		}
		// Comprobar si el movimiento colocó una arista roja en el lado izquierdo de la cara anterior (para c>1).
		if( grid[K*9 + 3] == 0 ){
			// En caso de comprobarse, se envía la pieza a la cara Naranja (5).
			lado_izquierdo_cara_lateral(grid, pos, K);
		}
	} 
}



void lado_derecho_cara_lateral(byte* grid, byte* pos, byte c){
	// F: Cara lateral siguiente.
	byte F = c % 4 + 1;
	// Detectar si hay una arista roja al lado derecho de la cara 'c'.
	if( grid[c*9 + 5] == 0 ){
		// En caso de haber, comprobar que un giro antihorario en la cara siguiente (F) no retire una arista roja de la cara Naranja (5).
		while( grid[ 5*9 + ((F<3) ? 5-2*F : 2*F-1) ] == 0 ){
			giro_horario(grid, pos, 5);
		}
		// Colocar la arista roja encontrada en la cara Naranja (5).
		giro_antihorario(grid, pos, F);
		// Comprobar si el movimiento colocó una arista roja en la hilera superior de la cara 'F'.
		if( grid[F*9 + 1] == 0 ){
			hilera_superior_cara_lateral(grid, pos, F);
		}
		// Para c=4: Comprobar si el movimiento colocó una arista roja en el lado derecho de la cara Azul (1).
		if( c==4 && grid[14] == 0 ){
			lado_derecho_cara_lateral(grid, pos, 1);
		}
	}
}



void esquinas_rojas_cara_naranja(byte* grid, byte* pos){
	byte c;
	bool rec;
	// Recorrer las esquinas de la cara naranja.
	for(byte i=1; i<5; i++){
		// En caso de encontrar una esquina roja, busca alinearla en la cara lateral correcta.
		if( grid[ 5*9 + 2*i + ((i<3) ? -2 : 0) ] == 0 ){
			rec = false;
			c = i;
			while(rec == false){
				if( grid[(c%4+1)*9 + 6] == c || grid[c*9 + 8] == c%4+1 ){
					c = c % 4 + 1;
					rec = true;
					break;
				}
				giro_horario(grid, pos, 5);
				c = c % 4 + 1;
			}
			// Una vez alineada la esquina en una posición opuesta a la correcta, se ejecuta el algoritmo.
			giro_antihorario(grid, pos, c);
			giro_antihorario(grid, pos, 5);
			giro_antihorario(grid, pos, 5);
			giro_horario(grid, pos, c);
			giro_horario(grid, pos, 5);
			giro_antihorario(grid, pos, c);
			giro_antihorario(grid, pos, 5);
			giro_horario(grid, pos, c);
		}
	}
}



void subir_esquina_izquierda(byte* grid, byte* pos, byte c){
	giro_horario(grid, pos, 5);
	giro_horario(grid, pos, (c+2)%4+1);
	giro_antihorario(grid, pos, 5);
	giro_antihorario(grid, pos, (c+2)%4+1);
}



void subir_esquina_derecha(byte* grid, byte* pos, byte c){
	giro_antihorario(grid, pos, 5);
	giro_antihorario(grid, pos, c%4+1);
	giro_horario(grid, pos, 5);
	giro_horario(grid, pos, c%4+1);
	
}



void selec_giro(byte* grid, byte* pos, byte c, bool state){
	if(state == true){
		giro_horario(grid, pos, c);
	} else{
		giro_antihorario(grid, pos, c);
	}
}



void esquina_roja_hilera_inferior_izquierda(byte* grid, byte* pos, byte c){
	byte K = c;
	bool find;
	// Detectar si la esquina inferior izquierda de la cara 'c' es roja.
	if( grid[c*9 + 6] == 0 ){
		do{
			// Cara lateral anterior a 'K'.
			K = (K+2) % 4 + 1;
			find = true;
			if( grid[K*9 + 8] == K ){
				find = false;
				break;
			}
			giro_antihorario(grid, pos, 5);
			
		} while(find);
		subir_esquina_izquierda(grid, pos, K%4+1);
	}
}



void esquina_roja_hilera_inferior_derecha(byte* grid, byte* pos, byte c){
	byte F = c;
	bool find;
	// Detectar si la esquina inferior izquierda de la cara 'c' es roja.
	if( grid[c*9 + 8] == 0 ){
		do{
			// Cara lateral siguiente a 'F'.
			F = F % 4 + 1;
			find = true;
			if( grid[F*9 + 6] == F ){
				find = false;
				break;
			}
			giro_horario(grid, pos, 5);
			
		} while(find);
		subir_esquina_derecha(grid, pos, (F+2)%4+1);
	}
}



void revision_superior(byte* grid, byte* pos){
	byte R;
	bool find;
	// Recorrer las diagonales de la cara Roja (0).
	do{
		find = false;
		for(byte i=1; i<5; i++){
			R = (i < 3) ? 3-i : i;
			// Detectar esquinas rojas en la cara Roja, pero en su posición incorrecta.
			if( grid[ 2*i + ((i<3) ? -2 : 0) ] == 0 && grid[R*9 + 2] != R ){
				giro_horario(grid, pos, R);
				giro_horario(grid, pos, 5);
				giro_antihorario(grid, pos, R);
				subir_esquina_izquierda(grid, pos, (R+1)%4+1);
			}
		}
		// Verificar si es necesario volver a hacer el ciclo.
		for(byte i=1; i<5; i++){
			R = (i<3) ? 3-i : i;
			// Detectar esquinas rojas en la cara Roja, pero en su posición incorrecta.
			if( grid[ 2*i + ((i<3) ? -2 : 0) ] == 0 && grid[R*9 + 2] != R ){
				find = true;
				break;
			}
		}
	// En caso de 'find == true', se ejecutará nuevamente el código.
	} while(find);
}



void giro_aleatorio(byte* grid, byte* pos){
  	byte c = random(0,6);
  	bool f = random(0,2);
	selec_giro(grid, pos, c, f);
}



void cruz_roja(byte* grid, byte* pos){
	bool find;
	// Paso 1: Buscar aristas rojas en la cara Roja (0).
	Serial.println(F("Paso 1. Buscar aristas rojas en la cara Roja."));
	// En caso de encontrar una arista roja en la cara Roja (0), la envía a la cara Naranja (5).
	for(byte i=0; i<4; i++){
		if( grid[2*i + 1] == 0 ){
			// Comprobar que el envío no reemplace a otra arista roja en la cara Naranja (5).
			while( grid[ 5*9 + ((i<2) ? 4*i+1 : 4*i-5) ] == 0 ){
				// En caso de encontrar conflicto, girar la cara Naranja (5) hasta resolverlo.
				giro_horario(grid, pos, 5);
			}
			// Colocar la arista roja en la cara Naranja (5).
			giro_horario( grid, pos, ((i<2) ? i+2 : 3*i-5) );
			giro_horario( grid, pos, ((i<2) ? i+2 : 3*i-5) );
		}
	}
	
	// Paso 2: Buscar aristas rojas en la hilera superior de cada cara lateral (1-4).
	Serial.println(F("Paso 2: Buscar aristas rojas en la hilera superior de cada cara lateral."));
	do{
		find = false;
		for(byte c=1; c<5; c++){
			hilera_superior_cara_lateral(grid, pos, c);
		}
		// Verificación.
		for(byte c=1; c<5; c++){
			if( grid[c*9 + 1] == 0 ){
				Serial.println(F("¡Repetir Paso A.2!"));
				find = true;
				break;
			}
		}
	// En caso de 'find == true', se ejecutará nuevamente el código.
	} while(find);
	

	// Paso 3: Buscar aristas rojas en el lado izquierdo de cada cara lateral (1-4).
	Serial.println(F("Paso 3: Buscar aristas rojas en el lado izquierdo de cada cara lateral."));
	do{
		find = false;
		for(byte c=1; c<5; c++){
			lado_izquierdo_cara_lateral(grid, pos, c);
		}
		// Verificación.
		for(byte c=1; c<5; c++){
			if( grid[c*9 + 3] == 0 ){
				Serial.println(F("¡Repetir Paso A.3!"));
				find = true;
				break;
			}
		}
	// En caso de 'find == true', se ejecutará nuevamente el código.
	} while(find);
	

	// Paso 4: Buscar aristas rojas en el lado derecho de cada cara lateral (1-4).
	Serial.println(F("Paso 4: Buscar aristas rojas en el lado derecho de cada cara lateral."));
	do{
		find = false;
		for(byte c=1; c<5; c++){
			lado_derecho_cara_lateral(grid, pos, c);
		}
		// Verificación.
		for(byte c=1; c<5; c++){
			if( grid[c*9 + 5] == 0 ){
				Serial.println(F("¡Repetir Paso A.4!"));
				find = true;
				break;
			}
		}
	// En caso de 'find == true', se ejecutará nuevamente el código.
	} while(find);

	// Paso 5: Buscar aristas rojas en la hilera inferior de cada cara lateral (1-4).
	Serial.println(F("Paso 5: Buscar aristas rojas en la hilera inferior de cada cara lateral."));
	do{
		find = false;
		for(byte c=1; c<5; c++){
			// Detectar si hay una arista roja en la hilera inferior de la cara 'c'.
			if( grid[c*9 + 7] == 0 ){
				// Algoritmo para colocar la arista roja en la cara Naranja (5) aprovechando el espacio generado por la arista encontrada.
				giro_antihorario(grid, pos, c);
				giro_horario(grid, pos, 5);
				giro_antihorario(grid, pos, c % 4 + 1);
				// Regresar la cara Naranja (5) a su posición original, para evitar problemas en la iteración.
				giro_antihorario(grid, pos, 5);
			}
		}
		// Verificación.
		for(byte c=1; c<5; c++){
			if( grid[c*9 + 7] == 0 ){
				Serial.println(F("¡Repetir Paso A.5!"));
				find = true;
				break;
			}
		}
	// En caso de 'find == true', se ejecutará nuevamente el código.
	} while(find);
}



void verify(byte* grid, byte* pos, byte A){
	// Verificación de la posición de las piezas color 'A'.
	for(byte c=0; c<6; c++){
		for(byte i=0; i<9; i++){
			if( grid[c*9 + i] == A ){
				Serial.print(F("Color "));
				Serial.print(A);
				Serial.print(F(" en cara "));
				Serial.print(c);
				Serial.print(F(", pos "));
				Serial.println(i);
			}
		}
	}
}



void esquinas_cara_roja(byte* grid, byte* pos){
	bool find;
	// Paso 1: Revisar en las hileras superiores de las caras laterales si existen esquinas rojas en la orientación correcta, pero posición incorrecta.
	Serial.println(F("Paso 1. Revisar en las hileras superiores de las caras laterales si existen esquinas rojas en la orientacion correcta, pero posicion incorrecta."));
	revision_superior(grid, pos);
	
	// Paso 2: Buscar esquinas rojas en la cara Naranja (5).
	Serial.println(F("Paso 2: Buscar esquinas rojas en la cara Naranja."));
	do{
		find = false;
		esquinas_rojas_cara_naranja(grid, pos);
		// Verificación.
		for(byte i=1; i<5; i++){
			if( grid[ 5*9 + 2*i + ((i<3) ? -2 : 0) ] == 0 ){
				Serial.println(F("¡Repetir Paso B.2!"));
				find = true;
				break;
			}
		}
	// En caso de 'find == true', se ejecutará nuevamente el código.
	} while(false);

	// Paso 3: Buscar 'rojo' (0) en la esquina inferior izquierda de cada cara lateral.
	Serial.println(F("Paso 3: Buscar 'rojo' en la esquina inferior izquierda de cada cara lateral."));
	// Si al final del bloque 'do' se encuentra un 'c' tal que se cumpla la condición 'grid[c*9 + 6] == 0', se repetirá la ejecución del bloque.
	do{
		find = false;
		for(byte c=1; c<5; c++){
			// Detectar si la esquina inferior izquierda de la cara 'c' es roja.
			esquina_roja_hilera_inferior_izquierda(grid, pos, c);
		}

		// Comprobar si existe algún otro valor 'c' que satisfaga 'grid[c*9 + 6] == 0'. En dado caso, se repetirá el código.
		for(byte c=1; c<5; c++){
			// Detectar si la esquina inferior de la cara 'c' es roja.
			if( grid[c*9 + 6] == 0 ){
				Serial.println(F("¡Repetir Paso B.3!"));
				find = true;
				break;
			}
		}
	// En caso de 'find == true', se ejecutará nuevamente el código.
	} while(find);

	// Paso 4: Buscar 'rojo' (0) en la esquina inferior derecha de cada cara lateral.
	Serial.println(F("Paso 4: Buscar 'rojo' en la esquina inferior derecha de cada cara lateral."));
	// Si al final del bloque 'do' se encuentra un 'c' tal que se cumpla la condición 'grid[c*9 + 8] == 0', se repetirá la ejecución del bloque.
	do{
		find = false;
		for(byte c=1; c<5; c++){
			// Detectar si la esquina inferior derecha de la cara 'c' es roja.
			esquina_roja_hilera_inferior_derecha(grid, pos, c);
		}

		// Comprobar si existe algún otro valor 'c' que satisfaga 'grid[c*9 + 8] == 0'. En dado caso, se repetirá el código.
		for(byte c=1; c<5; c++){
			// Detectar si la esquina inferior de la cara 'c' es roja.
			if( grid[c*9 + 8] == 0 ){
				Serial.println(F("Repetir Paso B.5"));
				find = true;
				break;
			}
		}
	// En caso de 'find == true', se ejecutará nuevamente el código.
	} while(find);

	// Paso 5: Buscar esquinas rojas en la hilera superior de las caras laterales.
	Serial.println(F("Paso 5: Buscar esquinas rojas en la hilera superior de las caras laterales."));
	do{
		find = false;
		for(byte c=1; c<5; c++){
			// Esquina superior izquierda.
			if( grid[c*9] == 0 ){
				// K: Cara lateral anterior.
				byte K = (c+2) % 4 + 1;
				// Caso #1: Esquina en posición correcta, pero orientación incorrecta.
				if( grid[ ((c<3) ? 14-6*c : 6*c-18) ] == K ){
					giro_horario(grid, pos, K);
					giro_antihorario(grid, pos, 5);
					giro_antihorario(grid, pos, K);
					giro_horario(grid, pos, 5);
					giro_horario(grid, pos, K);
					giro_antihorario(grid, pos, 5);
					giro_antihorario(grid, pos, K);
				// Caso #2: Esquina en posición y orientación incorrectas.
				} else{
					// Mover la esquina a la hilera inferior de la cara lateral anterior.
					giro_antihorario(grid, pos, c);
					giro_antihorario(grid, pos, 5);
					giro_horario(grid, pos, c);
					// "Subir" la esquina roja en su posición correcta.
					esquina_roja_hilera_inferior_izquierda(grid, pos, K);
				}
			}
			// Esquina superior derecha.
			if( grid[c*9 + 2] == 0 ){
				// F: Cara lateral siguiente.
				byte F = c % 4 + 1;
				// Caso #1: Esquina en posición correcta, pero orientación incorrecta.
				if( grid[ ((c<3) ? 4-2*c : 3*c) ] == F ){
					giro_antihorario(grid, pos, F);
					giro_horario(grid, pos, 5);
					giro_horario(grid, pos, F);
					giro_antihorario(grid, pos, 5);
					giro_antihorario(grid, pos, F);
					giro_horario(grid, pos, 5);
					giro_horario(grid, pos, F);
				// Caso #2: Esquina en posición y orientación incorrectas.
				} else{
					// Mover la esquina a la hilera inferior de la cara lateral siguiente.
					giro_horario(grid, pos, c);
					giro_horario(grid, pos, 5);
					giro_antihorario(grid, pos, c);
					// "Subir" la esquina roja en su posición correcta.
					esquina_roja_hilera_inferior_derecha(grid, pos, F);
				}
			}
		}

		// Verificar si es necesario repetir el bloque de código.
		for(byte c=1; c<5; c++){
			if( grid[c*9] == 0 || grid[c*9 + 2] == 0){
				Serial.println(F("Repetir Paso B.5"));
				find = true;
				break;
			}
		}
	// En caso de 'find == true', se ejecutará nuevamente el código.
	} while(find);
}



void colocar_arista_inferior(byte* grid, byte* pos, byte c){
	// F: Cara lateral siguiente; K: Cara lateral anterior.
	byte F = c % 4 + 1;
	byte K = (c+2) % 4 + 1;
	// Variable auxiliar para condensar el código.
	bool state = (grid[ 5*9 + ((c<3) ? 5-2*c : 2*c-1) ] == F);
	// Caso #1 (state): El lado de la arista en la cara Naranja (5) es del color de la cara lateral siguiente (F).
	// Caso #2 (!state): El lado de la arista en la cara Naranja (5) es del color de la cara lateral anterior (K).
	selec_giro(grid, pos, 5, !state);
	selec_giro(grid, pos, state ? F : K, !state);
	selec_giro(grid, pos, 5, state);
	selec_giro(grid, pos, state ? F : K, state);
	selec_giro(grid, pos, 5, state);
	selec_giro(grid, pos, c, state);
	selec_giro(grid, pos, 5, !state);
	selec_giro(grid, pos, c, !state);
}



void mover_naranja(byte* grid, byte* pos, byte c, byte N){
	// K: Cara lateral anterior.
	byte K = (c+2) % 4 + 1;
	giro_horario(grid, pos, c);
	// Repetir el movimiento 'N' veces.
	for(byte i=0; i < N; i++){
		giro_horario(grid, pos, K);
		giro_horario(grid, pos, 5);
		giro_antihorario(grid, pos, K);
		giro_antihorario(grid, pos, 5);
	}
	giro_antihorario(grid, pos, c);
}


// Función a emplear durante la alineación de aristas de la última cara.
void permutar_aristas(byte* grid, byte* pos, byte c){
	giro_antihorario(grid, pos, c);
	giro_antihorario(grid, pos, 5);
	giro_horario(grid, pos, c);
	giro_antihorario(grid, pos, 5);
	giro_antihorario(grid, pos, c);
	giro_antihorario(grid, pos, 5);
	giro_antihorario(grid, pos, 5);
	giro_horario(grid, pos, c);
	giro_antihorario(grid, pos, 5);
}



bool revisar_posicion(byte* grid, byte* pos, byte c){
	// Revisar con base en la esquina inferior derecha de la cara.
	byte count;
	byte F = c % 4 + 1;
	// Verificar si la esquina tiene el color de la cara actual.
	if( grid[c*9 + 8] == c || grid[F*9 + 6] == c || grid[5*9 + ((c<3) ? 2*c-2 : 14-2*c)] == c ){
		count++;
	}
	// Verificar si la esquina tiene el color de la cara siguiente.
	if( grid[c*9 + 8] == F || grid[F*9 + 6] == F || grid[5*9 + ((c<3) ? 2*c-2 : 14-2*c)] == F ){
		count++;
	}
	// En caso de encontrar ambos colores, sabemos que la esquina está en su posición.
	if(count == 2){
		return true;
	} else{
		return false;
	}
}




void permutar_esquinas(byte* grid, byte* pos, byte c){
	byte F = c % 4 + 1;
	byte K = (c+2) % 4 + 1;
	giro_antihorario(grid, pos, 5);
	giro_antihorario(grid, pos, F);
	giro_horario(grid, pos, 5);
	giro_horario(grid, pos, K);
	giro_antihorario(grid, pos, 5);
	giro_horario(grid, pos, F);
	giro_horario(grid, pos, 5);
	giro_antihorario(grid, pos, K);
}



void girar_esquinas(byte* grid, byte* pos){
	for(byte c=1; c<5; c++){
		// Primera posible rotación.
		if( grid[1*9 + 6] != c){
			giro_antihorario(grid, pos, 4);
			giro_antihorario(grid, pos, 0);
			giro_horario(grid, pos, 4);
			giro_horario(grid, pos, 0);
			giro_antihorario(grid, pos, 4);
			giro_antihorario(grid, pos, 0);
			giro_horario(grid, pos, 4);
			giro_horario(grid, pos, 0);
		}
		// Segunda posible rotación.
		if( grid[1*9 + 6] != c){
			giro_antihorario(grid, pos, 4);
			giro_antihorario(grid, pos, 0);
			giro_horario(grid, pos, 4);
			giro_horario(grid, pos, 0);
			giro_antihorario(grid, pos, 4);
			giro_antihorario(grid, pos, 0);
			giro_horario(grid, pos, 4);
			giro_horario(grid, pos, 0);
		}
		// Ir recorriendo las esquinas respectivas.
		giro_antihorario(grid, pos, 5);
	}
}

void comprobar(byte* grid, byte* pos){
	for(byte i=0; i<3; i++){
		for(byte c=0; c<6; c++){
			for(byte j=0; j<3; j++){
				Serial.print( grid[c*9 + 3*i + j] );
				Serial.print(F(" "));
			}
			if(c<5){
				Serial.print(F("| "));
			}
		}
		Serial.println("");
	}
}


// Función para resolver el cubo.
void solve(byte* grid, byte* pos){

	// Mostrar el estado inicial del cubo.
	comprobar(grid, pos);
	// Esperar 5 segundos antes de iniciar el algoritmo.
	delay(5000);
	
// Parte A: Colocar la cruz roja.
	bool find;
	byte count, R, F, N;
  	Serial.println(F("Parte A. Cruz roja."));
	cruz_roja(grid, pos);

	// Contención de errores: Si no se encuentran 4 aristas rojas en la cara Naranja (5), se repite el proceso 'cruz_roja'.
	do{
		find = true;
		count = 0;
		// Contar el número de aristas rojas en la cara Naranja (5).
		for(byte i = 0; i<4; i++){
			if( grid[5*9 + 1 + 2*i] == 0 ){
				count++;
			}
		}
		// Si el total es de 4 aristas rojas, se rompe el ciclo.
		if(count == 4){
			find = false;
			break;
		}
		// Caso contrario, se repite el proceso 'cruz_roja'.
		Serial.println(F("Repetir el proceso cruz_roja"));
		cruz_roja(grid, pos);
	// En caso de 'find == true', se ejecutará nuevamente el código.	
	} while(find);

	// Paso 6: Paso 6: Mover las aristas rojas de la cara Naranja (5) a la cara Roja (0).
	Serial.println(F("Paso 6: Mover las aristas rojas de la cara Naranja (5) a la cara Roja (0)."));
	byte rep = 0;
	count = 0;
	// Iterar hasta haber desplazado 4 aristas.
	while(rep < 4){
		// Explorar las caras laterales.
		for(byte c=1; c<5; c++){
			// Buscar aristas en la hilera inferior que coincidan con el color del centro de la cara.
			if( grid[c*9 + 7] == c && grid[ 5*9 + ((c<3) ? 5-2*c : 2*c-1) ] == 0 ){
				giro_horario(grid, pos, c);
				giro_horario(grid, pos, c);
				rep++;
				count++;
				if(count > 12){
					Serial.println(F("Error en Paso A.6"));
					break;
				}
			}
		}
		// Girar la cara Naranja (5) y continuar el ciclo hasta haber desplazado 4 aristas.
		giro_horario(grid, pos, 5);
	}

// Parte B: Esquinas de la cara Roja (0).
	Serial.println(F("Parte B: Esquinas de la cara Roja."));
	do{
		find = false;
		esquinas_cara_roja(grid, pos);
		// Verificar si alguna esquina de la cara roja es de un color diferente.
		for(byte i=1; i<5; i++){
			if( grid[ 2*i + ((i<3) ? -2 : 0) ] != 0 ){
				// En caso de encontrar una esquina errónea, repite el proceso 'esquinas_cara_roja'.
				Serial.println(F("Repetir proceso esquinas_cara_roja"));
				find = true;
				break;
			}
		}
	} while(find);
	
// Parte C: Aristas intermedias.
	Serial.println(F("Parte C: Aristas intermedias."));
	Serial.println(F("Paso 1: Buscar aristas sin color naranja (5) en la hilera inferior de cada cara lateral."));
	// Paso 1: Buscar aristas sin color naranja (5) en la hilera inferior de cada cara lateral.
	bool check;
	do{
		find = false;
		for(byte c=1; c<5; c++){
			// Revisar ambos costados de la arista ubicada en la hilera inferior de la cara 'c'.
			if( grid[c*9 + 7] != 5 && grid[5*9 + ((c<3) ? 5-2*c : 2*c-1) ] != 5 ){
				// R: Variable auxiliar.
				R = c;
				// Repetir el ciclo hasta que la arista inferior coincida con la cara correspondiente.
				do{
					check = true;
					if( grid[R*9 + 7] == R ){
						check = false;
						break;
					} else{
						// Actualizar 'R' a la cara lateral siguiente.
						R = R % 4 + 1;
						giro_horario(grid, pos, 5);
					}
				} while(check);
				// Colocar la arista en su posición correcta.
				colocar_arista_inferior(grid, pos, R);
			}
		}

		// Verificación.
		for(byte c=1; c<5; c++){
			// Repetir el bloque de código en caso de encontrar una arista restante.
			if( grid[c*9 + 7] != 5 && grid[5*9 + ((c<3) ? 5-2*c : 2*c-1) ] != 5 ){
				Serial.println(F("Repetir Paso C.1"));
				find = true;
				break;
			}
		}
	} while(find);
	
	Serial.println(F("Paso 2: Buscar aristas intermedias en la posición correcta, pero con orientacion incorrecta."));
	// Paso 2: Buscar aristas intermedias en la posición correcta, pero con orientación incorrecta.
	do{
		find = false;
		byte F;
		for(byte c=1; c<5; c++){
			// F: Cara lateral siguiente.
			F = c % 4 + 1;
			// Detectar si la arista derecha es del color de la cara lateral siguiente y viceversa.
			if( grid[c*9 + 5] == F && grid[F*9 + 3] == c ){
				// Retirar la pieza de su posición.
				giro_antihorario(grid, pos, F);
				giro_horario(grid, pos, 5);
				giro_horario(grid, pos, F);
				giro_horario(grid, pos, 5);
				giro_horario(grid, pos, c);
				giro_antihorario(grid, pos, 5);
				giro_antihorario(grid, pos, c);
				// Colocarla nuevamente, con la orientación corregida.
				giro_horario(grid, pos, 5);
				giro_antihorario(grid, pos, F);
				giro_horario(grid, pos, 5);
				giro_horario(grid, pos, F);
				giro_horario(grid, pos, 5);
				giro_horario(grid, pos, c);
				giro_antihorario(grid, pos, 5);
				giro_antihorario(grid, pos, c);
			}
		}

		// Verificación.
		for(byte c=1; c<5; c++){
			if( grid[c*9 + 5] == c%4+1 && grid[(c%4+1)*9 + 3] == c ){
				Serial.println(F("Repetir Paso C.2"));
				find = true;
				break;
			}
		}
	} while(find);

// Parte D. Cara naranja.
	Serial.println(F("Parte D: Cruz naranja."));
	Serial.println(F("Paso 1: Posibles casos para la orientacion de las aristas de la cara Naranja."));
	// Paso 1: Posibles casos para la orientación de las aristas de la cara Naranja (5).
	count = 0;
	// Contar el número de aristas naranjas en la cara Naranja (5).
	for(byte i=0; i<4; i++){
		if( grid[5*9 + 2*i + 1] == 5 ){
			count++;
		}
	}
	// Caso #1: Ninguna arista naranja.
	if(count == 0){
		mover_naranja(grid, pos, 1, 2);
		mover_naranja(grid, pos, 2, 1);
	} else if(count == 2){
		// Caso #2: Dos aristas naranjas opuestas.
		if( (grid[5*9 + 1] == 5 && grid[5*9 + 7] == 5) || (grid[5*9 + 3] == 5 && grid[5*9 + 5] == 5) ){
			mover_naranja(grid, pos, ((grid[5*9 + 1] == 5) ? 1 : 2), 1);
		// Caso #3: Dos aristas naranjas contiguas.
		} else{
			// Orientar la cara naranja en la posición deseada.
			do{
				check = true;
				if( grid[5*9 + 1] == 5 && grid[5*9 + 5] == 5 ){
					check = false;
					break;
				}
				giro_horario(grid, pos, 5);
				
			} while(check);
			mover_naranja(grid, pos, 1, 2);
		}
	// Caso #4: Cuatro aristas naranjas (ninguna acción es necesaria).
	}

	// Paso 2: Alinear las aristas naranjas con las caras laterales.
	Serial.println(F("Paso 2: Alinear las aristas naranjas con las caras laterales."));
	// Probar las cuatro orientaciones posibles de la cara naranja hasta encontrar dos o cuatro aristas alineadas.
	for(byte N=0; N < 4; N++){
		// Contar la cantidad de aristas alineadas.
		count = 0;
		// Revisar las cuatro caras laterales, contando el número de aristas alineadas.
		// Si el número de aristas es menor a 2, se continúa iterando. En caso de ser 2 o 4, se ejecutan los casos posibles.
		for(byte c=1; c<5; c++){
			if( grid[c*9 + 7] == c ){
				count++;
			}
			// Caso #1: Cuatro aristas alineadas.
			if(count == 4){
				// En caso de encontrar una configuración donde estén las cuatro aristas alineadas, salta al siguiente paso.
				goto loops_exit;
			// Dos aristas alineadas.
			} else if(count == 2){
				// Caso #2: Dos aristas alineadas opuestas.
				if( (grid[1*9 + 7] == 1 && grid[3*9 + 7] == 3) || (grid[2*9 + 7] == 2 && grid[4*9 + 7] == 4) ){
					permutar_aristas(grid, pos, ((grid[1*9 + 7] == 1) ? 1 : 2));
					permutar_aristas(grid, pos, ((grid[1*9 + 7] == 1) ? 4 : 1));
					permutar_aristas(grid, pos, ((grid[1*9 + 7] == 1) ? 1 : 2));
					// Continuar al siguiente paso.
					goto loops_exit;
				// Caso #3: Dos aristas alineadas contiguas.
				} else{
					byte i;
					i = 1;
					do{
						F = i % 4 + 1;
						if( grid[i*9 + 7] == i && grid[F*9 + 7] == F ){
							permutar_aristas(grid, pos, i);
							// Continuar al siguiente paso.
							goto loops_exit;
						} else{
							i++;
						}
						// Contención de errores.
						if(i > 4){
							Serial.println(F("Error fatal en el Paso D.2"));
							goto loops_exit;
						}
					} while(true);
				}
			}
		}
		giro_horario(grid, pos, 5);
	}
	// Línea a la que el código para continuar con el siguiente paso.
	loops_exit:

	// Paso 3: Posición de las esquinas.
	Serial.println(F("Paso 3: Posición de las esquinas."));
	while(true){
		count = 0;
		// Revisar cuántas esquinas están en su posición correcta.
		for(byte c=1; c<5; c++){
			// Cada vez que encuentre una esquina en posición, suma al contador.
			if( revisar_posicion(grid, pos, c) == true ){
				// En caso de ser la primera esquina en posición encontrada, reservarla.
				if(count == 0){
					N = c;
				}
				count++;
			}
		}
		// Caso #1: Sólo una esquina en posición correcta (sin considerar orientación).
		if(count == 1){
			permutar_esquinas(grid, pos, N);
		// Caso #2: Ninguna esquina en posición correcta.
		} else if(count == 0){
			permutar_esquinas(grid, pos, 1);
		// Caso #3: Cuatro esquinas en posición (continuar al siguiente paso).
		} else if(count == 4){
			// El ciclo 'while' únicamente se detendrá si 'count == 4'.
			goto exit_loop;
			break;
		}
	}

	exit_loop:

	// Paso 4: Orientación de las esquinas.
	girar_esquinas(grid, pos);

	Serial.println(F("Cubo resuelto!"));
	comprobar(grid, pos);
	
}





void setup() {
  
  	// Configurar pulsador.
	pinMode(plsd, INPUT);
	
	// Configurar servomotores.
	servo0.attach(srvP0);
	servo1.attach(srvP1);
	servo2.attach(srvP2);
	servo3.attach(srvP3);
	servo4.attach(srvP4);
	servo5.attach(srvP5);
  
  	// Inicializar la pantalla serial para visualización del usuario.
   	Serial.begin(9600);
	// Inicializar la lectura de datos desde el puerto Bluetooth.
	Bluetooth.begin(9600);

	// Arreglo con los pines conectados a los servomotores.
	servos = {servo0, servo1, servo2, servo3, servo4, servo5};
  
    	// Generar cubo rubik.
 	static byte grid[9*6];
   	// Rellenar colores: Rojo (0) - Azul (1) - Blanco (2) - Verde (3) - Amarillo (4) - Naranja (5).
   	for (byte c = 0; c < 6; c++) {
      		for (byte i = 0; i < 9; i++) {
       			grid[c * 9 + i] = c;
       		}
   	}

    	// Lista de posiciones relativas para un giro horario <0,C1,5,C2>.
    	static byte pos[12 * 4]{
		2, 5, 8,  2, 5, 8,  6, 3, 0,  0, 3, 6,  // eje == 1 (fila 0).
		0, 1, 2,  2, 5, 8,  0, 1, 2,  6, 3, 0,  // eje == 2 (fila 1).
		0, 3, 6,  8, 5, 2,  2, 5, 8,  6, 3, 0,  // eje == 3 (fila 2).
		6, 7, 8,  8, 5, 2,  8, 7, 6,  0, 3, 6   // eje == 4 (fila 3).
   	};

    	// Puntero a la grilla.
    	grid_ptr = grid;
    	// Puntero al arreglo de posiciones.
    	pos_ptr = pos;

	// Estado inicial de 'selec'.
	selec = true;
}

void loop() {
	
	// Comprobar si hay datos disponibles desde el módulo Bluetooth.
	if (Bluetooth.available() > 0) {
		// Leer el comando enviado desde el Bluetooth.
		reader = Bluetooth.read();
		// Introducir todos los casos de comandos que brindemos al módulo.
		switch(reader){
			// Alternar tipo de giro ( Horario <-> Antihorario ). Predeterminado: Giro horario.
			case 'a':
				selec = !selec;
				break;
			// Giro en cara Roja (0).
			case 'b':
				selec_giro(grid_ptr, pos_ptr, 0, selec);
				break;
			// Giro en cara Azul (1).
			case 'c':
				selec_giro(grid_ptr, pos_ptr, 1, selec);
				break;
			// Giro en cara Blanca (2).
			case 'd':
				selec_giro(grid_ptr, pos_ptr, 2, selec);
				break;
			// Giro en cara Verde (3).
			case 'e':
				selec_giro(grid_ptr, pos_ptr, 3, selec);
				break;
			// Giro en cara Amarilla (4).
			case 'f':
				selec_giro(grid_ptr, pos_ptr, 4, selec);
				break;
			// Giro en cara Naranja (5).
			case 'g':
				selec_giro(grid_ptr, pos_ptr, 5, selec);
				break;
			// Resolver el cubo Rubik en el estado inicial dado.
			case 'S':
				solve(grid_ptr, pos_ptr);
				break;
			default:
         			// Si el comando no es reconocido, no hacer nada.
         			break;
		}
	}
  
	// Pulsar el botón conectado al pin 'plsd'. Genera giros aleatorios.
	if( digitalRead(plsd) == LOW ){
		// Verificar que 150ms después siga pulsado.
		delay(150);
		// Detener hasta soltar el botón.
	  	if( digitalRead(plsd) == LOW){
			while( digitalRead(plsd) == LOW ){
				giro_aleatorio(grid_ptr, pos_ptr);
				delay(250);
			}
		}
	}
}
