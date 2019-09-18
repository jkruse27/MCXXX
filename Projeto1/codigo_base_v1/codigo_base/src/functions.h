#include <string.h>

#define N_INSTRUCTIONS_C 14
#define N_INSTRUCTIONS_N 3
#define N_DIRECTIVES 5

typedef enum{
  INSTRUCTION=1000, DIRECTIVE, ROTULO, HEXADECIMAL, DECIMAL,
   NAME, WFILL, SET, ORG, WORD, ALIGN, ERRO_GRAMATICAL, ERRO_LEXICO
}Types;

//Returns the point in the list where the comment has ended
int inside_range(char* ptr, int i, int word_beggining, Types type, Types lid, int complement);

// Returns the type of the word
int ignore_comment(char* entrada, int i, int tamanho);

//Checks if there is any lexical error in the rotulo word
Types find_type(char *ptr, int i, int word_beggining, char *complement, Types *lid);

//Checks if a word is a valid instruction
int rotulo_check(char *ptr, int i, int word_beggining);

//Return the type of complement (decimal, hexadecimal or name)
int is_instruction(char *ptr);

//Checks for the validity of the numbers
Types complement_type(char *ptr, int i, int word_beggining, Types lid, int complement);

//Retorns powers of 10
long int pot(int e, int p);

//Checks if a word is a valid directive
int is_directive(char* ptr);

//Returns the conversion of a string number to hexadecimal
int get_hex(char *ptr, int i, int word_beggining);

//Returns the conversion o a string number to decimal
long int get_dec(char *ptr, int i, int word_beggining);

//Checks if there is anything invalid with the type chosen
Types check_for_errors(Types type, Types lid, char complement);
