#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "vault.h"

FILE *F_open(char* file_name, char* type){
  FILE *fptr;
  fptr = fopen(file_name, type);
  if (!fptr) {
      perror("fopen");
      return fptr;
  }
  return fptr;
} // dont forget to close

int F_exist(char *file_name) {
  FILE *fptr;
  fptr = F_open(file_name, "r");
  if (fptr == NULL) {
    return 1;
  }
  fclose(fptr);
  return 0;
}

int F_write(char *file_name, char *input, int new_line) {
  FILE *fptr;
  fptr = F_open(file_name, "a");
  fputs(input, fptr);
  for (int i = 0; new_line > i; i++){
    fputc('\n', fptr);
  }
  fclose(fptr);
  return 0;
}

int new_line(char *file_name, int num){
  FILE *fptr;
  fptr = F_open(file_name, "a");
  for (int i = 0; num > i; i++){
    fputc('\n', fptr);
  }
  fclose(fptr);
  return 0;
}

char** Cred_search(char* file_name){
  FILE *fptr;
  fptr = F_open(file_name, "r");
  char** results = malloc(sizeof(char*));

    char word1[256]; char word2[256];
    fscanf(fptr, "%255s %255s", word1, word2);

    results = realloc(results, 2 * sizeof(char*));
    results[0] = strdup(word1);
    results[1] = strdup(word2);

    return results;
}


Entry* search(char* file_name,char* input, int search_type){
  FILE *fptr;
  fptr = F_open(file_name, "r");

  if (search_type == 2){

    int i = 0;
    Entry *results = NULL;

    char word1[256];
    char word2[256];
    char word3[256];
    char line[4024];

    while (fgets(line, sizeof(line), fptr) != NULL) {
      // only enters while loop for some reason
      // fetches out the first line only
      // then skips all the others

      if (sscanf(line, "%255s %255s %255s", word1, word2, word3) == 3) {

        if (strcmp(word1, input) == 0) {
          Entry *tmp = realloc(results, (1 + i) * sizeof(Entry));

          if (!tmp){free(results); return NULL;}
          results = tmp;

          results[i].site = strdup(word1);
          results[i].username = strdup(word2);
          results[i].password = strdup(word3);
 
          // debugging purpose
          printf("%s, %s, %s", results[i].site, results[i].username, results[i].password);

          i = i + 1;
        }
      }
    Entry *tmp = realloc(results, (i + 1) * sizeof(Entry));
    if (!tmp) { free(results); return NULL; }
    results = tmp;
    results[i] = (Entry){NULL, NULL, NULL};  // sentinel
    return results;
    }
  }

  if (search_type == 3){

    int i = 0;
    Entry *results = NULL;

    char word1[256];
    char word2[256];
    char word3[256];
    char line[1024];

    while (fgets(line, sizeof(line), fptr) != NULL) {

      if (sscanf(line, "%255s %255s %255s", word1, word2, word3)== 3) {

        if (strcmp(word2, input) == 0) {
          Entry *tmp = realloc(results, (i + 1) * sizeof(char*));

          if (!tmp){free(results); return NULL;}
          results = tmp;

          results[i].site = strdup(word1);
          results[i].username = strdup(word2);
          results[i].password = strdup(word3);

          // debugging purpose
          printf("%s, %s, %s", results[i].site, results[i].username, results[i].password);

          i = i + 1;
        }
      }
    Entry *tmp = realloc(results, (i + 1) * sizeof(Entry));
    if (!tmp) { free(results); return NULL; }
    results = tmp;
    results[i] = (Entry){NULL, NULL, NULL};  // sentinel
    return results;
    }
  }


  printf("Nothing !");
  return NULL;
}

// Legacy Function
// char** F_search(char* file_name,char* input, int search_type, int fetch_line){
//   FILE *fptr;
//   fptr = F_open(file_name, "r");
//   char** results = malloc(sizeof(char*));
//
//   /* search types :
//    * 1- user credentials
//    * 2- user saved sites
//    * 3- user saved logins
//     */
//
//   if (search_type == 1){
//     char word1[256]; char word2[256];
//     fscanf(fptr, "%255s %255s", word1, word2);
//
//     results = realloc(results, 2 * sizeof(char*));
//     results[0] = strdup(word1);
//     results[1] = strdup(word2);
//
//     return results;
//   }
//   if (search_type == 2){
//     // int j = 0;
//     int i = 1;
//
//     char word1[256]; 
//     char word2[256]; 
//     char word3[256]; 
//     char line[1024];
//     Entry *results = NULL;
//
//     while (fgets(line, sizeof(line), fptr) != NULL) {
//       if (sscanf(line, "%255s %255s %255s", word1, word2, word3) == 3) {
//
//         if (strcmp(word1, input) == 0) {
//           results = realloc(results, i * sizeof(char*));
//
//           if (!results) return NULL;
//
//           results[i].site = strdup(word1);
//           results[i].username = strdup(word2);
//           results[i].password = strdup(word3);
//
//           i = i + 1;
//         }
//       }
//     results = realloc(results, (i + 1) * sizeof(Entry));
//     results[i] = (Entry){NULL, NULL, NULL};  // sentinel
//     return results;
//     }
//   }
//
//   if (search_type == 3){
//     results = realloc(results, 3 * sizeof(char*));
//
//     char word1[256]; 
//     char word2[256]; 
//     char word3[256]; 
//     char line[1024];
//
//     int j = 0;
//     int i = 1;
//
//     while (fgets(line, sizeof(line), fptr) != NULL) {
//       if (sscanf(line, "%255s %255s %255s", word1, word2, word3) == 3) {
//
//         if (strcmp(word2, input) == 0) {
//           results = realloc(results, 3 * i * sizeof(char*));
//
//           if (!results) return NULL;
//
//           results[0] = strdup(word1);
//           results[1] = strdup(word2);
//           results[2] = strdup(word3);
//
//           j = j + 3;
//           i = i + 1;
//         }
//       }
//     return results;
//     }
//   }
//   return NULL;
// }
