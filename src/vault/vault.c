#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "include/vault.h"
#include "include/vault_helper.h"

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

  int flag;
  int i = 0;
  Entry *results = NULL;

  char word1[256];
  char word2[256];
  char word3[256];
  char line[4024];

  while (fgets(line, sizeof(line), fptr) != NULL) {

    if (sscanf(line, "%255s %255s %255s", word1, word2, word3) != 3){
      continue;
    }

    // disable the flag
    flag = 0;

    if (search_type == 1){
      if (strcmp(word1, input) == 0) {
        flag = 1;
      }
    }
    else if (search_type == 2){
      if (strcmp(word2, input) == 0) {
        flag = 1;
      }
    }

    if (flag == 1){
      Entry *tmp = realloc(results, (i + 1) * sizeof(Entry));

      if (!tmp){free(results); return NULL;}
      results = tmp;

      results[i].site = strdup(word1);
      results[i].username = strdup(word2);
      results[i].password = strdup(word3);

      i = i + 1;
    }
  }

  Entry *tmp = realloc(results, (i + 1) * sizeof(Entry));
  if (!tmp) { free(results); return NULL; }
  results = tmp;

  // sentinel end delimitter
  results[i] = (Entry){NULL, NULL, NULL};

  fclose(fptr);
  return results;
}

Entry* dump_all(char* file_name){
  FILE *fptr;
  fptr = F_open(file_name, "r");

  int i = 0;
  Entry *results = NULL;

  char word1[256];
  char word2[256];
  char word3[256];
  char line[4024];

  while (fgets(line, sizeof(line), fptr) != NULL) {
    if (sscanf(line, "%255s %255s %255s", word1, word2, word3) != 3){
      continue;
    }
    Entry *tmp = realloc(results, (i + 1) * sizeof(Entry));

    if (!tmp){free(results); return NULL;}
    results = tmp;

    results[i].site = strdup(word1);
    results[i].username = strdup(word2);
    results[i].password = strdup(word3);

    i = i + 1;
  }

  Entry *tmp = realloc(results, (i + 1) * sizeof(Entry));
  if (!tmp) { free(results); return NULL; }
  results = tmp;

  // sentinel end delimitter
  results[i] = (Entry){NULL, NULL, NULL};

  return results;
}

int delete_password(char* site, char* username){
  char word1[256];
  char word2[256];
  char word3[256];
  char line[4096];

  FILE *fptr = F_open("user.bin", "r");
  if (!fptr) return -1;

  while (fgets(line, sizeof(line), fptr) != NULL) {

    sscanf(line, "%255s %255s %255s", word1, word2, word3);

    if (strcmp(word1, site) == 0 && strcmp(word2, username) == 0) {
    }
    else {
      F_write("temp.bin",  line, 0);
    }

  }

  fclose(fptr);

  if (rename("temp.bin", "user.bin") != 0) {
    return -1;
  }

  return 0;
}
