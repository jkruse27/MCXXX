#include "montador.h"
#include <stdio.h>
#include "functions.h"


/*
Exemplo de erros:
const char* get_error_string (enum errors code) {
    switch (code) {
        case ERR_HEXADECIMAL_NAO_VALIDO:
            return "LEXICO: Numero Hexadecimal Inválido!";
        case ERRO_ROTULO_JA_DEFINIDO:
            return "GRAMATICAL: ROTULO JA FOI DEFINIDO!";
        case ERR_DIRETIVA_NAO_VALIDA:
            return "LEXICO: Diretiva não válida";
*/

/*
    ---- Você Deve implementar esta função para a parte 1.  ----
    Essa função é chamada pela main em main.c
    Entrada da função: arquivo de texto lido e seu tamanho
    Retorna:
        * 1 caso haja erro na montagem; (imprima o erro em stderr)
        * 0 caso não haja erro.         (Caso não haja erro, na parte 1, ao retornar desta função, a lista de Tokens (adicionados utilizando a função adicionarToken()) é impressa)
*/
int processarEntrada(char* entrada, unsigned tamanho)
{
    int order[] = {0, 0};  //Marca a ordem [rotulo][instucao/diretiva]
    unsigned int word_beggining = 0, line = 1;  //Marca o inicio de cada palavra no vetor e a linha atual
    char complement = 0;  //Numero de complementos que a instrucao/diretiva atual recebe
    Types lid = 0;    //Diretiva/Instrucao mais atual

    //Para cada letra na entrada
    for(int i = 0; i < tamanho; i++){

      // Pula os comentarios
      if(entrada[i] == '#'){
        i = ignore_comment(entrada, i, tamanho);
        word_beggining = i;
      }

      //Converte letras maiusculas para minusculas
      if (entrada[i] >= 'A' && entrada[i] <= 'Z')
        entrada[i] = entrada[i] + 32;

      //Verifica o que fazer com cada palvra da entrada
      if(entrada[i] == ' ' || entrada[i] == '\n' || entrada[i] == '\t'){
        // Cria um ponteiro para a palavra
        char *ptr = entrada + word_beggining;
        char aux = entrada[i];
        entrada[i] = '\0';

        //Se a palavra nao for vazia, verifica ela
        if(word_beggining != i){

          //Encontra o tipo da palavra
          Types type = find_type(ptr, i, word_beggining, &complement, &lid);

          if(type == ERRO_LEXICO){
            fprintf(stderr, "ERRO LEXICO: palavra inválida na linha %d!\n", line);
            return 1;
          }else if(type == ERRO_GRAMATICAL){
            fprintf(stderr, "ERRO GRAMATICAL: palavra na linha %d!\n", line);
            return 1;
          }

          enum TipoDoToken t;

          if(type == DIRECTIVE){
            t = Diretiva;
            if(order[1] == 1)
              type = ERRO_GRAMATICAL;
            order[1] = 1;
          }
          else if(type == INSTRUCTION){
            t = Instrucao;
            if(order[1] == 1)
              type = ERRO_GRAMATICAL;
            order[1] = 1;
          }
          else if(type == ROTULO){
            t = DefRotulo;
            if(order[1] == 1 || order[0] == 1)
              type = ERRO_GRAMATICAL;
            order[0] = 1;
          }
          else if(type == DECIMAL){
            t = Decimal;
          }
          else if(type == HEXADECIMAL){
            t = Hexadecimal;
          }
          else{
            t = Nome;
          }
          if(type == ERRO_GRAMATICAL){
            fprintf(stderr, "ERRO GRAMATICAL: palavra na linha %d!\n", line);
            return 1;
          }

          //Caso a palvra nao cause nenhum erro, cria um token para ela e adiciona a lista
          adicionarToken(t, ptr, line);

        }

        //Atualiza o numero da linha atual quando necessario
        if(aux == '\n'){
          //Se mudar a linha e houverem complementos demais ou de menos, marca um erro gramatical
          if (complement != 0){
            fprintf(stderr, "ERRO GRAMATICAL: palavra na linha %d!\n", line);
            return 1;
          }
          line++;
          //Zera as variaveis de ordem na linha e ultimo comando
          order[0] = 0; order[1] = 0;
          lid = 0;
        }

        //Marca o inicio da palavra seguinte
        word_beggining = i + 1;
      }
    }

    return 0;
}
