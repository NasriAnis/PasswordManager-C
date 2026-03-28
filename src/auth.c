#include <stdio.h>
#include "auth.h"
#include "crypto.h"
#include "vault.h"

char encoded[ENCODED_LEN];

int authenticate(char *password_buffer) {
  char encoded_saved_pass[256];
  F_search("user.bin", "password", encoded_saved_pass);

  if (verify_password(password_buffer, encoded_saved_pass) == 0){
    printf("Corret password\n");
    return 0;
  } else {
    printf("Wrong password !\n");
    return 1;
  }
}

// Create and save a user to the data base
int create_user(char* username, char* password) {
  // hash the password : encoded
  hash_password(password, encoded);
 
  // save user
  F_write("user.bin", "username");
  F_write("user.bin", username);
  F_write("user.bin", "password");
  F_write("user.bin", encoded);
  printf("User created and saved.\n");
  return 0;
}
