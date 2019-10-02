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

//----------------------------- Primeira Passada Pela Lista -----------------------------------//
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
    /*  //  Se a palavra for .set, verifica se a palavra seguinte ja esta na lista
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

      }*/
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
//----------------------------- Segunda Passada Pela Lista ------------------------------------//
    //Completa a lista de .set e verifica se todos os rotulos e sets sao declarados
    for(int i = 0; i < size; i++){
      temp = recuperaToken(i);
      char flag = 0;

      if(temp->tipo == Nome){
        Rotulo *element = r_linked_list;

        while(element != NULL){
          if(!strcmp(element->name, temp->palavra)){
            flag = 1;
            break;
          }
          element = element->next_rotulo;
        }

        if(flag == 0){

          Set *element = s_linked_list;

          //Checa se a definicao ja se encontra na lista
          while(element != NULL){
            if(!strcmp(element->name, temp->palavra)){
              flag = 1;
              break;
            }
            element = element->next_set;
          }
        }

        if(flag == 0){
          fprintf(stderr, "ERRO: Rotulo ou sımbolo usado mas não definido: %s\n", temp->palavra);
          return 1;
        }
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
    }
//---------------------------- Terceira Passada Pela Lista ------------------------------------//
    current_line = 0;
    current_side = Left;

    for(int i = 0; i < size; i++){
      temp = recuperaToken(i);
      //  Se a palavra for .org, ja atualiza a posicao para a nova linha a esquerda
      if(temp->tipo == Diretiva && !strcmp(temp->palavra, ".org")){
        i++;
        //Completa a linha com zeros se necessario
        if(current_side == Right)
          printf("00 000\n");

        temp = recuperaToken(i);
        if(temp->tipo == Decimal)
          current_line = dec(temp->palavra);
        else
          current_line = hex(temp->palavra);
        current_side = Left;
      }
      //  Se a diretiva for .align, pula para a proxima linha e lado permitidos
      else if(temp->tipo == Diretiva && !strcmp(temp->palavra, ".align")){
        //Completa a linha com zeros se necessario
        if(current_side == Right)
          printf("00 000\n");

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
      //Se a palavra for .word imprime a word correspondente em hexadecimal
      else if(temp->tipo == Diretiva && !strcmp(temp->palavra, ".word")){
          Token *aux = recuperaToken(++i);

          char *hexa = get_word(aux->palavra, r_linked_list, s_linked_list, WORD);

          char *l = dec_to_hex(current_line, THREE_CHARS);
          printf("%s %s\n", l, hexa);

          free(hexa);
          free(l);

          current_line++;
      }
      //Se a palavra for .wfill, completa as n linhas seguintes com o valor dado
      else if(temp->tipo == Diretiva && !strcmp(temp->palavra, ".wfill")){
        Token *aux = recuperaToken(++i);
        int lines = dec(aux->palavra);

        char *hexa;
        aux = recuperaToken(++i);
        if(aux->tipo == Nome)
          hexa = get_word(aux->palavra, r_linked_list, s_linked_list, WFILL);
        else if(aux->tipo == Decimal)
          hexa = dec_to_hex(dec(aux->palavra), TEN_CHARS);
        else
          hexa = complete_hex(aux->palavra, TEN_CHARS);

        for(int j = current_line; j < current_line + lines; j++){
          char *l = dec_to_hex(j, THREE_CHARS);
          printf("%s %s\n", l, hexa);
          free(l);
        }

        free(hexa);
        current_line += lines;
      }
      //Caso a palavra seja uma instrucao imprime o codigo correspondente
      else if(temp->tipo == Instrucao){
        char *ins;
        char *num;

        if(!strcmp(temp->palavra, "ld")){

        }else if(!strcmp(temp->palavra, "ldinv")){

        }else if(!strcmp(temp->palavra, "ldabs")){

        }else if(!strcmp(temp->palavra, "ldmq")){

        }else if(!strcmp(temp->palavra, "ldmqmx")){

        }else if(!strcmp(temp->palavra, "store")){

        }else if(!strcmp(temp->palavra, "jge")){

        }else if(!strcmp(temp->palavra, "add")){

        }else if(!strcmp(temp->palavra, "addabs")){

        }else if(!strcmp(temp->palavra, "sub")){

        }else if(!strcmp(temp->palavra, "subabs")){

        }else if(!strcmp(temp->palavra, "mult")){

        }else if(!strcmp(temp->palavra, "div")){

        }else if(!strcmp(temp->palavra, "lsh")){

        }else if(!strcmp(temp->palavra, "rsh")){

        }else if(!strcmp(temp->palavra, "storend")){

        }
      }
    }

    // Libera as listas ligadas alocadas
    free_s(s_linked_list);
    free_r(r_linked_list);

    return 0;
}
