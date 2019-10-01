#include "montador.h"
#include <stdio.h>
#include <string.h>
#include "auxiliary.h"

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


//------------------------- Primeira Passada Pela Lista ---------------------------------------//
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

        for(int j = 0; j < 1024; j++){
          if(j % div == 0){
            current_line = j;
            break;
            }
        }
      }
      //  Se a palavra for um rotulo, verifica se ele ja esta na lista, e,
      //  caso nao esteja, adiciona a lista
      else if(temp->tipo == DefRotulo){
        Rotulo *element = r_linked_list;

        //  Remove o ':' do rotulo
        temp->palavra[strlen(temp->palavra) - 1] = '\0';

        //Checa se a definicao ja se encontra na lista
        while(element != NULL){
          if(!strcmp(element->name, temp->palavra)){
            fprintf(stderr, "ERRO GRAMATICAL: palavra na linha %u!\n", temp->linha);
            return 1;
          }
          element = element->next_rotulo;
        }

        //  Caso nao esteja, adiciona-a no inicio
        r_linked_list = new_r_node(temp->palavra, current_line, current_side, r_linked_list);

      }
      //  Se a palavra for .set, verifica se a palavra seguinte ja esta na lista
      //  e, caso nao esteja, adiciona-a
      else if(temp->tipo == Diretiva && !strcmp(temp->palavra, ".set")){
        Set *element = s_linked_list;
        Token *aux = recuperaToken(++i);

        //Checa se a definicao ja se encontra na lista
        while(element != NULL){
          if(!strcmp(element->name, aux->palavra)){
            fprintf(stderr, "ERRO GRAMATICAL: palavra na linha %u!\n", temp->linha);
            return 1;
          }
          element = element->next_set;
        }

        Token *aux2 = recuperaToken(++i);

        //  Caso nao esteja, adiciona-a no inicio
        s_linked_list = new_s_node(aux->palavra, aux2->tipo, aux2->palavra, s_linked_list);

      }
      //  Caso a palavra atual seja uma instrucao atualiza a linha e o lado
      //  em que o programa se encontra
      else if(temp->tipo == Instrucao){
        current_side = (current_side + 1) % 2;
        current_line = current_side == Left ? current_line + 1 : current_line;
      }
      //Se a palavra for um .word, pula a linha simplesmente
      else if(temp->tipo == Diretiva && !strcmp(temp->palavra, ".word")){
          if(current_side == Right){
            fprintf(stderr, "ERRO GRAMATICAL: palavra na linha %u!\n", temp->linha);
            return 1;
          }
          current_line++;
      }
      //Se for .wfill pula o numero de linhas que serao completas
      else if(temp->tipo == Diretiva && !strcmp(temp->palavra, ".wfill")){
        if(current_side == Right){
          fprintf(stderr, "ERRO GRAMATICAL: palavra na linha %u!\n", temp->linha);
          return 1;
        }
        Token *aux = recuperaToken(++i);
        int skip_line = dec(aux->palavra);
        current_line += skip_line;
      }
    }

//------------------------- Segunda Passada Pela Lista ---------------------------------------//
    /*


      Codigo de verdade


    */

    // Libera as listas ligadas alocadas
    free_s(s_linked_list);
    free_r(r_linked_list);

    /* printf("Voce deve implementar essa função para a Parte 2!");*/
    return 0;
}
