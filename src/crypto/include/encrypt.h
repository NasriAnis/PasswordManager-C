#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <stddef.h>

unsigned char* crypto_decrypt(const unsigned char *key, unsigned char* blob);
unsigned char* crypto_encrypt(const unsigned char *key, \
    const unsigned char *message, size_t message_len, size_t *blob_len);

#endif
