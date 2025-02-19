#include <iostream>

void giro_horario(int* grid, int* p, int eje){
  int aux[3];
  int rec;
  
  // Cara roja (0) o naranja (5).
  if(eje == 0 || eje == 5){
    // Respaldar los valores de la primera cara en un array auxiliar.
    for(int i=0; i<3; i++){
      aux[i] = grid[9 + (eje==0 ? i : 8-i)];
    }
    // Sobreescribir la cara actual con los valores de la siguiente cara.
    for(int c=1; c<4; c++){
      for(int i=0; i<3; i++){
        grid[c*9 + (eje==0 ? i : 8-i)] = grid[(c+1)*9 + (eje==0 ? i : 8-i)];
      }
    }
    // Asignar los valores guardados a la última cara.
    for(int i=0; i<3; i++){
      grid[4*9 + (eje==0 ? i : 8-i)] = aux[i];
    }
    
  // Azul (1), Blanco (2), Verde(3) o Amarillo (4).
  } else{
    
    int c;
    // p[]: <0,C1,5,C2>.
    for(int i = 0; i<3; i++){
      // Respaldar los valores de la cara '0' (Rojo).
      aux[i] = grid[ p[(eje-1)*12 + i + 3*0] ];
		std::cout << "Respaldado en " << i << ": " << aux[i] << std::endl;
      // "C1".
      c = (eje+2)%4+1;
      //[0 <- c1].
      grid[ p[(eje-1)*12 + 3*0 + i] ] = grid[ c*9 + p[(eje-1)*12 + 3*1 + i] ];
      // [c1 <- 5].
      grid[ c*9 + p[(eje-1)*12 + ((eje==3 || eje==4) ? (2-i) : i) + 3*1] ] = grid[ 5*9 + p[(eje-1)*12 + i + 3*2] ];
      // "C2".
      c = (eje%4+1);
      // [5 <- c2].
      grid[ 5*9 + p[(eje-1)*12 + ((eje==1 || eje==4) ? (2-i) : i) + 3*2] ] = grid[ c*9 + p[(eje-1)*12 + i + 3*3] ];
		//std::cout << grid[ c*9 + p[(eje-1)*12 + i + 3*3] ] << std::endl;
      // [c2 <- aux].
      // Última ronda, empleando los valores auxiliares.
      grid[ c*9 + p[(eje-1)*12 + ((eje==2 || eje==3) ? (2-i) : i) + 3*3] ] = aux[((eje==1 || eje==2) ? (2-i) : i)];
    }   
  }

  // Reservar el primer valor de la cara base.
  rec = grid[eje*9];
  // Rotar cara base.
  for(int j=0; j<3; j++){
    for(int i=0; i<3; i++){
      // Intercambiar posiciones.
      if(i==2 && j==2){
        grid[eje*9 + i + j*3] = rec;
      } else{
        grid[eje*9 + j*3 + (2-i)] = grid[eje*9 + i + j*3];
      }
    }
  }
}

void print_grid(int* grid){
	for(int c = 0; c < 6; c++){
		std::cout << " --- " << c << " ---" << std::endl;
		for(int i = 0 ; i < 3; i++){
			for(int j = 0; j < 3; j++){
				std::cout << grid[c*9 + i*3 + j] << " ";
			}
			std::cout << std::endl;
		}
	}
}

int main(int argc, char* argv[]){
  // Generar cubo rubik.
  int grid[9*6];
  
  // Rellenar colores: Rojo (0) - Azul (1) - Blanco (2) - Verde (3) - Amarillo (4) - Naranja (5)
  for(int c = 0; c<6; c++){
    for(int i = 0; i<9; i++){
      grid[c*9 + i] = c;
    }
  }

// Lista de posiciones relativas para un giro horario.
// <0,C1,5,C2>.
int pos[12*4]{
    2,5,8, 2,5,8, 6,3,0, 0,3,6,  // eje == 1 (fila 0).
    0,1,2, 2,5,8, 0,1,2, 6,3,0,  // eje == 2 (fila 1).
    0,3,6, 8,5,2, 2,5,8, 6,3,0,  // eje == 3 (fila 2).
    6,7,8, 8,5,2, 8,7,6, 0,3,6   // eje == 4 (fila 3).
};
  // Puntero a la grilla, para usar como valor de entrada.
  int* grid_ptr = grid;
  // Puntero al array de posiciones.
  int* pos_ptr = pos;

  print_grid(grid_ptr);

  int eje = 2;
  giro_horario(grid_ptr, pos_ptr, eje);
  
  print_grid(grid_ptr);

  return 0;
}
