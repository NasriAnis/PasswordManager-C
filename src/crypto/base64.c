#include <argon2.h>
#include <sodium.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "include/base64.h"

#define CIPHERTEXT_LEN (crypto_secretbox_MACBYTES + MESSAGE_LEN)
#define MESSAGE_LEN 4

#define ui32 uint32_t

char* encode_base64(char* bin){
  // remove new linw charactere before encoding
  size_t len = strlen(bin);
  if (len > 0 && bin[len - 1] == '\n') {
    bin[len - 1] = '\0';
  }

  size_t l_len = sodium_base64_ENCODED_LEN(strlen(bin), sodium_base64_VARIANT_ORIGINAL);
  char *b64 = malloc(l_len);
  sodium_bin2base64(b64, l_len, (unsigned char *)bin, strlen(bin), sodium_base64_VARIANT_ORIGINAL);

  return b64;
}

char* encode_base64_bin(const char* bin, size_t bin_len){
  // size_t b_len = crypto_secretbox_NONCEBYTES + crypto_secretbox_MACBYTES + bin_len + sizeof(ui32);
  size_t l_len = sodium_base64_ENCODED_LEN(bin_len, sodium_base64_VARIANT_ORIGINAL);
  char *b64 = malloc(l_len);
  sodium_bin2base64(b64, l_len, (unsigned char *)bin, bin_len, sodium_base64_VARIANT_ORIGINAL);
  return b64;
}

char* decode_base64(const char* b64){
  size_t b64_len = strlen(b64);
  size_t bin_maxlen = 1024;
  unsigned char* bin = malloc(bin_maxlen);
  size_t bin_len = 0;

  int ret = sodium_base642bin(
    bin, bin_maxlen,
    b64, b64_len,
    NULL,        // don't ignore any characters
    &bin_len,
    NULL,        // don't need pointer to end
    sodium_base64_VARIANT_ORIGINAL
  );
  if (ret != 0){ printf("Decoding Error !"); }
  bin[bin_len] = '\0';

  return (char *)bin;
}

unsigned char* decode_base64_bin(const char* b64, size_t *out_len) {
    size_t bin_maxlen = strlen(b64);  // decoded is always shorter
    unsigned char *bin = malloc(bin_maxlen);
    sodium_base642bin(bin, bin_maxlen, b64, strlen(b64),
                      NULL, out_len, NULL,
                      sodium_base64_VARIANT_ORIGINAL);
    return bin;
}
