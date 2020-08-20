#include "functions.h"

const char* lc[] = {"ld", "ldinv", "ldabs",
                  "ldmqmx", "store", "jump",
                    "add", "jge", "addabs",
                    "sub", "subabs", "mult",
                     "div", "storend"};

const char* ld[] = {"lsh", "rsh", "ldmq"};

const char* di[] = {".set", ".org", ".align",
                    ".wfill", ".word"};

/*
Returns the point in the vector where the comment has ended
*/
int ignore_comment(char* entrada, int i, int tamanho){
  for(int j = i; entrada[j] != '\n' && j < tamanho; j++)
    i = j + 1;
  return i;
}

/*
Returns the type of the word
*/
Types find_type(char *ptr, int i, int word_beggining, char *complement, Types *lid){
    Types type;
    //If the word begins with a '.', it is a directive
    if(ptr[0] == '.'){
      type = DIRECTIVE;
      //checks if it is a valid directive
      if(!is_directive(ptr))
        return ERRO_LEXICO;

      //Finds the number of complements it receives and saves the command in lid
      if(strcmp(ptr, ".set") == 0){
        *complement = 2;
        *lid = SET;
      }
      else if(strcmp(ptr, ".wfill") == 0){
        *complement = 2;
        *lid = WFILL;
      }
      else{
        if(strcmp(ptr, ".word") == 0)
          *lid = WORD;
        else if(strcmp(ptr, ".align") == 0)
          *lid  = ALIGN;
        else
          *lid = ORG;
        *complement = 1;
      }
    }
    //If the word begins with ':' it is a rotulo
    else if(ptr[i - word_beggining -1] == ':'){
      type = ROTULO;

      //Checks if the word is valid
      if(rotulo_check(ptr, i, word_beggining))
        type = ERRO_LEXICO;
    }
    else if((*complement) != 0){
      type = complement_type(ptr, i, word_beggining, *lid, *complement);
      (*complement)--;
    }
    //Finds if a word is a instruction or a complement and, if so, of what type
    else{
      type = INSTRUCTION;
      if(is_instruction(ptr) == 1){
        *lid = INSTRUCTION;
        *complement = 1;
      }
      else if(is_instruction(ptr) == 2);
      else if(complement_type(ptr, i, word_beggining, *lid, *complement) == HEXADECIMAL){
        type = HEXADECIMAL;
        (*complement)--;
      }
      else if(complement_type(ptr, i, word_beggining, *lid, *complement) == DECIMAL){
        type = DECIMAL;
        (*complement)--;
      }
      else if(complement_type(ptr, i, word_beggining, *lid, *complement) == NAME){
        type = NAME;
        (*complement)--;
      }
      else
        type = ERRO_LEXICO;
    }
    //Checks if there is any incoherence between the type chosen and the line as a whole
    type = check_for_errors(type, *lid, *complement);

    return type;
}

/*
Checks if there is any lexical error in the rotulo word
Returns 0 if the word is valid and n > 1 if the word is invalid
*/
int rotulo_check(char *ptr, int i, int word_beggining){
  char double_dot = 0;
  //Checks if the first char is a number, because, if so, it is invalid
  if (ptr[0] >= '0' && ptr[0] <= '9')
    return 2;

  //Checks if there is more than 1 ':' and if all the character are valid
  for(int k = 0; k < (i - word_beggining - 1); k++){
    if(ptr[k] == ':')
      double_dot++;
    if(ptr[k] != '_' && (ptr[k] < '0' || (ptr[k] > '9' && ptr[k] < 'a') || (ptr[k] > 'z')))
      return 2;
  }
  return (double_dot > 1);
}

/*
Checks if a word is a valid instruction
Returns 1 if the instruction receives 1 parameter, 2 if it receives 2 and 0 if it
isn't a valid word
*/
int is_instruction(char *ptr){

  //Checks if the word is a instruction that has a parameter
  for(int i = 0; i < N_INSTRUCTIONS_C; i++)
    if(strcmp(ptr, lc[i]) == 0)
      return 1;

  //Checks if the word is a instruction that doesn't receive a parameter
  for(int j = 0; j < N_INSTRUCTIONS_N; j++)
    if(strcmp(ptr, ld[j]) == 0)
      return 2;

  //Returns 0 if the word isn't a valid instruction
  return 0;
}

