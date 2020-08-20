#include <stdio.h>

typedef struct{
  long int cpf;
  char nome[41];
  char email[31];
  int idade;
}oi;

int smallestIndex(int vetor[11], int comprimento, int posicao){
  int index = posicao, i;
  for(i = posicao + 1; i < comprimento; i++){
    if(vetor[i] < vetor[index])
      index = i;
    }
  return index;
  }


/*
Realiza a ordenacao da lista utilizando selection sort e a idade como
principal prioridade e usando o cpf como segundo parametro em caso de igualdade
*/
void selectionSort(int vetor[11], int comprimento){
  int i, menor;
  int aux;
  for(i = 0; i < comprimento - 1; i++){
    menor = smallestIndex(vetor, comprimento, i);
    aux = vetor[i];
    vetor[i] = vetor[menor];
    vetor[menor] = aux;
  }
}

int main(){
  int vetor[] = {1, 5, 8, 1000, 223, 54, 234, 2, 3, 6, 22};
  int *a;
  *a = 11;
  selectionSort(vetor, *a);
  for(int i = 0; i < 11; i++)
    printf("\n%d", vetor[i]);
  return 0;
}
