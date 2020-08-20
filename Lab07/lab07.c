/*Joao Gabriel Segato Kruse RA:218615*/
#include "lab07.h"

int main(){
  int iterations, max_cars, i, c, p, j;
  scanf(" %d %d", &iterations, &max_cars);
  Heap* heaps[3];
  for(i = 0; i < 3; i++){
    heaps[i] = (Heap*) malloc(sizeof(Heap));
    heaps[i]->list = malloc(max_cars * sizeof(Car*));
    heaps[i]->n = -1;
  }
  if(!heaps[0] || !heaps[1] || !heaps[2])
    exit(1);
  for(i = 0; i < iterations; i++){
    scanf(" %d %d", &c, &p);
    for(j = 0; j < c; j++){
      receive(heaps);
    }
    for(j = 0; j < p; j++){
      print(heaps);
    }
  }
  free_up(heaps);
  return 0;
}

/*
Insere um novo elemento na posicao correta do heap, em comlexidade O(log n)
*/
Heap *insert_element(Heap *heap, Car *new_car, int atribute){
  int aux = heap->n + 1;
  heap->list[++(heap->n)] = new_car;
  new_car->positions[atribute] = aux;
  while(aux > 0 && (heap->list[aux]->atributes[atribute] > heap->list[FATHER(aux)]->atributes[atribute])){
    change_order(heap, aux, FATHER(aux));
    heap->list[FATHER(aux)]->positions[atribute] = FATHER(aux);
    heap->list[aux]->positions[atribute] = aux;
    aux = FATHER(aux);
  }
  return heap;
}

/*
Remove elemento de um heap e retorna ele (nao necessariamente o primeiro) em O(log n)
*/
Car *remove_position(Heap *heap, int atribute, int position){
  int biggestSon, change = 1;
  change_order(heap, position, heap->n);
  Car *car = heap->list[heap->n];
  heap->list[position]->positions[atribute] = position;
  heap->n--;
  while(LEFT_SON(position) <= heap->n && change){
    biggestSon = LEFT_SON(position);
    if(RIGHT_SON(position) <= heap->n && (heap->list[LEFT_SON(position)]->atributes[atribute] < heap->list[RIGHT_SON(position)]->atributes[atribute]))
      biggestSon = RIGHT_SON(position);
    if((heap->list[biggestSon]->atributes[atribute]) > heap->list[position]->atributes[atribute]){
      change_order(heap, position, biggestSon);
      heap->list[position]->positions[atribute] = position;
      heap->list[biggestSon]->positions[atribute] = biggestSon;
      position = biggestSon;
    }
    else
      change = 0;
  }
  while(position > 0 && (heap->list[position]->atributes[atribute] > heap->list[FATHER(position)]->atributes[atribute])){
    change_order(heap, position, FATHER(position));
    heap->list[FATHER(position)]->positions[atribute] = FATHER(position);
    heap->list[position]->positions[atribute] = position;
    position = FATHER(position);
  }
  return car;
}

/*
Troca dois carros de lugar em O(1)
*/
void change_order(Heap *heap, int n1, int n2){
    Car *aux = heap->list[n1];
    heap->list[n1] = heap->list[n2];
    heap->list[n2] = aux;
}

/*
Imprime os dados de um Carro, ja o retirando de todos os heaps
*/
void print(Heap *heaps[]){
  int choice;
  scanf(" %d", &choice);
  Car *new_car = remove_position(heaps[choice], choice, 0);
  switch(choice){
    case 0:
      remove_position(heaps[1], 1, new_car->positions[1]);
      remove_position(heaps[2], 2, new_car->positions[2]);
      break;
    case 1:
      remove_position(heaps[0], 0, new_car->positions[0]);
      remove_position(heaps[2], 2, new_car->positions[2]);
      break;
    case 2:
      remove_position(heaps[0], 0, new_car->positions[0]);
      remove_position(heaps[1], 1, new_car->positions[1]);
      break;
  }
  printf("%.2f %.2f %.2f\n", new_car->atributes[0], new_car->atributes[1], new_car->atributes[2]);
  free(new_car);
}

/*
Recebe os elementos, inserindo-os nos heaps
*/
Car* receive(Heap *heaps[]){
  Car *new_car = (Car*) malloc(sizeof(Car));
  if(!new_car)
    exit(1);
  scanf(" %f %f %f", &new_car->atributes[0], &new_car->atributes[1], &new_car->atributes[2]);
  heaps[0] = insert_element(heaps[0], new_car, 0);
  heaps[1] = insert_element(heaps[1], new_car, 1);
  heaps[2] = insert_element(heaps[2], new_car, 2);
  return new_car;
}

/*
Libera os espacos de memoria alocados
*/
void free_up(Heap *heaps[]){
  int i, j;
  for(j = 0; j <= heaps[0]->n; j++)
    free(heaps[0]->list[j]);
  for(i = 0; i < 3; i++){
    free(heaps[i]->list);
    free(heaps[i]);
  }
}
