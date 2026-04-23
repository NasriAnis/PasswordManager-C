
#ifndef CRED_CLI_H
#define CRED_CLI_H

typedef struct {
  char username[1080];
  char passwd[1080];
} user_t;

extern user_t user;

// Function declarations
void cred_init(void);
void cred_cleanup(void);

#endif

