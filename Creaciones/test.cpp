
void giro_horario(int* grid, int eje){
  int aux[3];
  
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
  // Azul (1), Blanco (2), Verde(3), Amarillo (4).
  } else{
    int c;
    int p[3];
    for(int i = 0; i<3; i++){
      // Respaldar los valores de la cara '0' (Rojo).
      aux[i] = grid[i];
      // Primera ronda de traslaciones.
      c = (eje+2)%4+1;
      //[c*9 -> 0]
      grid[i] = grid[ c*9 + p[i] ];
      // [5 -> c*9]
      grid[ c*9 + p[i] ] =  grid[ c*9 + p[i] ]
      // Tercera ronda.
      c = (eje%4+1);
      // [c*9 -> 5]
      // Última ronda, empleando los valores auxiliares.
      // [aux -> c*9]
      
      if(eje==1){
        grid[i] = grid[c*];
      }

      
      // Rotación lateral del cubo.
       grid[i] = grid[ ((c+2)%4+1)*9 + A ];
       grid[ ((c+2)%4+1)*9 + A ] = grid[5*9 + B];
       grid[5*9 + B] = grid[ (c%4+1)*9 + C ];
      grid[ (c%4+1)*9 + C ] = aux[i];
    }   
  }

  if(){}
}

int main(){
  int grid[56];
  // Colores: Rojo (0) - Azul (1) - Blanco (2) - Verde (3) - Amarillo (4) - Naranja (5)
  for(int c = 0; c<6; c++){
    for(int i = 0; i<9; i++){
      grid[c*9 + i] = c;
    }
  }
  int* ptr = grid;
  
  return 0;
}






  
void giro_horario(int* position_grid, int eje){
  int aux[3];
  int p;
  // Cara roja (0) o naranja (5).
  if(eje == 0 || eje == 5){
    for(c=1; c<5; c++){
      for(int i=0; i<3; i++){
        aux[i] = (*position)[c*9+(eje==0 ? i : 8-i)];
        (*position)[(c==4 ? 1 : c+1)*9+(eje==0 ? i : 8-i)] = aux[i];
      }
    }
    
  // Otros colores (1-4).
  } else{
    int suc[] = {5, (eje>2 ? abs(2-eje) : eje+2), 0, eje};
    for(int c = 0; c<4; c++){
      for(int i = 0; i<3; i++){
        aux[i] = (*position)[suc[c]*9+i];
      }
    }
  }
}

void giro_horario(int* position_grid, int eje){
  int aux[3], p;
  if(eje == 0 || eje == 5){
    for(int c=1; c<5; c++){
      for(int i=0; i<3; i++){
        aux[i] = (*position)[c*8 + (eje==0 ? i : 8-i)];
        (*position)[(c<4 ? c+1 : 1)*8 + (eje==0 ? i : 7-i)] = aux[i];
      }
    }
  } else{
    int suc[] = {5, (eje>2 ? abs(3-eje) : eje+2), 0};
    for(int c=0; c<4; c++){
      
    }
  }
}
