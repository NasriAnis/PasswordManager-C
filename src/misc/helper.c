#include <ctype.h>
#include <string.h>

void trim(char *str) {
    // trim leading spaces
    int start = 0;
    while (isspace((unsigned char)str[start]))
        start++;

    // shift string left
    if (start > 0)
        memmove(str, str + start, strlen(str) - start + 1);

    // trim trailing spaces
    int end = strlen(str) - 1;
    while (end >= 0 && isspace((unsigned char)str[end]))
        str[end--] = '\0';
}

int tokenize(char* input, char** tokens){
  int count = 0;
  char *token = strtok(input, " ");
 
  while (token != NULL){
    tokens[count++] = token;
    token = strtok(NULL, " ");
  }
  return count;
}

