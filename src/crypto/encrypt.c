#include <argon2.h>
#include <sodium.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "include/encrypt.h"

#define CIPHERTEXT_LEN (crypto_secretbox_MACBYTES + MESSAGE_LEN)
#define MESSAGE_LEN 4

#define ui32 uint32_t


unsigned char *crypto_encrypt(const unsigned char *key, const unsigned char *message, size_t message_len, size_t *blob_len) {
  size_t ctext_len = crypto_secretbox_MACBYTES + message_len;
  *blob_len  = crypto_secretbox_NONCEBYTES + ctext_len + sizeof(ui32);

  unsigned char *blob = malloc(*blob_len);
  if (!blob){ return NULL; }

  // save message lenght
  ui32 len32 = (ui32)message_len;
  memcpy(blob, &len32, sizeof(ui32));

  // unsigned char *nonce = out_blob;
  unsigned char* nonce = blob + sizeof(ui32);
 
  // unsigned char *ciphertext = out_blob + crypto_secretbox_NONCEBYTES;
  unsigned char* ctext = blob + crypto_secretbox_NONCEBYTES + sizeof(ui32);

  randombytes_buf(nonce, crypto_secretbox_NONCEBYTES);
  crypto_secretbox_easy(ctext, message, message_len, nonce, key);

  return blob;
}

unsigned char* crypto_decrypt(const unsigned char *key, unsigned char* blob){
  uint32_t len32;
  memcpy(&len32, blob, sizeof(uint32_t));
  size_t message_len = (size_t)len32;

  const unsigned char* nonce = blob + sizeof(ui32);
  const unsigned char* ctext = blob + crypto_secretbox_NONCEBYTES + sizeof(ui32);

  size_t ctext_len = crypto_secretbox_MACBYTES + message_len;
  // size_t blob_len  = crypto_secretbox_NONCEBYTES + ctext_len;

  unsigned char* plain_text = malloc(message_len + 1);
  if (!plain_text){ return NULL; }

  if (crypto_secretbox_open_easy(plain_text, ctext, ctext_len, nonce, key) != 0){
    free(plain_text);
    fprintf(stderr, "Decryption failed\n");
    return NULL;
  }
 
  plain_text[message_len] = '\0';
  return plain_text;
}
