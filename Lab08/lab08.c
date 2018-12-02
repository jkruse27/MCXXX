/*Joao Gabriel Segato Kruse RA:218615*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Struct para os nos da arvore
*/
typedef struct Node{
  int info;
  struct Node *left, *right;
}Node;

int side(Node *tree, int side);
int diameter(Node *tree);
Node* insert_node(Node **tree, int value);
void in_print(Node *tree);
void pos_print(Node *tree);
void pre_print(Node *tree);
void free_tree(Node **tree);

int main(){
  int value, size, i;
  char operation[4];
  Node *tree;
  scanf(" %d %s", &size, operation);
  do{
    tree = NULL;
    for(i = 0; i < size; i++){  /*Insere todos os elementos na arvore*/
      scanf(" %d", &value);
      tree = insert_node(&tree, value);
    }
    printf("Diametro da arvore binaria: %d\n", diameter(tree));

    /*Imprime a lista na ordem desejada*/
    if(!strcmp(operation, "pre"))
      pre_print(tree);
    else if(!strcmp(operation, "pos"))
      pos_print(tree);
    else if(!strcmp(operation, "in"))
      in_print(tree);
    printf("\n");

    free_tree(&tree);
    scanf(" %d %s", &size, operation);
  }while(size && (strcmp(operation, "0"))); /*Reali\za o loop enquanto nao receber um "0 0" como input*/
  return 0;
}

/*
Insere um no na posicao ordenada da arvore de forma recursiva e retorna a raiz da arvore
*/
Node* insert_node(Node **tree, int value){
  if((*tree) == NULL){
    Node *new = (Node*) malloc(sizeof(Node));
    new->info = value;
    new->left = NULL;
    new->right = NULL;
    return new;
  }
  else if((*tree)->info > value)
    (*tree)->left = insert_node(&(*tree)->left, value);
  else
    (*tree)->right = insert_node(&(*tree)->right, value);
  return (*tree);
}

/*
Imprime a arvore em ordem infixa
*/
void in_print(Node *tree){
  if(tree != NULL){
    in_print(tree->left);
    printf("%d ", tree->info);
    in_print(tree->right);
  }
}

/*
Imprime a arvore em ordem prefixa
*/
void pre_print(Node *tree){
  if(tree != NULL){
    printf("%d ", tree->info);
    pre_print(tree->left);
    pre_print(tree->right);
  }
}

/*
Imprime a arvore em ordem posfixa
*/
void pos_print(Node *tree){
  if(tree != NULL){
    pos_print(tree->left);
    pos_print(tree->right);
    printf("%d ", tree->info);
  }
}

/*
Libera o espaco alocado pela arvore
*/
void free_tree(Node **tree){
  if((*tree)){
    free_tree(&(*tree)->left);
    free_tree(&(*tree)->right);
    free((*tree));
  }
}

/*
Encontra a maior altura posssivel a partir de um no de forma recursiva
*/
int height(Node *tree){
  int h_left, h_right;
  if(!tree)
    return 0;
  h_left = height(tree->left);
  h_right = height(tree->right);
  return 1 + (h_right > h_left ? h_right : h_left); /*Retorna a maior altura entre a esquerda e a diretita + 1 (o +1 é para adicionar o no atual)*/
}

/*
Funcao que encontra e retorna o diametro da arvore
*/
int diameter(Node *tree){
  if(tree == NULL)
    return 0;
  int diam = height(tree->left) + height(tree->right) + 1; /*Diametro da asrvore atual*/
  int left = diameter(tree->left); /*Diametro da subarvore esquerda*/
  int right = diameter(tree->right); /*Diametro da subarvore direita*/
  return (diam > left ? (diam > right ? diam : right) : (left > right ? left : right));  /*Retorna o maior entre os diametros*/
}
