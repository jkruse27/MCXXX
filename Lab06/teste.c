#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int number;
  char information[53];
}Person;

int main(){
  Person *new = (Person*) malloc(sizeof(Person));
  new->number = 1;
  scanf("%[^\n]", new->information);
  printf("oi");
  return 0;
}
