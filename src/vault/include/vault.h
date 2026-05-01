#ifndef VAULT_H
#define VAULT_H

typedef struct {
  char *site;
  char *username;
  char *password;
} Entry;

Entry* dump_all(char* file_name);
char** Cred_search(char* file_name);
int delete_password(char* site, char* username);
Entry* search(char* file_name,char* input, int search_type);

#endif
