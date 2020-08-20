#include <stdio.h>
#include <stdlib.h>

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
int decrypt(int mat[4]){
  int i, sum = 0, local;
  for(i = 0, local = 6; i <= 3; i++, local -= 2){
    sum = sum | bitwise(mat[i], local);
  }
  return sum;
}

int main(){
  /*Recebemos o tamanho da matriz e do maximo*/
  int linhas = 0, colunas = 0, max;
  scanf("P2\n %d %d\n", &colunas, &linhas);
  scanf(" %d\n", &max);

  /*Encontra cada letra encriptada, lendo os numeros da imagem em grupos
  de 4 (um caracter por iteracao do while)*/
  int i, j = 0, contadora = 0, frase[(linhas * colunas)/4], character[4];
  do{
    for(i = 0; i < 4; i++){
      scanf(" %d", &character[i]);
      contadora++;
    }
    frase[j] = decrypt(character);
    j++;
  }while(frase[j-1]);

  /*Le os valores nao usados da imagem*/
  char inutil;
  while(contadora < (colunas * linhas)){
    scanf(" %c", &inutil);
    contadora++;
  }

  /*imprime a frase obtida*/
  for(i = 0; frase[i]; i++)
    printf("%c", frase[i]);
  return 0;
}
