#include <stdio.h>
#include <string.h>

#include "auth.h"
#include "vault.h"

char password_buffer[50];

int main(int argc, char *argv[]) {

  // if no user file exists prompt to create a user
  if (F_exist("user.bin") == 1) {
    user_t user;

    // Takes user credential
    printf("please create a user.\n");
    printf("Username : ");
    fgets(user.username, sizeof(user.username), stdin);
    user.username[strcspn(user.username, "\n")] = '\0';

    printf("Password : ");
    fgets(user.passwd, sizeof(user.passwd), stdin);
    user.passwd[strcspn(user.passwd, "\n")] = '\0';
    create_user(user.username, user.passwd);
  }

  // if no argument are specififed 
  if (argc < 2) {
    do {
      printf("Enter your password : ");
      fgets(password_buffer, sizeof(password_buffer), stdin);
      password_buffer[strcspn(password_buffer, "\n")] = '\0';
    } while (authenticate(password_buffer) != 0);

  }

  // if arguments are specified
  else {
  printf("Runnig with argument : %s\n", argv[2]);
  }
  return 0;
}
