/*Joao Gabriel Segato Kruse RA:218615*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FATHER(i) ((i - 1) / 2)
#define LEFT_SON(i) ((2 * i) + 1)
#define RIGHT_SON(i) ((2 * i) + 2)

typedef struct{
  float atributes[3]; /*Guarda os atributos de cada carro (0 = aceleracao, 1 = controle, 2 = velocidade)*/
  int positions[3]; /*Guarda a posicao em cada heap do carro (0 = aceleracao, 1 = controle, 2 = velocidade)*/
}Car;

typedef struct{
  Car **list;
  int n;
}Heap;

Heap *insert_element(Heap *heap, Car *new_car, int atribute);
Car *remove_first(Heap *heap, int atribute, int position);
void change_order(Heap *heap, int n1, int n2);
void print(Heap *heaps[]);
Car* receive(Heap *heaps[]);
void free_up(Heap *heaps[]);
