/*
Joao Gabriel Segato Kruse RA:218615
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Condicoes de termino de uma palavra (se ler um desses char, implica que a palvra anterior termina ali)
*/
#define WORD_END(c) ((c != '(') && (c != ')') && (c != ' ')\
                    && (c != '{') && (c != '}') && (c != '\n')\
                    && (c != '\r') && (c != ';') && (c != '*')\
                    && (c != '\t') && (c != ':') && (c != EOF)\
                    && (c != '#') && (c != '[') && (c != ']'))
#define RESERVED_WORDS 32

/*
Struct para a arvore AVL
*/
typedef struct Node{
  char name[10];
  struct Node *left, *right;
}Node;

/*
Estrura para a pilha
*/
typedef struct Stack{
  Node *info;
  struct Stack *next;
}Stack;

Stack *insert_stack(Node *info, Stack *stack);
Node *remove_stack(Stack **stack);
Node *create_node(char *info);
char *get_word(char *last_char);
int is_word_reserved(char *word, char reserved_names[RESERVED_WORDS][10]);
Node *insert_in_tree(char *word, Node *tree);
void zigzag_print(Node *tree);
void free_tree(Node **tree);
int tree_height(Node *tree);
Node *rotation_right(Node *change);
Node *rotation_left(Node *change);

int main(){
  /*Matriz contendo todas as palavras reservadas ordenadas alfabeticamente*/
  char reserved_names[RESERVED_WORDS][10] = {
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "int",
    "long",
    "register",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while"
  };
  char *word;
  /*A variavel last_char e o ultimo char lido, indicando o termino do arquivo quando for EOF*/
  char last_char = '1';
  Node *avl_tree = NULL;

  while(last_char != EOF){
    word = get_word(&last_char);
    if(word && word[0] != '\0') /*Testa se a palvra nao e nula*/
      if(is_word_reserved(word, reserved_names)) /*Testa se a plavra e reservada*/
        avl_tree = insert_in_tree(word, avl_tree);
    free(word);
  }
  printf("O percurso da árvore é:\n");
  zigzag_print(avl_tree);
  free_tree(&avl_tree);
  return 0;
}

/*
Insere um novo elemento em uma pilha, retornando ele
*/
Stack *insert_stack(Node *info, Stack *stack){
  Stack *new = (Stack*) malloc(sizeof(Stack));
  new->info = info;
  new->next = stack;
  return new;
}

/*
Remove um elemento da pilha, retornando o seu valor
*/
Node *remove_stack(Stack **stack){
  if(stack){
    Stack *aux = (*stack);
    (*stack) = (*stack)->next;
    Node *aux2 = aux->info;
    free(aux);
    return aux2;
  }
  return NULL;
}

/*
Funcao que cria um novo no com a palavra registrada
*/
Node *create_node(char *info){
  Node *new = (Node*) malloc(sizeof(Node));
  if(!new)
    exit(1);
  strcpy(new->name, info);
  new->left = NULL;
  new->right = NULL;
  return new;
}

/*
Funcao que retorna a altura de uma subarvore
*/
int tree_height(Node *tree){
  if(!tree)
    return 0;
  int right = tree_height(tree->right);
  int left = tree_height(tree->left);
  return 1 + (left > right ? left : right);
}

/*
Funcao que retorna uma palavra do texto, alterando a variavel last_char na main
*/
char *get_word(char *last_char){
  char character, *word;
  int occupied, size = 10;
  word = (char*) malloc(sizeof(char) * size);
  if(!word)
    exit(1);
  /*Vai colocando chars na string ate que um char que indica o final de palavra seja lido*/
  for(occupied = 2, character = getchar(); WORD_END(character); occupied++, character = getchar()){
    /*Sempre deixa um espaco a mais no vetor da palavra para podermos inserir o '/0' e realoca caso necessario*/
    if(occupied >= size)
    size = size * 2;
      word = realloc(word, (sizeof(char) * size));
      if(!word)
        exit(1);
    word[occupied - 2] = character;
  }
  word[occupied - 2] = '\0';
  *last_char = character;
  return word;
}

