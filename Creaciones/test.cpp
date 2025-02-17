
void giro_horario(int* grid, int eje){
  int aux[3];
  // Cara roja (0) o naranja (5).
  if(eje == 0 || eje == 5){
    for(int c=1; c<5; c++){
      for(int i=0; i<3; i++){
        // Guardar los valores en un array auxiliar.
        aux[i] = grid[c*9 + (eje==0 ? i : 8-i)];
      }
      // Asignar los valores a la siguiente cara,
      grid[(c==4 ? 1 : c+1)*9 + (eje==0 ? i : 8-i)] = aux[i];
    }
  }
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
