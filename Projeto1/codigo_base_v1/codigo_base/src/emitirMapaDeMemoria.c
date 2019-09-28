#include "montador.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auxiliary.h"

//Marcador para o lado da linha
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

/*
    ---- Voce deve implementar essa função para a Parte 2! ----
    Utilize os tokens da estrutura de tokens para montar seu código!
    Retorna:
        *  1 caso haja erro na montagem; (imprima o erro em stderr)
        *  0 caso não haja erro.
 */
int emitirMapaDeMemoria()
{
    Rotulo *r_linked_list = NULL;     //Lista ligada contendo os rotulos
    Set *s_linked_list = NULL;        //Lista ligada contendo os .set
    int size = getNumberOfTokens();   //Numero de tokens na lista
    Token *temp;                      //Variavel temporaria para receber o comando atual
    unsigned current_line = 0;        //Linha atual
    Side current_side = Left;         //Lado da linha atual

    //  Percorre a lista salavando os valores dos .set e as
    //  posicoes de todos os rotulos em suas respectivas listas ligadas
    for(int i = 0; i < size; i++){
      temp = recuperaToken(i);

      //  Se a palavra for .org, ja atualiza a posicao para a nova linha a esquerda
      if(temp->tipo == Diretiva && !strcmp(temp->palavra, ".org")){
        i++;
        temp = recuperaToken(i);
        if(temp->tipo == Decimal)
          current_line = dec(temp->palavra);
        else
          current_line = hex(temp->palavra);
        current_side = Left;
      }
      //  Se a diretiva for .align, pula para a proxima linha e lado permitidos
      else if(temp->tipo == Diretiva && !strcmp(temp->palavra, ".align")){

        //  Se a palavra estiver na direita comeca a contar a partir da linha seguinte
        //  Caso contrario comeca a contar a partir da propria linha
        current_side = (current_side + 1) % 2;
        current_line = current_side == Left ? current_line + 1 : current_line;

        //  Encontra a proxima linha qu e divisivel pelo parametro do align
        //  e atualiza a liha atual e o lado atual
        i++;
        int div = dec(recuperaToken(i)->palavra);

        for(int j = 0; j < 1024; i++){
          if(j % div == 0){
            current_line = j;
            break;
            }
        }
      }
      //  Se a palavra for um rotulo, verifica se ele ja esta na lista, e,
      //  caso nao esteja, adiciona a lista
      else if(temp->tipo == DefRotulo){
        char is_on_list = 0;
        Rotulo *element = r_linked_list;

        //  Remove o ':' do rotulo
        temp->palavra[strlen(temp->palavra) - 2] = '\0';

        //Checa se a definicao ja se encontra na lista
        while(element != NULL){
          if(!strcmp(element->name, temp->palavra))
            is_on_list = 1;
          element = element->next_rotulo;
        }

        //  Caso nao esteja, adiciona-a no inicio
        if(!is_on_list){
          Rotulo *new_element = malloc(sizeof(Rotulo));
          new_element->name = temp->palavra;
          new_element->line = current_line;
          new_element->side = current_side;
          new_element->next_rotulo = r_linked_list;
          r_linked_list = new_element;
        }

      }
      //  Se a palavra for .set, verifica se a palavra seguinte ja esta na lista
      //  e, caso nao esteja, adiciona-a
      else if(temp->tipo == Diretiva && !strcmp(temp->palavra, ".set")){
        char is_on_list = 0;
        Set *element = s_linked_list;
        Token *aux = recuperaToken(++i);

        //Checa se a definicao ja se encontra na lista
        while(element != NULL){
          if(!strcmp(element->name, aux->palavra))
            is_on_list = 1;
          element = element->next_set;
        }

        Token *aux2 = recuperaToken(++i);

        //  Caso nao esteja, adiciona-a no inicio
        if(!is_on_list){
          Set *new_element = malloc(sizeof(Rotulo));
          new_element->name = aux->palavra;
          new_element->type = aux2->tipo;
          new_element->next_set = s_linked_list;
          s_linked_list = new_element;
        }

      }
      //  Caso a palavra atual seja uma instrucao atualiza a linha e o lado
      //  em que o programa se encontra
      else if(temp->tipo == Instrucao){
        current_side = (current_side + 1) % 2;
        current_line = current_side == Left ? current_line + 1 : current_line;
      }
    }

    /* printf("Voce deve implementar essa função para a Parte 2!");*/
    return 0;
}
