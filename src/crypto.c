#include <argon2.h>
#include <stdio.h>
#include <string.h>
#include "crypto.h"

// Hash the password and return success value
void hash_password(const char* password, char encoded[ENCODED_LEN]){
    unsigned char salt[16] = {0};
    int rc = argon2id_hash_encoded(
        2,           // time cost (iterations)
        1 << 16,     // memory cost (64 MB)
        1,           // parallelism
        password, strlen(password),
       salt, sizeof(salt),
        HASH_LEN,
        encoded, ENCODED_LEN
    );
    rc == ARGON2_OK ? 0 : -1;
    if (rc != 0){
      perror("Error hashing the password\n");
    }
}

// Verify a password against a stored hash
int verify_password(const char *password, const char *encoded) {
    int rc = argon2id_verify(encoded, password, strlen(password));
    return rc == ARGON2_OK ? 0 : -1;  // 0 = match
}
