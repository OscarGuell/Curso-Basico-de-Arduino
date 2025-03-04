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

// Declaración de pines.
int p0 = 2;
int p1 = 3;
int p2 = 4;
int p3 = 5;
int p4 = 6;
int p5 = 7;
int p6 = 9;

// Punteros recursivos.
int *grid_ptr;
int *pos_ptr;

// Función para resolver el cubo.
solve(int* grid, int* p){
// Parte A: Resolver la cruz roja.
	// Paso 1: Buscar piezas rojas en la cara Roja.
	// En caso de encontrarlas, las envía a la cara Naranja.
	for(int i=0; i<4; i++){
		if( grid[1+2*i] == 0){
			giro_horario
		}
	}
	
}


// Función para realizar un giro horario
void giro_horario(int* grid,  int* p, int eje) {

  int aux[3];
  
  // Parte 1: Caras laterales.
  
	// Caso A: Cara roja (0) o naranja (5).
	if (eje == 0 || eje == 5) {
		K = (eje == 0 ? 1 : 4);
		// Respaldar los valores de la primera cara (1 o 4) en un array auxiliar.
		for (int i = 0; i < 3; i++) {
			aux[i] = grid[K*9 + i];
		}
		// Sobreescribir la cara actual con los valores de la siguiente cara.
		for (int c = 1; c < 4; c++) {
			F = (eje == 0 ? c : 5-c);
			for (int i = 0; i < 3; i++) {
				grid[F*9 + i] = grid[ (F + (eje == 0 ? 1 : -1) ) * 9 + i ];
			}
		}
		// Asignar los valores guardados a la última cara (4 o 1).
		for (int i = 0; i < 3; i++) {
			grid[ (5-K)*9 + i ] = aux[i];
		}

	// Caso B: Azul (1), Blanco (2), Verde(3) o Amarillo (4).
	} else {

		int c1 = (eje + 2) % 4 + 1;
		int c2 = eje % 4 + 1;

		// Paso 1: Respaldar los valores de la cara inicial (0) en 'aux'.
		for (int i = 0; i < 3; i++) {
			aux[i] = grid[ p[ (eje - 1) * 12 + i] ];
		}

		// Paso 2: Actualizar '0'.
		for (int i = 0; i < 3; i++) {
			// [0 <- c1].
			grid[ p[ (eje - 1) * 12 + 3 * 0 + i ] ] = grid[ c1 * 9 + p[ (eje - 1) * 12 + 3 * 1 + i ] ];
		}

		// Paso 3: Actualizar 'C1'.
		for (int i = 0; i < 3; i++) {
			// [c1 <- 5].
			grid[ c1 * 9 + p[ (eje - 1) * 12 + ((eje == 3 || eje == 4) ? (2 - i) : i) + 3 * 1 ] ] = grid[ 5 * 9 + p[ (eje - 1) * 12 + i + 3 * 2 ] ];
		}

		// Paso 4: Actualizar '5'.
		for (int i = 0; i < 3; i++) {
			// [5 <- c2].
			grid[ 5 * 9 + p[ (eje - 1) * 12 + ((eje == 1 || eje == 4) ? (2 - i) : i) + 3 * 2] ] = grid[c2 * 9 + p[ (eje - 1) * 12 + i + 3 * 3] ];
		}

		// Paso 5: Usar 'aux' para actualizar la cara final (C2).
		for (int i = 0; i < 3; i++) {
			// [c2 <- aux].
			// Última ronda, empleando los valores auxiliares.
			grid[ c2 * 9 + p[ (eje - 1) * 12 + ((eje == 2 || eje == 3) ? (2 - i) : i) + 3 * 3 ] ] = aux[ ((eje == 1 || eje == 2) ? (2 - i) : i) ];
		}
	}

  // Parte 2: Rotación de la cara seleccionada.

	// Respaldar los valores originales de la cara a rotar en un array temporal.
	int temp[9];
	for (int i = 0; i < 9; i++) {
		temp[i] = grid[eje * 9 + i];
	}

	// Aplicar la rotación A[i][j] -> A[j][2-i].
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 3; i++) {
			grid[eje * 9 + j * 3 + (2 - i)] = temp[i * 3 + j];
		}
	}
    
  Serial.print("Giro horario. Cara ");
  Serial.println(eje);
  
}