/*
Funcao que recebe uma palavra e retorna 1 se ela estiver na lista das reservadas e 0 caso contrario
Como apenas buscamos 1 palavra de cada reservada. (E utilizada uma busca binaria iterativa, ja que a lista
de palavras reservadas esta ordenada)
*/
int is_word_reserved(char *word, char reserved_names[RESERVED_WORDS][10]){
  int begin = 0, end = RESERVED_WORDS - 1, middle, value;
  while(begin <= end){
    middle = (begin + end)/2;
    value = strcmp(word, reserved_names[middle]);
    if(!value)
      return 1;
    else if(value > 0)
      begin = middle + 1;
    else
      end = middle - 1;
  }
  return 0;
}

/*
Funcao que libera o espaco alocado para a arvore
*/
void free_tree(Node **tree){
  if(*tree != NULL){
    free_tree(&((*tree)->left));
    free_tree(&((*tree)->right));
    free(*tree);
  }
}

/*
Funcao que imprime a arvore na ordem zig-zag
*/
void zigzag_print(Node *tree){
  int print = 0, first;
  Stack *stack1 = NULL;
  Stack *stack2 = NULL;
  Node *aux = tree;
  stack1 = insert_stack(aux, stack1);
  while(stack1 || stack2){
    first = 1;
    print = 0;
    while(stack1){
      aux = remove_stack(&stack1);
      if(aux){
        if(first){
          printf("[ ");
          first = 0;
          print = 1;
        }
        printf("%s ", aux->name);
        stack2 = insert_stack(aux->right, stack2);
        stack2 = insert_stack(aux->left, stack2);
      }
    }
    if(print)
      printf("]\n");

    first = 1;
    print = 0;
    while(stack2){
      aux = remove_stack(&stack2);
      if(aux){
        if(first){
          printf("[ ");
          first = 0;
          print = 1;
        }
        printf("%s ", aux->name);
        stack1 = insert_stack(aux->left, stack1);
        stack1 = insert_stack(aux->right, stack1);
      }
    }
    if(print)
      printf("]\n");
  }
}

/*
Realiza a rotacao de um elemento para a direita
*/
Node *rotation_right(Node *change){
  Node *aux1 = change->left;
  Node *aux2 = aux1->right;
  /*Troca de ponteiros*/
  aux1->right = change;
  change->left = aux2;
  return aux1;
}

/*
Realiza a rotacao de um no para a esquerda
*/
Node *rotation_left(Node *change){
  Node *aux1 = change->right;
  Node *aux2 = aux1->left ;
  /*Troca de ponteiros*/
  aux1->left = change;
  change->right = aux2;
  return aux1;
}

/*
Funcao que insere um novo no na arvore, mantendo ela em ordem alfabetica e com as propriedades avl
*/
Node *insert_in_tree(char *word, Node *tree){
  /*Insercao normal do elemento*/
  if(!tree)
    return create_node(word);
  else if(strcmp(tree->name, word) > 0)
    tree->left = insert_in_tree(word, tree->left);
  else if(strcmp(tree->name, word) < 0)
    tree->right = insert_in_tree(word, tree->right);
  else
    return tree;

  /*Verificacao do fator de balanceamento*/
  int balance = tree_height(tree->left) - tree_height(tree->right);

  /*Realiza a rotacao certa, se necessario*/
    if(balance > 1 && strcmp(word, tree->left->name) < 0)
      return rotation_right(tree);
    else if(balance > 1 && strcmp(word, tree->left->name) > 0){
      tree->left = rotation_left(tree->left);
      return rotation_right(tree);
      }
    if(balance < -1 && strcmp(word, tree->right->name) > 0)
      return rotation_left(tree);
    else if(balance < -1 && strcmp(word, tree->right->name) < 0){
      tree->right = rotation_right(tree->right);
      return rotation_left(tree);
    }
  return tree;
}
