#include <stdio.h>

int toBinary(int a, int b, int c, int d){
  int q = 0, soma = 1, vezes = 0;
  while(vezes < 2){
    q = q + (soma*(a%2));
    a = a/2;
    soma = soma * 10;
    vezes += 1;
  }
  vezes = 0;
  while(vezes < 2){
    q = q + (soma*(b%2));
    b = b/2;
    soma = soma * 10;
    vezes += 1;
  }
  vezes = 0;
  while(vezes < 2){
    q = q + (soma*(c%2));
    c = c/2;
    soma = soma * 10;
    vezes += 1;
  }
  vezes = 0;
  while(vezes < 2){
    q = q + (soma*(d%2));
    d = d/2;
    soma = soma * 10;
    vezes += 1;
  }
  printf("%d\n", q);
  return q;
}

int main(){
  int a, b, c, d, e;
  scanf("%d %d %d %d", &a, &b, &c, &d);
  e = (char)toBinary(a, b, c, d);
  printf("%c %d \n", e, e);

  return 0;
}
