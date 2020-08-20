#include <stdio.h>

void readMatrix(int mat[][96]){
    for(int i = 0; i < 128; i++){
      for(int j = 0; j < 96; j++){
        if(i == 0 || i == 127 || j == 0 || j == 95){
          mat[i][j] = 0;
        }else{
          scanf(" %d ", mat[i][j]);
        }
      }
    }
}

int main(){
  int i = 0;
  int matriz[128][96];
  readMatrix(matriz);
  while(i < 128){
    printf("%d", matriz[i][1]);
    i++;
  }


  return 0;
}
