#include "auxiliary.h"
#include <stdio.h>

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
Rotulo *new_r_node(char *name, int line, Side side, Rotulo *atual){

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

/*
  Converte um int para uma string em hexadecimal com 3 ou 10 caracteres
  Recebe o numero a ser convertido e o tipo (3 ou 10 caracteres)
*/
char *dec_to_hex(int dec, char type){

  char *string;

  if(type == THREE_CHARS){
    string = malloc(4*sizeof(char));
    string[3] = '\0';

    for(int j = 2; j >= 0; j--){
      int a = dec%16;
      if(a < 10)
        string[j] = a + 48;
      else
        string[j] = a + 55;
      dec = dec/16;
      }
  }else{
    string = malloc(14*sizeof(char));
    string[13] = '\0';

    char string1[10];

    for(int j = 9; j >= 0; j--){
      int a = dec%16;

      if(a < 10)
        string1[j] = a + 48;
      else
        string1[j] = a + 55;
      dec = dec/16;
      }

    for(int j = 0, k = 0; j < 13; j++){
      if(j == 2 || j == 6 || j == 9)
        string[j] = ' ';
      else
        string[j] = string1[k++];
    }

  }

  return string;
}

/*
  Completa o numero em hexadecimal com zeros para fechar os 3 ou 10 digitos
  Recebe o numero em hexadecimal na forma de string e o tipo (3 ou 10 caracteres)
  Retorna a string contendo o numero com os zeros adicionados
*/
char *complete_hex(char *hex, char type){

  int len = strlen(hex); //Tamanho desconsidera o '0x'
  char *string;

  if(type == THREE_CHARS){
    string = malloc(4*sizeof(char));
    string[3] = '\0';

    for(int j = 0, k = 2; j < 3; j++)
      if(j < 3 - len + 2)
        string[j] = '0';
      else{
        if(hex[k] < 58)
          string[j] = hex[k++];
        else
          string[j] = hex[k++] - 32;
      }

  }else{
    string = malloc(14*sizeof(char));
    string[13] = '\0';

    char string1[10];

    for(int j = 0, k = 2; j < 10; j++)
      if(j < 10 - len + 2)
        string1[j] = '0';
      else{
        if(hex[k] < 58)
          string1[j] = hex[k++];
        else
          string1[j] = hex[k++] - 32;
      }
    for(int j = 0, k = 0; j < 13; j++){
      if(j == 2 || j == 6 || j == 9)
        string[j] = ' ';
      else
        string[j] = string1[k++];
      }
    }

  return string;
}

/*
  Encontra a palavra hexadecimal a que se refere a word
*/
char *get_word(char *word, Rotulo *r_list, Set *s_list, char command){
  Rotulo *r_aux = r_list;
  Set *s_aux = s_list;

  if(command == WORD){
    while(r_aux != NULL){
      if(!strcmp(r_aux->name, word)){
        return dec_to_hex(r_aux->line, TEN_CHARS);
      }
      r_aux = r_aux->next_rotulo;
    }
  }

  while(s_aux != NULL){
    if(!strcmp(s_aux->name, word)){
      if(s_aux->type == Hexadecimal)
        return complete_hex(s_aux->value_set, TEN_CHARS);
      else if(command == WFILL && s_aux->type == Nome){
        return get_word(s_aux->name, r_list, s_list, WORD);
      }
      else{
        int a = dec(s_aux->value_set);
        return dec_to_hex(a, TEN_CHARS);
      }
    }
    s_aux = s_aux->next_set;
  }

  return NULL;
}

/*
  Retorna o rotulo a que se refere um rotulo de uma instrucao
*/
Rotulo *get_rotulo(char *word, Rotulo *r_list){
  Rotulo *r_aux = r_list;

  while(r_aux != NULL){
    if(!strcmp(r_aux->name, word)){
      return r_aux;
    }
    r_aux = r_aux->next_rotulo;
  }

  return NULL;
}

/*
  Retorna o valor em hexa do numero equivalente do set
*/
char *get_set(char *word, Set *s_list){
    Set *s_aux = s_list;
    while(s_aux != NULL){
      if(!strcmp(s_aux->name, word)){
        if(s_aux->type == Hexadecimal)
          return complete_hex(s_aux->value_set, THREE_CHARS);
        else{
          int a = dec(s_aux->value_set);
          return dec_to_hex(a, THREE_CHARS);
        }
      }
      s_aux = s_aux->next_set;
    }

    return NULL;
}
