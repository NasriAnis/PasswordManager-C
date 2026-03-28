#ifndef VAULT_H
#define VAULT_H

int F_exist(char* file_name);
int F_write(char* file_name, char* input);
int F_search(char* file_name, char* in_to_search, char* word);

#endif
