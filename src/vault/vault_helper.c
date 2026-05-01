#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "include/vault_helper.h"

FILE *F_open(char* file_name, char* type){
  FILE *fptr;
  fptr = fopen(file_name, type);
  if (!fptr) {
      return fptr;
  }
  return fptr;
} // dont forget to close

int F_exist(char *file_name) {
  FILE *fptr;
  fptr = F_open(file_name, "r");
  if (fptr == NULL) {
    return 1;
  }
  fclose(fptr);
  return 0;
}

int F_write(char *file_name, char *input, int new_line) {
  FILE *fptr;
  fptr = F_open(file_name, "a");
  fputs(input, fptr);
  for (int i = 0; new_line > i; i++){
    fputc('\n', fptr);
  }
  fclose(fptr);
  return 0;
}

int new_line(char *file_name, int num){
  FILE *fptr;
  fptr = F_open(file_name, "a");
  for (int i = 0; num > i; i++){
    fputc('\n', fptr);
  }
  fclose(fptr);
  return 0;
}
