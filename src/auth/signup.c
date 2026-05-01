#include <stdio.h>
#include <stdlib.h>

#include "../crypto/include/base64.h"
#include "../crypto/include/hash.h"
#include "../vault/include/vault_helper.h"

// Create and save a user to the data base
void create_user(char* username, char* password) {
  char* b64_username;
  char* b64_password;

  // hash the password : encoded
  char hash_pass[ENCODED_LEN];
  hash_password(password, hash_pass);

  b64_username = encode_base64(username);
  b64_password = encode_base64(hash_pass);
 
  // save user
  F_write("user.bin", b64_username, 0);
  F_write("user.bin", " ", 0);
  F_write("user.bin", b64_password, 1);
  printf("User created and saved.\n");

  free(b64_username);
  free(b64_password);
}
