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
  new->next = NULL;
  return new;
}

/*
Funca que adiciona recursivamente um no a lista ligada ja na posicao ordenada.
Recebe o ponteiro do primeiro elemento da lista e o valor a ser adicionado
*/
void insert_node(Node **list, int info){
  /*Se o valor ja esta na lista, nao faz nada*/
  if((*list)->next != NULL && (*list)->next->value == info);
  /*Enquanto o elemento seguinte da lista nao for maior que o info nem nulo, avanca nela*/
  else if(((*list)->next == NULL || (*list)->next->value > info)){
    Node *new = new_node(info);
    new->next = (*list)->next;
    (*list)->next = new;
  }else if((*list)->next != NULL)
    insert_node(&(*list)->next, info);
}

/*
Remove recursivamente o elemento que tem valor == info
Recebe como parametro o valor buscado e o header da lista
*/
void delete(Node **list, int info){
  if((*list)->next == NULL)
    return;
  /*Enquanto o valor do proximo elemento nao for o desejado, avanca na lista*/
  else if((*list)->next->value == info){
    Node *aux = (*list)->next->next;
    free((*list)->next);
    (*list)->next = aux;
  /*Se chegamos no final da lista sem achar o valor desejado, simplesmente deixamos a lista como esta*/
  }
  else if((*list)->next != NULL)
    delete(&(*list)->next, info);
}

/*
Funcao que busca recursivamente um valor em uma lista
Recebe como parametro o header da lista e o valor buscado
Nao retorna nada, mas imprime "sim" se o valor estiver e "nao" caso contrario
*/
void search(Node *list, int info){
  if(list == NULL)
    printf("NAO\n");
  else if(list->value == info)
    printf("SIM\n");
  else
    search(list->next, info);
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

/*
Funcao que realiza a uniao entre lista1 e lista2 recursivamente, colocando o resultado em lista1
Recebe o primeiro elemento de lista1 e lista2 como parametros
*/
void join(Node **list1, Node *list2){
  if(list2 != NULL){
    insert_node(&(*list1), list2->value);
    join(list1, list2->next);
  }
}

/*
Funcao que realiza a intersecao de 2 grupos recursivamente e guarda no grupo 1
Recebe lista1 e lista2 como parametros
*/
void intersection(Node **list1, Node *list2){
  if((*list1)->next != NULL && list2->next != NULL){
    if((*list1)->next->value < list2->next->value || list2->next == NULL){
      intersection(&(*list1)->next, list2);
      Node *aux = (*list1)->next->next;
      free((*list1)->next);
      (*list1)->next = aux;
    }else if(list2->next->value < (*list1)->next->value)
      intersection(&(*list1), list2->next);
    else
      intersection(&(*list1)->next, list2->next);
  }else if(list2->next == NULL){
    while((*list1)->next != NULL){
      Node *aux = (*list1)->next->next;
      free((*list1)->next);
      (*list1)->next = aux;
      }
    }
}

/*
Funcao que realiza a subtracao entre os grupos 1 e 2 e salva no grupo 1
Recebe lista1 e lista2 como parametros
*/
void subtraction(Node **list1, Node *list2){
  if((*list1)->next != NULL && list2->next != NULL){
    if((*list1)->next->value == list2->next->value){
      subtraction(&(*list1)->next, list2->next);
      Node *aux = (*list1)->next->next;
      free((*list1)->next);
      (*list1)->next = aux;
    }else if((*list1)->next->value < list2->next->value)
      subtraction(&(*list1)->next, list2);
    else
      subtraction(&(*list1), list2->next);
  }
}

/*
Funcao que libera todo o espaco alocado para as listas ligadas recursivamente
Recebe o header da lista como parametro apenas
*/
void free_list(Node **list){
  if((*list)->next == NULL)
    free((*list));
  else{
    free_list(&(*list)->next);
    free((*list));
  }
}

int main(){
  int i = 1, element, group;
  char operation;
  Node *group1, *group2;
  group1 = new_node(-1);
  group2 = new_node(-1);
  Node* list[] = {group1, group2};

  while(i){
    scanf(" %c", &operation);
    switch(operation){
      case 'i':
        scanf(" %d %d", &element, &group);
        insert_node(&list[group - 1], element);
        break;
      case 'p':
        scanf(" %d %d", &element, &group);
        search(list[group - 1], element);
        break;
      case 'r':
        scanf(" %d %d", &element, &group);
        delete(&list[group - 1], element);
        break;
      case 'u':
        join(&list[0], list[1]->next);
        break;
      case 'x':
        intersection(&list[0], list[1]);
        break;
      case 'b':
        subtraction(&list[0], list[1]);
        break;
      case 's':
        i = 0;
        break;
    }
    printf("{"); print(list[0]->next); printf("}\n");
    printf("{"); print(list[1]->next); printf("}\n");
  }
  free_list(&list[0]);
  free_list(&list[1]);
  return 0;
}
