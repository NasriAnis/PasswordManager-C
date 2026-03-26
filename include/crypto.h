#ifndef CRYPTO_H
#define CRYPTO_H

#define HASH_LEN 32
#define ENCODED_LEN 128

int hash_password(const char *password, char encoded[ENCODED_LEN]);
int verify_password(const char *password, const char *encoded);

#endif
