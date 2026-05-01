#ifndef VAULT_HELPER_H
#define VAULT_HELPER_H

#include <stdio.h>

int F_exist(char* file_name);
int new_line(char *file_name, int num);
int F_write(char* file_name, char* input, int new_line);
FILE *F_open(char* file_name, char* type);

#endif
