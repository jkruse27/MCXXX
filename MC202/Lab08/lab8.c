/*
Joao Gabriel Segato Kruse RA:218615
*/
#include <stdio.h>
#include <stdlib.h>

/*
Struct para os nos da arvore contendo a informacao, um ponteiro para o filho
a esquerda, um para o a direita e um para o pai
*/
typedef struct Node{
  int info;
  struct Node *left, *right, *father;
}Node;

int side(Node *tree, int side);
int diameter(Node *tree);
void insert_node(Node **tree, int value);
void in_print(Node *tree);
void pos_print(Node *tree);
void pre_print(Node *tree);
void free_tree(Node **tree);

int main(){
  int value, size, i;
  char operation[4];
  Node *tree;
  do{
    scanf(" %d %s", &size, operation); /*Recebe o numero de nos (size) e a forma de impressao da arvore (operation)*/
    tree = NULL; /*Inicializa uma arvore vazia*/
    for(i = 0; i < size; i++){  /*Insere todos os elementos na arvore*/
      scanf(" %d", &value);
      insert_node(&tree, value);
    }
    if(size && operation[0]){
      printf("Diametro da arvore binaria: %d\n", diameter(tree));

      /*Imprime a lista na ordem desejada usando ternario*/
      (operation[0] == 'p') ? (operation[1] == 'r' ? pre_print(tree) : pos_print(tree)) : in_print(tree);
      printf("\n");
      free_tree(&tree);  /*Libera a arvore*/
    }
  }while(size && operation[0]); /*Reali\za o loop enquanto nao receber um "0 0" como input*/
  return 0;
}

/*
Insere um no na posicao ordenada da arvore de forma iterativa, alterando a arvore por ponteiro
*/
void insert_node(Node **tree, int value){
  Node *new = (Node*) malloc(sizeof(Node));
  new->info = value;
  new->left = NULL;
  new->right = NULL;
  new->father = NULL;
  /*Se a arvore esta vazia, inserimos o elemento na raiz*/
  if(*tree == NULL)
    (*tree) = new;
  else{
    int side; /*Inteiro que marca o ultimo lado para o qual descemos na arvore*/
    Node *aux = (*tree);
    /*Enquanto nao estivermos em uma folha, vamos descendo na arvore seguindo a regra de maiores a direita e menores a esquerda*/
    while(aux){
      new->father = aux;
      if(aux->info > value){
        aux = aux->left;
        side = 0;
      }else{
        aux = aux->right;
        side = 1;
      }
    }
    /*Se estamos em NULL, inserimos o novo no e alteramos os filho do pai desse novo no*/
    aux = new;
    side ? (new->father->right = aux) : (new->father->left = aux);
  }
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
Libera o espaco alocado pela arvore segundo um percurso pos ordem
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
  if(tree != NULL){
    int diam = height(tree->left) + height(tree->right) + 1; /*Diametro da asrvore atual*/
    int left = diameter(tree->left); /*Diametro da subarvore esquerda recursivamente*/
    int right = diameter(tree->right); /*Diametro da subarvore direita recursivamente*/
    return (diam > left ? (diam > right ? diam : right) : (left > right ? left : right));  /*Retorna o maior entre os diametros*/
  }
  return 0;  /*Quando chegamos em um no nulo o diametro e 0*/
}
