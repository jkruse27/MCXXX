/*Joao Gabriel Segato Kruse RA:218615*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 4
#define MAX_ARRAY 5

typedef struct{
  int number;
  char information[53];
}Person;

typedef struct{
  int top;
  Person *list[MAX_STACK + 1];
}Stack;

typedef struct Queue{
  Person *info;
  struct Queue *first;
  struct Queue *last;
  struct Queue *next;
}Queue;

void print(Stack *stacks[], Queue *queue, int topArray);
void final_print(Stack *stacks[], Queue *queue, int lastPoint);
Queue* receive(Queue *queue, int number, int *totalCounter);
Queue* insert_in_queue(Queue *queue, Person *info);
void remove_from_queue(Stack *stacks[], Queue **queue, int number, int *topArray, int *lastPoint);
void insert_in_stack(Stack *stacks[], Queue *queue, int *topArray, int *lastPoint);
void remove_from_stack(Stack *stacks[], int *topArray, int number);
void free_space(Stack *stacks[], Queue **queue, int lastPoint);

int main(){
  int quit = 0, topArray = -1, lastPoint = -1, totalCounter = 0;
  char operation;
  int times;
  Queue *queue = NULL;
  Stack* stacks[MAX_ARRAY + 1];
  while(!quit){
    operation = getchar();
    switch(operation){
      case 'Q':
        operation = getchar();
        switch(operation){
          case 'I':
            scanf(" %d", &times);
            queue = receive(queue, times, &totalCounter);
            break;
          case 'R':
            scanf(" %d", &times);
            remove_from_queue(stacks, &queue, times, &topArray, &lastPoint);
            operation = getchar();
            break;
        }
        break;
      case 'S':
        operation = getchar();
        scanf(" %d", &times);
        remove_from_stack(stacks, &topArray, times);
        operation = getchar();
        break;
      case 'P':
        print(stacks, queue, topArray);
        operation = getchar();
        break;
      case 'D':
        final_print(stacks, queue, lastPoint);
        quit = 1;
        break;
    }
  }
  free_space(stacks, &queue, lastPoint);
  return 0;
}

/*
Imprime as pilhas e a fila
*/
void print(Stack *stacks[], Queue *queue, int topArray){
  int i, j = 0;
  Queue *aux = queue;
  printf("[Q]");
  while(aux != NULL){
    printf("%d,", aux->info->number);
    aux = aux->next;
  }
  printf("\n");
  for(i = 0; i <= 5; i++){
    printf("[S%d]", i + 1);
    if(i <= topArray)
      for(j = 0; j <= stacks[i]->top; j++)
        printf("%d,", stacks[i]->list[j]->number);
    printf("\n");
  }
}

/*
Imprime os dados das pessoas em ordem
*/
void final_print(Stack *stacks[], Queue *queue, int lastPoint){
  int i, j = 0;
  for(i = 1; i <= lastPoint + 1; i++){
    printf("%d,%s", stacks[j]->list[(i-1)%5]->number, stacks[j]->list[(i-1)%5]->information);
    free(stacks[j]->list[(i-1)%5]);
    if((i % 5) == 0)
      j++;
  }
}

/*
Insere pessoa na fila
*/
Queue *insert_in_queue(Queue *queue, Person *info){
  Queue *new = (Queue*) malloc(sizeof(Queue));
  if (!new)
    exit(1);
  new->info = info;
  new->next = NULL;
  if(queue)
    queue->last->next = new;
  else{
    queue = new;
    queue->first = new;
  }
  queue->last = new;
  return queue;
}

/*
Recebe as novas pessoas
*/
Queue* receive(Queue *queue, int number, int *totalCounter){
  int i;
  i = getchar();
  i = getchar(); /*Le o \n que tinha sobrado*/
  for(i = 1; i <= number; i++){
    Person *new = (Person*) malloc(sizeof(Person));
    new->number = ++(*totalCounter);
    fgets(new->information, 53, stdin);
    queue = insert_in_queue(queue, new);
  }
  return queue;
}

/*
Insere uma pessoa nas pilhas
*/
void insert_in_stack(Stack *stacks[], Queue *queue, int *topArray, int *lastPoint){
  if((*topArray == -1) || ((stacks[(*topArray)]->top == MAX_STACK) && ((*topArray) < MAX_ARRAY))){
    Stack *new = (Stack*) malloc(sizeof(Stack));
    new->top = 0;
    new->list[new->top] = queue->first->info;
    stacks[(++(*topArray))] = new;
    (*lastPoint)++;
  }
  else if(stacks[(*topArray)]->top == MAX_STACK);
  else{
    (stacks[(*topArray)]->top)++;
    stacks[(*topArray)]->list[stacks[(*topArray)]->top] = queue->first->info;
    (*lastPoint)++;
  }
}

/*
Remove elementos da fila e insere nas pilhas se possivel
*/
void remove_from_queue(Stack *stacks[], Queue **queue, int number, int *topArray, int *lastPoint){
  int i;
  for(i = 0; i < number; i++){
  /*Se ainda houverem pessoas na fila*/
    if((*queue)){
      insert_in_stack(stacks, *queue, topArray, lastPoint);
      Queue *aux = (*queue);
      if((*queue)->next){
        (*queue)->next->last = (*queue)->last;
        (*queue) = (*queue)->next;
        (*queue)->first = (*queue);
        free(aux);
      }else{
        free(aux);
        (*queue) = NULL;
      }
    }
  }
}

/*
Remove os elementos das pilhas
*/
void remove_from_stack(Stack *stacks[], int *topArray, int number){
  int i;
  for(i = 0; i < number; i++){
    if((*topArray) >= 0){
      stacks[(*topArray)]->top = stacks[(*topArray)]->top - 1;
        if(stacks[(*topArray)]->top == -1)
          (*topArray) = (*topArray) - 1;
    }
  }
}

/*
Libera os espaços de memoria alocada
*/
void free_space(Stack *stacks[], Queue **queue, int lastPoint){
  int i;
  for(i = 0; i <= lastPoint/5; i++)
    free(stacks[i]);
}
