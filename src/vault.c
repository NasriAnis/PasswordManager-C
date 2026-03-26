#include <stdio.h>
#include <stdlib.h>
#include "vault.h"

int F_exist(char* file_name){
  FILE* fptr;
  fptr = fopen(file_name, "r");
  if (fptr == NULL){
    return 1;
  }
  fclose(fptr);
  return 0;
}

int F_write(char* file_name, char* input){
  FILE* fptr;
  fptr = fopen(file_name, "a");
  fputs(input, fptr);
  fputc('\n', fptr);
  fclose(fptr);
  return 0;
}

int F_search(char* file_name, char* in_to_search, char search_type){
  return 0;
}
