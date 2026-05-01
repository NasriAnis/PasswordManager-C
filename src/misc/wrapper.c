#include <stdio.h>
#include <string.h>
#include <string.h>

int f_gets(char* input, size_t size){
  // This function adds a null terminator
  // at the new line of a string
  if(fgets(input, size, stdin) == NULL) {
    return -1;  // Error
  }
 
  // If newline exists, input fits
  if(strchr(input, '\n')) {
    input[strcspn(input, "\n")] = '\0';
    return 1;  // Success
  } else {
    // Flush remaining input
    int c;
    while((c = getchar()) != '\n' && c != EOF);
    input[0] = '\0';
    return 0;  // Input too long
  }
}

void str_cpy(char* dest, char* src, size_t dest_size){
  strncpy(dest, src,  dest_size - 1);
  dest[sizeof(dest) - 1] = '\0';
}