/*
Return the type of complement (decimal, hexadecimal or name)
*/
Types complement_type(char *ptr, int i, int word_beggining, Types lid, int complement){
  Types type;

  //if it begins with 0x it means it is hexadecimal
  if (ptr[0] == '0' && ptr[1] == 'x'){

    //Checks if the word has a valid number of digits
    if(i - word_beggining > 12)
      return ERRO_LEXICO;

    //Checks if every digit is valid for a hexadecimal number
    for(int j = 2; j < i - word_beggining; j++)
        if (ptr[j] > 'f' || (ptr[j] < 'a' && ptr[j] > '9') || ptr[j] < '0')
          return ERRO_LEXICO;

    /*
    //Checks if the hexadecimal value is inside the valid range
      if(!inside_range(ptr, i, word_beggining, HEXADECIMAL))
        return ERRO_GRAMATICAL;
    */
    type = HEXADECIMAL;
  }else if((ptr[0] >= '0' && ptr[0] <= '9' ) || ptr[0] == '-'){ //It means it is an integer

    //Checks if every digit is valid for a decimal integer
    for(int j = 1; j < i - word_beggining - 1; j++)
        if (ptr[j] > '9' || ptr[j] < '0')
          return ERRO_LEXICO;
    //Checks if the number is inside the valid range for each instruction or directive
    if(!inside_range(ptr, i, word_beggining, DECIMAL, lid, complement))
      return ERRO_GRAMATICAL;

    type = DECIMAL;
  }else{ //If a complement is neither a decimal nor a hexadecimal then it is a NAME
    //Checks if all the character are valid for a name
    for(int j = 0; j < i - word_beggining - 1; j++)
        if (ptr[j] != '_' && ((ptr[j] > '9' && ptr[j] < 'a') || ptr[j] < '0' || ptr[j] > 'z'))
          return ERRO_LEXICO;
    type = NAME;
  }
  return type;
}

/*
Checks if the numbers are inside the valid range for the instruction they are for
Returns 0 if the number is off-limits and 1 if it is valid
*/
int inside_range(char* ptr, int i, int word_beggining, Types type, Types lid, int complement){
  if(type == HEXADECIMAL){
    if(i - word_beggining > 12)
      return 0;
    /*
        Verifica se o valor em hex esta dentro do intervalo
    int hex = get_hex(ptr, i, word_beggining);
    if(hex > 1023 || hex < 0)
      return 0;
    */
  }else if(type == DECIMAL){
    long int sum = get_dec(ptr, i, word_beggining);

    //Analyses the valid interval based on the instruction/directive the number is meant for
    if((lid == INSTRUCTION || lid == ALIGN || lid == ORG) && (sum > 1023 || sum < 0))
      return 0;
    else if(lid == WORD && (sum < -1*pot(31, 2) || sum > pot(31, 2) - 1))
      return 0;
    else if(lid == SET && (sum < 0 || sum > (pot(31, 2) - 1)))
      return 0;
    else if(lid == WFILL){
      if(complement == 2 && (sum > 1023 || sum < 0))
        return 0;
      else if (complement == 1 && (sum < -1*pot(31, 2) || sum > ((pot(31, 2) - 1))))
        return 0;
    }
  }
  return 1;
}

/*
Retorns the power of a number by a expoent
*/
long int pot(int e, int p){
  long int mul = 1;
  for(int i = 0; i < e; i++)
    mul = mul*p;
  return mul;
}

/*
Checks if a word is a valid directive
Returns 0 if it isn't a directive and 1 if it is
*/
int is_directive(char* ptr){
  //For all possible directives, checks if any of them is equal to the word
  for(int i = 0; i < N_DIRECTIVES; i++)
    if(strcmp(ptr, di[i]) == 0)
      return 1;
  return 0;
}

/*
  Returns the decimal equivalent of a hexadecimal number expressed as a string
*/
int get_hex(char *ptr, int i, int word_beggining){
  int sum = 0;
  for(int j = 2; j < i - word_beggining; j++){
    if(ptr[j] > '9')
      sum = sum + ((ptr[j] - 87)*pot(i - word_beggining - j - 1, 16));
    else
      sum = sum + ((ptr[j] - '0')*pot(i - word_beggining - j - 1, 16));
  }
  return sum;
}

/*
  Returns the decimal equivalent of a decimal number expressed as a string
*/
long int get_dec(char *ptr, int i, int word_beggining){
  long int sum = 0;
  int u = 0;
  if(ptr[0] == '-')
    u = 1;
  for(int j = i - word_beggining - 1 - u, k = u; j >= 0; j--, k++){
    sum = sum + ((ptr[k]-'0') * pot(j, 10));
  }
  if(ptr[0] == '-')
    sum = sum * -1;
  return sum;
}

/*
Checks if there is anything invalid with the type chosen, such as invalid type
of complement or invalid number of complements
Returns the original type if it is valid and the type of ERROR if it is not
*/
Types check_for_errors(Types type, Types lid, char complement){
  if(type == ERRO_LEXICO)
    return type;
  if(complement == 1 && type != INSTRUCTION && type != DIRECTIVE){
    if(lid == SET && type != NAME)
      return ERRO_GRAMATICAL;
    else if(lid == WFILL && type != DECIMAL)
      return ERRO_GRAMATICAL;
  }else if(type != INSTRUCTION && type != DIRECTIVE && type != ROTULO && complement == 0){
    if(lid == INSTRUCTION && type != DECIMAL && type != NAME && type != HEXADECIMAL)
      return ERRO_GRAMATICAL;
    else if(lid == SET && type != HEXADECIMAL && type != DECIMAL)
      return ERRO_GRAMATICAL;
    else if(lid == ALIGN && type != DECIMAL)
      return ERRO_GRAMATICAL;
    else if(lid == WFILL && type != HEXADECIMAL && type != DECIMAL && type != NAME)
      return ERRO_GRAMATICAL;
    else if(lid == ORG && type != DECIMAL && type != HEXADECIMAL)
      return ERRO_GRAMATICAL;
  }

  return type;
}
