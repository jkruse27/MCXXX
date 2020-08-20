#include <stdio.h>
#include <stdlib.h>

/*
Struct de cada no
*/
typedef struct Node{
  int value;
  struct Node *next;
}Node;

/*
Funcao cria um no, adiciona seu valor (recebido como parametro) e retorna ele
*/
Node *new_node(int info){
  Node *new = (Node*) malloc(sizeof(Node));
  if(new == NULL)
    exit(1);
  new->value = info;
  return new;
}

/*
Funca que adiciona recursivamente um no a lista ligada ja na posicao ordenada.
Recebe o ponteiro do primeiro elemento da lista e o valor a ser adicionado
*/
void insert_node(Node **list, int info){
  /*Enquanto o elemento seguinte da lista nao for maior que o info nem nulo, avanca nela*/
  if(((*list)->next == NULL || (*list)->next->value > info) && (*list)->value <= info){
    Node *new = new_node(info);
    new->next = (*list)->next;
    (*list)->next = new;
  }
  else
    insert_node(&(*list)->next, info);
}

/*
Imprime a lista recursivamente
Recebe como parametro o primeiro elemento da lista
*/
void print(Node *list){
  if(list != NULL){
    printf("%d", list->value);
    if(list->next != NULL)
      printf(",");
    print(list->next);
  }
}
int main(){
 Node *a;
 int b;
 a = new_node(-1);
 a->next = NULL;
 while(scanf(" %d", &b)){
   insert_node(&a, b);
   printf("\n");
   print(a);
   printf("\n");
 }
 return 0;
 }
