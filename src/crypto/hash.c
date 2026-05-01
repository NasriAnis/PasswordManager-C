#include <argon2.h>
#include <sodium.h>
#include <string.h>
#include <stdint.h>

#include "include/hash.h"

#define CIPHERTEXT_LEN (crypto_secretbox_MACBYTES + MESSAGE_LEN)
#define MESSAGE_LEN 4

#define ui32 uint32_t

// Hash the password and return success value
int hash_password(const char *password, char encoded[ENCODED_LEN]) {
  unsigned char salt[16] = {0};
  int rc = argon2id_hash_encoded(2,       // time cost (iterations)
                                 1 << 16, // memory cost (64 MB)
                                 1,       // parallelism
                                 password, strlen(password), salt, sizeof(salt),
                                 HASH_LEN, encoded, ENCODED_LEN);
  return rc == ARGON2_OK ? 0 : -1;
}

// Verify a password against a stored hash
int verify_password(const char *password, const char *encoded) {
  int rc = argon2id_verify(encoded, password, strlen(password));
  return rc == ARGON2_OK ? 0 : -1; // 0 = match
}
