#include <string.h>
#include <math.h>
#include "montador.h"
#include <stdlib.h>

#define THREE_CHARS '3'
#define TEN_CHARS '1'
#define WORD 'w'
#define WFILL 'f'

/*
Marcador para o lado da linha
*/
typedef enum{
  Left = 0, Right
}Side;

/*
  Struct contendo as informacoes de cada rotulo
  que serao elementos de uma lista ligada
*/
typedef struct Rotulo{
  char *name;
  unsigned line;
  Side side;
  struct Rotulo *next_rotulo;
}Rotulo;

/*
  Struct para os .set que serao elementos de uma lista ligada
*/
typedef struct Set{
    char *name;
    TipoDoToken type;
    char *value_set;
    struct Set *next_set;
}Set;

//Returns the conversion of a string number to hexadecimal
int hex(char *ptr);

//Returns the conversion o a string number to decimal
long int dec(char *ptr);

//Cria um novo no na lista de rotulos e retorna o primeiro elemento da nova lista
Rotulo *new_r_node(char *name, unsigned line, Side side, Rotulo *atual);

//Cria um novo no na lista de sets e retorna o primeiro elemento da nova lista
Set *new_s_node(char *name, TipoDoToken type, char *value_set, Set *atual);

//Libera a memoria alocada para a lista ligada de rotulos
void free_r(Rotulo *initial);

//Libera a memoria alocada para a lista ligada de rotulos
void free_s(Set *initial);

//Converte um int para uma string em hexadecimal com 3 ou 10 caracteres
char *dec_to_hex(int dec, char type);

//Completa o numero hexadecimal com zeros
char *complete_hex(char *hex, char type);

//Encontra a palavra a que se refere o word
char *get_word(char *word, Rotulo *r_list, Set *s_list, char command);
