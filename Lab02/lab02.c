#include <stdio.h>
#include <stdlib.h>

/*Recebe um binario e transforma em inteiro*/
int toInteger(int binary){
  int result = 0, multiplier = 1;
  while(binary){
    result = result + (multiplier * (binary % 10));
    binary = binary / 10;
    multiplier = multiplier * 2;
  }
  return result;
}

/*Funcao que recebe um inteiro e retorna os ultimos dois digitos de seu binario*/
int toBinary(int a){
  int binary = 0, factor, i;
  for(i = 0, factor = 1; i < 2; i++, factor *= 10){
    binary = binary + (factor * (a % 2));
    a = a / 2;
  }
  return binary;
}

/*Completa a matriz com os valores lidos*/
void complete(int *mat, int lin, int col){
  int i;
  for(i = 0; i < (lin * col); i++)
      scanf(" %d", &mat[i]);
}

/*Funcao que recebe uma posicao da matriz e retorna o char codificado em 4 numeros
na forma de um inteiro*/
int decrypt(int *mat, int posicao){
  int i, multiplicator = 1, sum = 0;
  for(i = posicao + 3; i >= posicao; i--){
    sum = sum + (multiplicator * toBinary(mat[i]));
    multiplicator = multiplicator * 100;
  }
  sum = toInteger(sum);
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
