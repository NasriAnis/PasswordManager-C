#include <stdio.h>
#include <string.h>
#include "auth.h"

int authentificate(char *password_buffer) { return 0; }

int is_there_users() { return 1; }

int create_user() {
  user_t user;

  // Get User credentials
  printf("please create a user.\n");
  printf("Username : ");
  fgets(user.username, sizeof(user.username), stdin);
  user.username[strcspn(user.username, "\n")] = '\0';

  printf("Password : ");
  fgets(user.passwd, sizeof(user.passwd), stdin);
  user.passwd[strcspn(user.passwd, "\n")] = '\0';

  // hash the password
  return 0;
}
