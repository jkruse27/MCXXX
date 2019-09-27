#include "montador.h"
#include <stdio.h>
#include <string.h>

//Marcador para o lado da linha
typedef enum{
  Left = 0, Right = 1
}Side;

/*
  Struct contendo as informacoes de cada rotulo
  que serao elementos de uma lista ligada
*/
typedef struct Rotulo{
  char name[64];
  unsigned line;
  Side side;
  Rotulo *next_rotulo;
}Rotulo;

/*
  Struct para os .set que serao elementos de uma lista ligada
*/
typedef struct Set{
    char name[64];
    int value_number;
    char value_set[64];
    Set *next_set;
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
    Rotulo *r_linked_list = null;     //Lista ligada contendo os rotulos
    Set *s_linked_list = null;        //Lista ligada contendo os .set
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
          current_line = get_dec(temp->palavra);
        else
          current_line = get_hex(temp->palavra);
        current_side = Left;
      }
      //  Se a diretiva for .align, pula para a proxima linha e lado permitidos
      else if(temp->tipo == Diretiva && !strcmp(temp->palavra, ".align")){
        int j;

        //  Se a palavra estiver na direita comeca a contar a partir da linha seguinte
        //  Caso contrario comeca a contar a partir da propria linha
        if(current_side == RIGHT)
          j = current_line + 1;
        else
          j = current_line;

        //  Encontra a proxima linha qu e divisivel pelo parametro do align
        //  e atualiza a liha atual e o lado atual
        i++;
        int div = get_dec(recuperaToken(i)->palavra);
        for(j; j < 1024; i++){
          if(j % div == 0){
            current_line = j;
            break;
            }
        current_side = Left;
        }
      }
      //  Se a palavra for um rotulo, verifica se ele ja esta na lista, e,
      //  caso nao esteja, adiciona a lista
      else if(temp->tipo == DefRotulo){
        char is_on_list = 0;
        Rotulo *element = r_linked_list;

        //  Remove o ':' do rotulo
        temp->palavra[strlen(temp->palavra) - 2] = '\0'

        //Checa se a definicao ja se encontra na lista
        while(element != null){
          if(!strcmp(element->name, temp->palavra))
            is_on_list = 1;
          element = element->next_rotulo;
        }

        //  Caso nao esteja, adiciona-a no inicio
        if(!is_on_list){
          Rotulo *new_element;
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

      }
    }

    /* printf("Voce deve implementar essa função para a Parte 2!");*/
    return 0;
}
