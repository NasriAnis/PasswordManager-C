#ifndef VAULT_H
#define VAULT_H

typedef struct {
  char *site;
  char *username;
  char *password;
} Entry;

int F_exist(char* file_name);
int F_write(char* file_name, char* input, int new_line);
int new_line(char *file_name, int num);
// char** F_search(char* file_name,char* input, int search_type, int fetch_line);
Entry* search(char* file_name,char* input, int search_type);
char** Cred_search(char* file_name);

#endif
