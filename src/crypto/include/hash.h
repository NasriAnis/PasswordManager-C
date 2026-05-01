#ifndef HASH_H
#define HASH_H

#include <stddef.h>

#define HASH_LEN 32
#define ENCODED_LEN 128

int verify_password(const char *password, const char *encoded);
int hash_password(const char *password, char encoded[ENCODED_LEN]);

#endif
