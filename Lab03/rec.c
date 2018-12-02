#include <stdio.h>

int main(){
  FILE *arq = fopen("read.txt", "r");
  char receptora = ' ';
  int contador = 0;
  while(receptora != EOF){
    receptora = fgetc(arq);
    if(receptora == '\n')
      contador++;
  }
  printf("%d", contador);
  fclose(arq);
  return 0;
}
