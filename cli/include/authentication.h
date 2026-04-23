#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <stdlib.h>

void user_creation(char* username_buffer, char* password_buffer, size_t user_size, size_t pass_size);
void authentication(char* username_buffer, char* password_buffer, size_t user_size, size_t pass_size);

#endif

