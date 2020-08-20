#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Struct de no para cada elemento da lista, que possui um ponteiro para o elemento
anaterior e um ponteiro para o posterior, alem da informacao
*/
typedef struct Node{
  char name[21];
  struct Node *next;
  struct Node *previous;
}Node;

void print_final(Node *list);
Node *create_Node(char *name);
Node *receive(Node *list);
void free_Space(Node *list);
Node *print(int position, Node *list, int direction);
Node *insert_in_position(int position, char name[], Node *list, int direction);
Node *delete_position(int position, Node *list, int direction);
Node *change_positions(char name1[], char name2[], Node *list);
Node *find_Node(char name[], Node *list);

int main(){
  int quit = 0, position, direction = 1; /*direction 1 = sentido inicial, direction 0 = sentido oposto*/
  char operation, action[10], name1[21], name2[21];
  Node *list = NULL; /*Inicializa a lista vazia*/
  list = receive(list);
  char command[20];
  while(!quit){
    if(scanf(" %d", &position)){
      scanf(" %c", &operation);
      switch(operation){
        case '+':
          scanf(" %s", name1);
          list = insert_in_position(position, name1, list, direction);
          break;
        case '-':
          list = delete_position(position, list, direction);
          break;
        case '!':
          list = print(position - 1, list, direction);
          break;
      }
    }else if(scanf(" %s", action)){
      switch(action[0]){
        case 't':
          scanf(" %s %s", name1, name2);
          list = change_positions(name1, name2, list);
          break;
        case 'm':
          scanf(" %s", action);
          direction = !direction;
          break;
        case 's':
          quit = 1;
          break;
      }
    }

  }
  print_final(list);
  free(list);
  return 0;
}

/*
Funcao que cria um novo no, ja colocando sua info como o nome
*/
Node *create_Node(char name[]){
  Node *new = (Node*) malloc(sizeof(Node));
  if(!new)
    exit(1);
  strcpy(new->name, name);
  return new;
}

/*
Funcao que recebe os elementos da lista, insere-os em uma lista ligada dupla e
circular e retorna o primeiro elemento recebeido como "inicio" da lista
*/
Node *receive(Node *list){
  char leter, name[21];
  do{
    scanf("%s", name);
    list = insert_in_position(1, name, list, 1);
    leter = getchar();
  }while(leter != '\n');

  return list;
}

/*
Imprime a lista inteira ao final do programa
*/
void print_final(Node *list){
  Node *aux = list;
  if(aux != NULL){
      do{
        printf("%s ", aux->name);
        aux = aux->next;
      }while(aux->next != list);
      printf("%s", aux->name);
  }
}

/*
Imprime o elemento da lista na posicao indicada
*/
Node *print(int position, Node *list, int direction){
  if(list != NULL){
    int i;
    if(direction)
      for(list, i = 0; i < position; i++, list = list->next);
    else
      for(list, i = 0; i < position; i++, list = list->previous);
    printf("%s\n", list);
  }
  return list;
}

/*
Libera a memoria alocada para os elementos da lista
*/
void free_Space(Node *list){
  Node *aux = list;
  list = list->next;
  if(aux != NULL){
    do{
      list = list->next;
      free(list->previous);
    }while(aux != list);
    free(list->previous);
    free(list);
  }
}

/*
Insere o item na posicao determinada, retornando o item inserido
*/
Node *insert_in_position(int position, char name[], Node *list, int direction){
  Node* new = create_Node(name);
  if (list == NULL){
    new->next = new;
    new->previous = new;
    return new;
  }
  int i;
  if(direction)
    for(list, i = 1; i < position; i++, list = list->next);
  else
    for(list, i = 1; i < position; i++, list = list->previous);
  list->previous->next = new;
  new->previous = list->previous;
  list->previous = new;
  new->next = list;
  return new;
}

/*
Deleta o elemento da posicao especificada, retornando o elemento seguinte
*/
Node *delete_position(int position, Node *list, int direction){
  int i;
  Node *aux;
  if(!list)
    return list;
  if(direction){
    for(list, i = 0; i < position; i++, list = list->next);
    aux = list->previous;
    list->previous->previous->next = list;
    list->previous = list->previous->previous;
  }else{
    for(list, i = 0; i < position; i++, list = list->previous);
    aux = list->next;
    list->next->next->previous = list;
    list->next = list->next->next;
  }
  free(aux);
  return list;
}

/*
Funcao que encontra um nome na lista e retorna o no contendo esse nome   
 */
Node *find_Node(char name[], Node *list){
	Node *aux = list;
	do{
		if(!strcmp(name, aux->name))
			return aux;
		aux = aux->next;
	}while(aux != list);
	return NULL;
}

/*
Troca os elementos com os nomes recebidos, retornando o elemento que estava no
inicio da lista antes da troca
*/
Node *change_positions(char name1[], char name2[], Node *list){
	Node *firstElement = find_Node(name1, list);
 	Node *secondElement = find_Node(name2, list);
	Node *aux;
	if(firstElement && secondElement){
		aux = firstElement->next;
		firstElement->next = secondElement->next;
		secondElement->next = aux;
		aux = firstElement->previous;
		printf("\n%s\n", firstElement->previous->name);	
		firstElement->previous = secondElement->previous;
		printf("\n%s\n", firstElement->previous->name);	
		secondElement->previous = aux;
		printf("\n%s\n", secondElement->previous->name);	
	}
	return list;	
}
