#ifndef AUTH_H
#define AUTH_H

typedef struct {
  char username[60];
  char passwd[60];
} user_t;

int authenticate(char *password_buffer);
int create_user(char *username, char *password);

#endif
