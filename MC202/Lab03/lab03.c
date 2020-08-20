#include <stdio.h>
#include <stdlib.h>

/*
Struct contendo a idade, o nome, o cfp e o email da pessoa cadastrada
*/
typedef struct{
  long int cpf;
  char nome[41];
  char email[31];
  int idade;
}cadastro;

/*
Encontra o menor indice para o selection sort
*/
int smallestIndex(cadastro *vetor, int comprimento, int posicao){
  int index = posicao, i;
  for(i = posicao + 1; i < comprimento; i++){
    if(vetor[i].idade < vetor[index].idade)
      index = i;
    else if(vetor[i].idade == vetor[index].idade)
      if(vetor[i].cpf < vetor[index].cpf)
        index = i;
    }
  return index;
  }

/*
Realiza a ordenacao da lista utilizando selection sort e a idade como
principal prioridade e usando o cpf como segundo parametro em caso de igualdade
*/
void selectionSort(cadastro *vetor, int comprimento){
  int i, menor;
  cadastro aux;
  for(i = 0; i < comprimento - 1; i++){
    menor = smallestIndex(vetor, comprimento, i);
    aux = vetor[i];
    vetor[i] = vetor[menor];
    vetor[menor] = aux;
  }
}

/*
Imprime a lista ordenada
*/
void print(cadastro *vetor, int comprimento){
  int i;
  for(i = 0; i < comprimento; i++)
    printf("%011ld, %s, %s, %d \n", vetor[i].cpf, vetor[i].nome, vetor[i].email, vetor[i].idade);
}

/*
Recebe os cadastros e aloca eles em uma lista que dobra de tamanho quando fica cheia
Recebe um ponteiro para o tamanho como parametro e retorna o a lista
*/
cadastro* receive(int **comprimento){
  int i = 1;
  cadastro *vetor;
  vetor = malloc(i * sizeof(cadastro));
  while(scanf(" %ld , %[^,] , %[^,] , %d", &vetor[i-1].cpf, vetor[i-1].nome, vetor[i-1].email, &vetor[i-1].idade) != EOF)
      vetor = realloc(vetor, (++i) * sizeof(cadastro));

  /*Altera o valor de tamanho atraves do ponteiro*/
  **comprimento = i - 1;
  return vetor;
}

int main(){
  cadastro *lista;
  int *tamanho;
  lista = receive(&tamanho);
  selectionSort(lista, *tamanho);
  print(lista, *tamanho);
  free(lista);
  return 0;
}
