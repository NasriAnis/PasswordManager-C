#include <stdio.h>

// debugging purpose function
void print_hex(const unsigned char* data, size_t len){
  for(size_t i = 0; i < len; i++){
    printf("%02x", data[i]);
  }
  printf("\n");
}
