#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>

char* encode_base64(char* bin);
char* decode_base64(const char* b64);
char* encode_base64_bin(const char* bin, size_t bin_len);
unsigned char* decode_base64_bin(const char* b64, size_t *out_len);

#endif
