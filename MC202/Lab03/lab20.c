#include <stdio.h>
#include <stdlib.h>

#define INPUT "read.txt"
#define OUTPUT "write.txt"

/*
Struct contendo todos os dados da pessoa cadastrada
*/
typedef struct{
  long int cpf;
  char nome[41];
  char email[31];
  int idade;
}cadastro;

/*
Funcao que auxilia o sort encontrando o indice do menor valor
*/
int smallestIndex(cadastro *vetor, int tamanho, int posicao){
  int index = posicao, i;
  for(i = posicao + 1; i < tamanho; i++){
    if(vetor[i].idade < vetor[i - 1].idade)
      index = i;
    else if(vetor[i].idade == vetor[i - 1].idade)
      if(vetor[i].cpf < vetor[i - 1].cpf)
        index = i;
    }
  return index;
}

/*
Funcao que ordena o vetor em ordem crescente de idade e em caso de idades iguais, usa o cpf.
Utiliza o algoritmo selection sort para o sort.
*/
void sort(cadastro *vetor, int tamanho){
  int i, menor;
  cadastro aux;
  for(i = 0; i < tamanho - 1; i++){
    menor = smallestIndex(vetor, tamanho, i);
    aux = vetor[i];
    vetor[i] = vetor[menor];
    vetor[menor] = aux;
  }
}

/*
Funcao que recebe um vetor e seu tamanho e imprime em um arquivo OUTPUT seu resultado.
Essa funcao ja libera os espacos de memoria alocados para as variaveis do tipo cadastro e vetores.
*/
void write(cadastro *vetor, int tamanho){
  int i;
  FILE *arq = fopen(OUTPUT, "w");

  for(i = 0; i < tamanho; i++)
    fprintf(arq, "%ld, %s, %s, %d\n", vetor[i].cpf, vetor[i].nome, vetor[i].email, vetor[i].idade);

  fclose(arq);
}

/*
Funcao que recebe os valores de um arquivo de input e os salva em variaveis do tipo cadastro,
que serao salvas em um vetor. Recebe como parametros um vetor no qual serao salvos os cadastros
e um int tamanho no qual sera guardado o numero de pessoas cadastradas (ambos os parametros sao ponteiros).
*/
void read(cadastro *vetor, int *tamanho){
  int numero = 0;
  char receptora = ' ';

  FILE *arq = fopen(INPUT, "r");

  /*Encontra o numero de pessoas a serem cadastradas*/
  while(receptora != EOF){
    receptora = fgetc(arq);
    if(receptora == '\n')
      numero++;
  }

  tamanho = &numero;
  rewind(arq);

  /*Aloca dinamicamente esse vetor e recebe em cada posicao o cadastro de uma dessas pessoas*/
  vetor = malloc(numero * sizeof(cadastro));
  int i;
  for(i = 0; i < numero; i++)
    fscanf(arq, "%ld, %s, %s, %d", &vetor[i].cpf, vetor[i].nome, vetor[i].email, &vetor[i].idade);

  fclose(arq);
}

int main(){
  int *tamanho;
  cadastro *vetor;

  read(vetor, tamanho);
  sort(vetor, *tamanho);
  write(vetor, *tamanho);

  free(vetor);
  return 0;
}
