#include <stdio.h>
#include <stdlib.h>

/*Completa a matriz com os valores lidos*/
void complete(int *mat, int lin, int col){
  int i;
  for(i = 0; i < (lin * col); i++)
      scanf(" %d", &mat[i]);
}


/*Funcao recebe um int e realiza bitwise para retirar os dois ultimos numeros
binarios e posicionalos no local onde ficarao no binario final*/
int bitwise(int a, int local){
  /* Pega os dois ultimos numeros do binario*/
  a = a & 3;

  /*shifta eles para a posicao desejada*/
  a = a << local;
  return a;
}

/*Funcao que retorna o char codificado em uma lista de 4 numeros
na forma de um inteiro usando bitwise */
int decrypt(int mat[4], int posicao){
  int i, sum = 0, local;
  for(i = posicao, local = 6; i <= posicao + 3; i++, local -= 2){
    sum = sum | bitwise(mat[i], local);
  }
  return sum;
}

int main(){

  /*Recebemos o tamanho da matriz e alocamos ela dinamicamente*/
  int linhas = 0, colunas = 0;
  scanf("P2\n %d %d\n", &colunas, &linhas);
  int *matriz;
  matriz = malloc((linhas * colunas) * sizeof(int));

  /*Recebemos o valor de maximo*/
  int max;
  scanf(" %d\n", &max);

  /*inicializamos a matriz com os valores*/
  complete(matriz, linhas, colunas);


  /*Encontra cada letra encriptada*/
  int i = 0, j = 0, frase[(linhas * colunas)/4];
  do{
    frase[j] = (char)decrypt(matriz, i);
    i = i + 4;
    j = j + 1;
  }while(i < (colunas * linhas) && frase[j - 1]);

  for(i = 0; frase[i]; i++)
    printf("%c", frase[i]);

  free(matriz);

  return 0;
}
