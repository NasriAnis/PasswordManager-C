#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/misc/include/wrapper.h"
#include "../../src/misc/include/helper.h"
#include "../../src/auth/include/signup.h"
#include "../../src/auth/include/login.h"

void user_creation(char* username_buffer, char* password_buffer, size_t user_size, size_t pass_size) {
  // Takes user credential
  printf("please create a user.\n");

  while (1){
    printf("Username : ");
    int flag1 = f_gets(username_buffer, user_size);

    if (flag1 == 0){
      printf("Input too long, repeat...\n");
    } else{
      trim(username_buffer);
      break;
    }
  }

  while (1){
    printf("Password : ");
    int flag2 = f_gets(password_buffer, pass_size);

    if (flag2 == 0){
      printf("Input too long, repeat...\n");
    } else{
      trim(password_buffer);
      break;
    }
  }

  create_user(username_buffer, password_buffer);
}
void authentication(char* username_buffer, char* password_buffer, size_t user_size, size_t pass_size) {
  do {

    while (1){
      printf("Enter your username : ");
      int flag1 = f_gets(username_buffer, user_size);

      if (flag1 == 0){
        printf("Input too long, repeat...\n");
      } else{
        trim(username_buffer);
        break;
      }
    }

    while (1){
      printf("Enter your password : ");
      int flag2 = f_gets(password_buffer, pass_size);

      if (flag2 == 0){
        printf("Input too long, repeat...\n");
      } else{
        trim(password_buffer);
        break;
      }
    }

  } while (authenticate(password_buffer, username_buffer) != 0);
}
