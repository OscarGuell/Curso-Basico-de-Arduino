#include <Arduino.h>

// Función para realizar un giro horario
void giro_horario(int* grid, int eje) {

	// Parte 1: Caras laterales.
	int aux[3];

	// Caso A: Cara roja (0).
	if (eje == 0) {
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

	// Caso B: Cara naranja (5).
	} else if (eje == 5) {
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

	// Caso C: Azul (1), Blanco (2), Verde(3) o Amarillo (4).
	} else {

		int c1 = (eje + 2) % 4 + 1;
		int c2 = eje % 4 + 1;

		// Paso 1: Respaldar los valores de la cara inicial (0) en 'aux'.
		for (int i = 0; i < 3; i++) {
			aux[i] = grid[p[(eje - 1) * 12 + i]];
		}

		// Paso 2: Actualizar '0'.
		for (int i = 0; i < 3; i++) {
			// [0 <- c1].
			grid[p[(eje - 1) * 12 + 3 * 0 + i]] = grid[c1 * 9 + p[(eje - 1) * 12 + 3 * 1 + i]];
		}

		// Paso 3: Actualizar 'C1'.
		for (int i = 0; i < 3; i++) {
			// [c1 <- 5].
			grid[c1 * 9 + p[(eje - 1) * 12 + ((eje == 3 || eje == 4) ? (2 - i) : i) + 3 * 1]] = grid[5 * 9 + p[(eje - 1) * 12 + i + 3 * 2]];
		}

		// Paso 4: Actualizar '5'.
		for (int i = 0; i < 3; i++) {
			// [5 <- c2].
			grid[5 * 9 + p[(eje - 1) * 12 + ((eje == 1 || eje == 4) ? (2 - i) : i) + 3 * 2]] = grid[c2 * 9 + p[(eje - 1) * 12 + i + 3 * 3]];
		}

		// Paso 5: Usar 'aux' para actualizar la cara final (C2).
		for (int i = 0; i < 3; i++) {
			// [c2 <- aux].
			// Última ronda, empleando los valores auxiliares.
			grid[c2 * 9 + p[(eje - 1) * 12 + ((eje == 2 || eje == 3) ? (2 - i) : i) + 3 * 3]] = aux[((eje == 1 || eje == 2) ? (2 - i) : i)];
		}
	}

	// Paso 2: Rotación de la cara seleccionada.

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
}


// Función para realizar un giro antihorario
void giro_antihorario(int* grid, int eje) {

	// Parte 1: Caras laterales.
	int aux[3];

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

	// Paso 2: Rotación de la cara seleccionada (A[j][2-i] -> A[i][j]).

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
}


// Función para imprimir la grilla en terminal (C++). Usado para pruebas.
void print_grid(int* grid) {
	for (int c = 0; c < 6; c++) {
		std::cout << " --- " << c << " ---" << std::endl;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				std::cout << grid[c * 9 + i * 3 + j] << " ";
			}
			std::cout << std::endl;
		}
	}    
}


