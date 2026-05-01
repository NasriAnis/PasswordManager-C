#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/login.h"
#include "../crypto/include/base64.h"
#include "../crypto/include/hash.h"
#include "../vault/include/vault.h"


int authenticate(char *password_buffer, char* username_buffer) {
  char* encoded_saved_pass;
  char* decoded_saved_pass;
  char* saved_username;
  char* de_saved_username;
  char** b64_raw_value;
  int flag = 0;

  b64_raw_value = Cred_search("user.bin");
  saved_username = b64_raw_value[0];
  encoded_saved_pass = b64_raw_value[1];

  decoded_saved_pass = decode_base64(encoded_saved_pass);
  de_saved_username = decode_base64(saved_username);

  if (strcmp(username_buffer, de_saved_username) != 0){
    printf("wrong user.\n");
    flag = 1;
  }
  if (verify_password(password_buffer, decoded_saved_pass) != 0){
      printf("wrong password\n");
    flag = 1;
  }

  free(b64_raw_value);
  free(encoded_saved_pass);
  free(de_saved_username);

  if (flag != 0){
    return 1;
  } else { return 0; }
}
