#include "auxiliary.h"

/*
  Returns the decimal equivalent of a hexadecimal number expressed as a string
*/
int hex(char *ptr){
  int sum = 0;
  for(int j = 2; j < strlen(ptr); j++){
    if(ptr[j] > '9')
      sum = sum + ((ptr[j] - 87)*pow(16, strlen(ptr) - j - 1));
    else
      sum = sum + ((ptr[j] - '0')*pow(16, strlen(ptr) - j - 1));
  }
  return sum;
}

/*
  Returns the decimal equivalent of a decimal number expressed as a string
*/
long int dec(char *ptr){
  long int sum = 0;
  int u = 0;
  if(ptr[0] == '-')
    u = 1;
  for(int j = strlen(ptr) - 1 - u, k = u; j >= 0; j--, k++){
    sum = sum + ((ptr[k]-'0') * pow(10, j));
  }
  if(ptr[0] == '-')
    sum = sum * -1;
  return sum;
}

/*
  Cria um novo elemento, adiciona-o ao inicio da lista rotulo e retorna a nova lista
*/
Rotulo *new_r_node(char *name, unsigned line, Side side, Rotulo *atual){

  Rotulo *new_element = malloc(sizeof(Rotulo));
  new_element->name = name;
  new_element->line = line;
  new_element->side = side;
  new_element->next_rotulo = atual;

  return new_element;

}

/*
  Cria um novo elemento, adiciona-o ao inicio da lista set e retorna a nova lista
*/
Set *new_s_node(char *name, TipoDoToken type, char *value_set, Set *atual){

  Set *new_element = malloc(sizeof(Set));
  new_element->name = name;
  new_element->type = type;
  new_element->value_set = value_set;
  new_element->next_set = atual;

  return new_element;

}

/*
  Desaloca a lista recebida de Rotulo da memoria
*/
void free_r(Rotulo *initial){
  Rotulo *aux;
  while(initial != NULL){
    aux = initial;
    initial = initial->next_rotulo;
    free(aux);
  }

}

/*
  Desaloca a lista recebida de Set da memoria
*/
void free_s(Set *initial){
  Set *aux;
  while(initial != NULL){
    aux = initial;
    initial = initial->next_set;
    free(aux);
  }

}
