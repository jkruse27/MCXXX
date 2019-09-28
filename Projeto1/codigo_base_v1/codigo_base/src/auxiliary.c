#include "auxiliary.h"

/*
  Returns the decimal equivalent of a hexadecimal number expressed as a string
*/
int hex(char *ptr){
  int sum = 0;
  for(int j = 2; j < strlen(ptr); j++){
    if(ptr[j] > '9')
      sum = sum + ((ptr[j] - 87)*pow(16, strlen(ptr) - j - 1));
    else
      sum = sum + ((ptr[j] - '0')*pow(16, strlen(ptr) - j - 1));
  }
  return sum;
}

/*
  Returns the decimal equivalent of a decimal number expressed as a string
*/
long int dec(char *ptr){
  long int sum = 0;
  int u = 0;
  if(ptr[0] == '-')
    u = 1;
  for(int j = strlen(ptr) - 1 - u, k = u; j >= 0; j--, k++){
    sum = sum + ((ptr[k]-'0') * pow(10, j));
  }
  if(ptr[0] == '-')
    sum = sum * -1;
  return sum;
}