// Función para realizar un giro antihorario
void giro_antihorario(int* grid, int* p, int eje) {

  int aux[3];
  
  // Parte 1: Caras laterales.

	// Caso A: Cara roja (0).
	if (eje == 0) {
		// Respaldar los valores de la última cara (4) en un array auxiliar.
		for (int i = 0; i < 3; i++) {
			aux[i] = grid[4 * 9 + i];
		}
		// Sobreescribir la cara actual con los valores de la cara anterior.
		for (int c = 4; c > 1; c--) {
			for (int i = 0; i < 3; i++) {
				grid[c * 9 + i] = grid[(c - 1) * 9 + i];
			}
		}
		// Asignar los valores guardados a la primera cara (1).
		for (int i = 0; i < 3; i++) {
			grid[9 + i] = aux[i];
		}

	// Caso B: Cara naranja (5).
	} else if (eje == 5) {
		// Respaldar los valores de la primera cara (1) en un array auxiliar.
		for (int i = 0; i < 3; i++) {
			aux[i] = grid[9 + i];
		}
		// Sobreescribir la cara actual con los valores de la siguiente cara.
		for (int c = 1; c < 4; c++) {
			for (int i = 0; i < 3; i++) {
				grid[c * 9 + i] = grid[(c + 1) * 9 + i];
			}
		}
		// Asignar los valores guardados a la última cara (4).
		for (int i = 0; i < 3; i++) {
			grid[4 * 9 + i] = aux[i];
		}

	// Caso C: Azul (1), Blanco (2), Verde(3) o Amarillo (4).
	} else {

		int c1 = (eje + 2) % 4 + 1;
		int c2 = eje % 4 + 1;

		// Paso 1: Respaldar los valores de la cara final (C2) en 'aux'.
		for (int i = 0; i < 3; i++) {
			aux[i] = grid[c2 * 9 + p[(eje - 1) * 12 + i + 3 * 3]];
		}

		// Paso 2: Actualizar 'C2'.
		for (int i = 0; i < 3; i++) {
			// [c2 <- 5].
			grid[c2 * 9 + p[(eje - 1) * 12 + i + 3 * 3]] = grid[5 * 9 + p[(eje - 1) * 12 + ((eje == 1 || eje == 4) ? (2 - i) : i) + 3 * 2]];
		}

		// Paso 3: Actualizar '5'.
		for (int i = 0; i < 3; i++) {
			// [5 <- c1].
			grid[5 * 9 + p[(eje - 1) * 12 + ((eje == 3 || eje == 4) ? (2 - i) : i) + 3 * 2]] = grid[c1 * 9 + p[(eje - 1) * 12 + 3 * 1 + i]];
		}

		// Paso 4: Actualizar 'C1'.
		for (int i = 0; i < 3; i++) {
			// [c1 <- 0].
			grid[c1 * 9 + p[(eje - 1) * 12 + 3 * 1 + i]] = grid[p[(eje - 1) * 12 + i]];
		}

		// Paso 5: Usar 'aux' para actualizar la cara inicial (0).
		for (int i = 0; i < 3; i++) {
			// [0 <- aux].
			grid[p[(eje - 1) * 12 + i]] = aux[i];
		}
	}

  // Parte 2: Rotación de la cara seleccionada (A[j][2-i] -> A[i][j]).

	// Respaldar los valores originales de la cara a rotar en un array temporal.
	int temp[9];
	for (int i = 0; i < 9; i++) {
		temp[i] = grid[eje * 9 + i];
	}

	// Aplicar la rotación A[j][2-i] -> A[i][j].
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 3; i++) {
			grid[eje * 9 + i * 3 + j] = temp[j * 3 + (2 - i)];
		}
	}
  
  Serial.print("Giro antihorario. Cara ");
  Serial.println(eje);
  
}



