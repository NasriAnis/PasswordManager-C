#include "auth.h"
#include <stdio.h>

char password_buffer[50];

int main(int argc, char *argv[]) {
  if (is_there_users() != 0) {
    create_user();
  }

  if (argc < 2) {
    printf("\n\nNo argument specififed running the CLI envirenment.\n");
    printf("Enter your password : ");
    fgets(password_buffer, sizeof(password_buffer), stdin);
    authentificate(password_buffer);
  } else {
    printf("Runnig with argument : %s\n", argv[2]);
  }

  return 0;
}
