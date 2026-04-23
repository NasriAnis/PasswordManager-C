#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/include/misc.h"
#include "../../src/include/crypto.h"
#include "../../src/include/vault.h"

#include "../include/cred_cli.h"

void add(char *tokens[]) {
  char *site = tokens[1];
  char *login = tokens[2];
  char *pass = tokens[3];
  char user_input[1080];

  printf("Do you wanna add this account to the database ?\n");
  printf("Site : %s\n", site);
  printf("User : %s\n", login);
  printf("Password : %s\n", pass);

  printf("(Y/n) : ");
  f_gets(user_input, sizeof(user_input));
  printf("\n");

  if (strcmp(user_input, "n") != 0) {
    size_t blob_len = 0;
    unsigned char *encrypted_pass =
        crypto_encrypt((unsigned char *)user.passwd, (unsigned char *)pass,
                       strlen(pass), &blob_len);

    char *b64_site = encode_base64(site);
    char *b64_login = encode_base64(login);
    char *b64_pass = encode_base64_bin((char *)encrypted_pass, blob_len);

    F_write("user.bin", b64_site, 0);
    F_write("user.bin", " ", 0);
    F_write("user.bin", b64_login, 0);
    F_write("user.bin", " ", 0);
    F_write("user.bin", b64_pass, 1);

    free(encrypted_pass);
    free(b64_login);
    free(b64_site);
    free(b64_pass);
  }
}

void show(char *tokens[]) {
  // check if the tokens contains "="
  int flag = 0;
  int len = strlen(tokens[1]);

  int i;
  for (i = 0; len >= i; i++) {
    if (tokens[1][i] == '=') {
      flag = 1;
    }
  }

  if (flag != 1){
    printf("Syntax error expected : \
           show site=[site] or show user=[username]");
    return;
  }

  Entry *result = NULL;
  char *key = strtok(tokens[1], "=");
  char *value = strtok(NULL, "=");

  size_t decoded_len = 0;

  char *b_key1 = encode_base64(value);

  if (strcmp(key, "site") == 0) {
    result = search("user.bin", b_key1, 1);
  }
  else if (strcmp(key, "user") == 0) {
    result = search("user.bin", b_key1, 2);
  }
  else {
    printf("Syntax error expected : \
           show site=[site] or show user=[username]");
  }

  if (result == NULL) {
    printf("Error: Not found\n");
    return;
  }
 
 // logic change loop throught 3 words at a time
  int j;
  for (j = 0; 1; j++){

    // check for sentinel
    if (result[j].site == NULL \
      && result[j].username == NULL \
      && result[j].password == NULL){
      break;
    }

    char *decoded_site = decode_base64(result[j].site);
    char *decoded_username = decode_base64(result[j].username);
    unsigned char *decoded_password =
        decode_base64_bin(result[j].password, &decoded_len);

    unsigned char *clear_passwd = crypto_decrypt(
        (const unsigned char *)user.passwd, (unsigned char *)decoded_password);

    printf("%s %s %s", decoded_site, decoded_username, clear_passwd);
  }

  free(b_key1);
  free(result);
}