void setup() {
  
  	// Configurar pulsadores.
  	pinMode(p0, INPUT);
  	pinMode(p1, INPUT);
  	pinMode(p2, INPUT);
 	pinMode(p3, INPUT);
 	pinMode(p4, INPUT);
    pinMode(p5, INPUT);
    pinMode(p6, INPUT);
  
  	// Inicializar la pantalla serial para visualización del usuario.
    Serial.begin(9600);
  
    // Generar cubo rubik.
    static int grid[9*6];
    // Rellenar colores: Rojo (0) - Azul (1) - Blanco (2) - Verde (3) - Amarillo (4) - Naranja (5).
    for (int c = 0; c < 6; c++) {
        for (int i = 0; i < 9; i++) {
            grid[c * 9 + i] = c;
        }
    }

    // Lista de posiciones relativas para un giro horario <0,C1,5,C2>.
    static int pos[12 * 4]{
    	2, 5, 8,  2, 5, 8,  6, 3, 0,  0, 3, 6,  // eje == 1 (fila 0).
	0, 1, 2,  2, 5, 8,  0, 1, 2,  6, 3, 0,  // eje == 2 (fila 1).
	0, 3, 6,  8, 5, 2,  2, 5, 8,  6, 3, 0,  // eje == 3 (fila 2).
	6, 7, 8,  8, 5, 2,  8, 7, 6,  0, 3, 6   // eje == 4 (fila 3).
    };

    // Puntero a la grilla.
    grid_ptr = grid;
    // Puntero al arreglo de posiciones.
    pos_ptr = pos;
}

void loop() {
  
    // Pulsar el botón 'p0'.
  if( digitalRead(p0) == LOW ){
    // Verificar que 25ms después siga pulsado.
    delay(25);
    if( digitalRead(p0) == LOW){
      // Giro horario en la cara '0' (Rojo).
      giro_horario(grid_ptr, pos_ptr, 0);
      // Detener hasta soltar el botón.
      while( digitalRead(p0) == LOW );
    }
  }
  
  // Pulsar el botón 'p1'.
  if( digitalRead(p1) == LOW ){
    // Verificar que 25ms después siga pulsado.
    delay(25);
    if( digitalRead(p1) == LOW){
      // Giro horario en la cara '1' (Azul).
      giro_horario(grid_ptr, pos_ptr, 1);
      // Detener hasta soltar el botón.
      while( digitalRead(p1) == LOW );
    }
  }
  
  
  // Pulsar el botón 'p2'.
  if( digitalRead(p2) == LOW ){
    // Verificar que 25ms después siga pulsado.
    delay(25);
    if( digitalRead(p2) == LOW){
      // Giro horario en la cara '2' (Blanco).
      giro_horario(grid_ptr, pos_ptr, 2);
      // Detener hasta soltar el botón.
      while( digitalRead(p2) == LOW );
    }
  }
  
  
  // Pulsar el botón 'p3'.
  if( digitalRead(p3) == LOW ){
    // Verificar que 25ms después siga pulsado.
    delay(25);
    if( digitalRead(p3) == LOW){
      // Giro horario en la cara '3' (Verde).
      giro_horario(grid_ptr, pos_ptr, 3);
      // Detener hasta soltar el botón.
      while( digitalRead(p3) == LOW );
    }
  }
  
  
  // Pulsar el botón 'p4'.
  if( digitalRead(p4) == LOW ){
    // Verificar que 25ms después siga pulsado.
    delay(25);
    if( digitalRead(p4) == LOW){
      // Giro horario en la cara '4' (Amarillo).
      giro_horario(grid_ptr, pos_ptr, 4);
      // Detener hasta soltar el botón.
      while( digitalRead(p4) == LOW );
    }
  }

    
  // Pulsar el botón 'p5'.
  if( digitalRead(p5) == LOW ){
    // Verificar que 25ms después siga pulsado.
    delay(25);
    if( digitalRead(p5) == LOW){
      // Giro horario en la cara '5' (Azul).
      giro_horario(grid_ptr, pos_ptr, 5);
      // Detener hasta soltar el botón.
      while( digitalRead(p5) == LOW );
    }
  }
  
  // Pulsar el botón 'p6'.
  if( digitalRead(p6) == LOW ){
    // Verificar que 150ms después siga pulsado.
    delay(150);
    if( digitalRead(p6) == LOW){
      solve(grid_ptr, pos_ptr);
      // Detener hasta soltar el botón.
      while( digitalRead(p6) == LOW );
    }
  }
  
}