// Función para resolver el cubo usando el Método de Capas.
void solve(int* grid, int* p) {
    // Resolver la primera capa (capa inferior)
    Serial.println("Resolviendo primera capa...");

    // Paso 1: Resolver la cruz de la primera capa.
    while (grid[46] != 2 || grid[37] != 0) { // Blanco (2) y Rojo (0)
        giro_horario(grid, p, 0); // Giro horario en la cara Roja
    }
    while (grid[50] != 2 || grid[28] != 1) { // Blanco (2) y Azul (1)
        giro_horario(grid, p, 1); // Giro horario en la cara Azul
    }
    while (grid[52] != 2 || grid[19] != 3) { // Blanco (2) y Verde (3)
        giro_horario(grid, p, 3); // Giro horario en la cara Verde
    }
    while (grid[48] != 2 || grid[10] != 5) { // Blanco (2) y Naranja (5)
        giro_horario(grid, p, 5); // Giro horario en la cara Naranja
    }

    // Paso 2: Resolver las esquinas de la primera capa
    while (grid[45] != 2 || grid[36] != 0 || grid[18] != 1) { // Blanco (2), Rojo (0), Azul (1)
        giro_horario(grid, p, 0); // Giro horario en la cara Roja
        giro_antihorario(grid, p, 1); // Giro antihorario en la cara Azul
    }
    while (grid[47] != 2 || grid[38] != 0 || grid[27] != 3) { // Blanco (2), Rojo (0), Verde (3)
        giro_horario(grid, p, 0); // Giro horario en la cara Roja
        giro_antihorario(grid, p, 3); // Giro antihorario en la cara Verde
    }
    while (grid[53] != 2 || grid[29] != 1 || grid[20] != 5) { // Blanco (2), Azul (1), Naranja (5)
        giro_horario(grid, p, 1); // Giro horario en la cara Azul
        giro_antihorario(grid, p, 5); // Giro antihorario en la cara Naranja
    }
    while (grid[51] != 2 || grid[9] != 5 || grid[19] != 3) { // Blanco (2), Naranja (5), Verde (3)
        giro_horario(grid, p, 5); // Giro horario en la cara Naranja
        giro_antihorario(grid, p, 3); // Giro antihorario en la cara Verde
    }

    // Resolver la segunda capa (capa media)
    Serial.println("Resolviendo segunda capa...");

    // Paso 3: Colocar las aristas de la segunda capa
    while (grid[12] != 0 || grid[21] != 3) { // Rojo (0) y Verde (3)
        giro_horario(grid, p, 0); // Giro horario en la cara Roja
        giro_horario(grid, p, 3); // Giro horario en la cara Verde
        giro_antihorario(grid, p, 0); // Giro antihorario en la cara Roja
        giro_antihorario(grid, p, 3); // Giro antihorario en la cara Verde
    }
    while (grid[14] != 0 || grid[30] != 1) { // Rojo (0) y Azul (1)
        giro_horario(grid, p, 0); // Giro horario en la cara Roja
        giro_horario(grid, p, 1); // Giro horario en la cara Azul
        giro_antihorario(grid, p, 0); // Giro antihorario en la cara Roja
        giro_antihorario(grid, p, 1); // Giro antihorario en la cara Azul
    }
    while (grid[32] != 1 || grid[23] != 5) { // Azul (1) y Naranja (5)
        giro_horario(grid, p, 1); // Giro horario en la cara Azul
        giro_horario(grid, p, 5); // Giro horario en la cara Naranja
        giro_antihorario(grid, p, 1); // Giro antihorario en la cara Azul
        giro_antihorario(grid, p, 5); // Giro antihorario en la cara Naranja
    }
    while (grid[34] != 3 || grid[23] != 5) { // Verde (3) y Naranja (5)
        giro_horario(grid, p, 3); // Giro horario en la cara Verde
        giro_horario(grid, p, 5); // Giro horario en la cara Naranja
        giro_antihorario(grid, p, 3); // Giro antihorario en la cara Verde
        giro_antihorario(grid, p, 5); // Giro antihorario en la cara Naranja
    }

    // Resolver la tercera capa (capa superior)
    Serial.println("Resolviendo tercera capa...");

    // Paso 4: Orientar las aristas de la tercera capa (formar una cruz)
    while (grid[1] != 4 || grid[3] != 4 || grid[5] != 4 || grid[7] != 4) { // Amarillo (4)
        giro_horario(grid, p, 4); // Giro horario en la cara Amarilla
        giro_horario(grid, p, 2); // Giro horario en la cara Blanca
        giro_antihorario(grid, p, 4); // Giro antihorario en la cara Amarilla
        giro_antihorario(grid, p, 2); // Giro antihorario en la cara Blanca
    }

    // Paso 5: Permutar las aristas de la tercera capa
    while (grid[12] != 0 || grid[21] != 3 || grid[30] != 1 || grid[39] != 5) { // Rojo (0), Verde (3), Azul (1), Naranja (5)
        giro_horario(grid, p, 0); // Giro horario en la cara Roja
        giro_horario(grid, p, 1); // Giro horario en la cara Azul
        giro_antihorario(grid, p, 0); // Giro antihorario en la cara Roja
        giro_antihorario(grid, p, 1); // Giro antihorario en la cara Azul
    }

    // Paso 6: Orientar las esquinas de la tercera capa
    while (grid[45] != 4 || grid[47] != 4 || grid[51] != 4 || grid[53] != 4) { // Amarillo (4)
        giro_horario(grid, p, 4); // Giro horario en la cara Amarilla
        giro_horario(grid, p, 0); // Giro horario en la cara Roja
        giro_antihorario(grid, p, 4); // Giro antihorario en la cara Amarilla
        giro_antihorario(grid, p, 0); // Giro antihorario en la cara Roja
    }

    // Paso 7: Permutar las esquinas de la tercera capa
    while (grid[36] != 0 || grid[27] != 3 || grid[18] != 1 || grid[9] != 5) { // Rojo (0), Verde (3), Azul (1), Naranja (5)
        giro_horario(grid, p, 0); // Giro horario en la cara Roja
        giro_horario(grid, p, 1); // Giro horario en la cara Azul
        giro_antihorario(grid, p, 0); // Giro antihorario en la cara Roja
        giro_antihorario(grid, p, 1); // Giro antihorario en la cara Azul
    }

    Serial.println("Cubo resuelto.");
}

void setup() {
    Serial.begin(9600);
    // Generar cubo rubik.
    int grid[9*6];
    // Rellenar colores: Rojo (0) - Azul (1) - Blanco (2) - Verde (3) - Amarillo (4) - Naranja (5).
    for (int c = 0; c < 6; c++) {
        for (int i = 0; i < 9; i++) {
            grid[c * 9 + i] = c;
        }
    }

    // Lista de posiciones relativas para un giro horario <0,C1,5,C2>.
    int pos[12 * 4]{
    	2, 5, 8,  2, 5, 8,  6, 3, 0,  0, 3, 6,  // eje == 1 (fila 0).
	0, 1, 2,  2, 5, 8,  0, 1, 2,  6, 3, 0,  // eje == 2 (fila 1).
	0, 3, 6,  8, 5, 2,  2, 5, 8,  6, 3, 0,  // eje == 3 (fila 2).
	6, 7, 8,  8, 5, 2,  8, 7, 6,  0, 3, 6   // eje == 4 (fila 3).
    };

    // Puntero a la grilla.
    int* grid_ptr = grid;
    // Puntero al arreglo de posiciones.
    int* pos_ptr = pos;
}

void loop() {
    // Nada aquí
}
