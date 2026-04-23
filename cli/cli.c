#include <stdio.h>
#include <string.h>

#include "../src/include/misc.h"
#include "../src/include/vault.h"

#include "include/cred_cli.h"
#include "include/authentication.h"
#include "include/password_handling.h"

int main(int argc, char *argv[]) {
  // initialize credentials space
  cred_init();

  // if no argument are specififed
  if (argc < 2) {
    char password_buffer[1080];
    char username_buffer[1080];
    char user_input[1080];
    char *tokens[64];
 
    // check credentials
    if (F_exist("user.bin") != 0) {
      user_creation(username_buffer, password_buffer, sizeof(username_buffer), sizeof(password_buffer));
    } else {
      authentication(username_buffer, password_buffer, sizeof(username_buffer), sizeof(password_buffer));
    }

    // save credential to a struct, the password will be used as an encryption key
    str_cpy(user.username, username_buffer, sizeof(user.username));
    str_cpy(user.passwd, password_buffer, sizeof(user.username));

    while (1) {
      printf("> ");
      f_gets(user_input, sizeof(user_input));
      int count = tokenize(user_input, tokens);

      if (strcmp(tokens[0], "add") == 0) {
        if (count != 4) {
          printf("Command layout : add [site] [username] [pasword]\n");
        } else {
          add(tokens);
        }
      } else if (strcmp(tokens[0], "show") == 0) {
        if (count != 2) {
          printf("Command layout : add site=[site] or add user=[username]\n");
        } else {
          show(tokens);
        }
      }
    }
  }

  // if arguments are specified
  else {
    printf("Runnig with argument : %s\n", argv[2]);
  }
  cred_cleanup();
  return 0;
}

