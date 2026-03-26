#include <stdio.h>
#include <string.h>

#include "auth.h"
#include "crypto.h"
#include "vault.h"

int authentificate(char *password_buffer) { return 0; }

int is_there_users() { 
  int x = F_exist("users.bin");
  return x; 
}

int create_user() {
  user_t user;
  char encoded[ENCODED_LEN];

  // Takes user credential
  printf("please create a user.\n");
  printf("Username : ");
  fgets(user.username, sizeof(user.username), stdin);
  user.username[strcspn(user.username, "\n")] = '\0';

  printf("Password : ");
  fgets(user.passwd, sizeof(user.passwd), stdin);
  user.passwd[strcspn(user.passwd, "\n")] = '\0';

  // hash the password : encoded
  if (hash_password(user.passwd, encoded) != 0){
    printf("Error hashing the password\n");
  }
  
  // save user
  F_write("users.bin", user.username);
  F_write("users.bin", encoded);
  printf("User created and saved.\n");
  return 0;
}
