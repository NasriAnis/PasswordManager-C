#ifndef AUTH_H
#define AUTH_H

typedef struct {
  char username[60];
  char passwd[60];
} user_t;

int authentificate(char *password_buffer);
int is_there_users();
int create_user();
#endif
