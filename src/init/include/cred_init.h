#ifndef CRED_H
#define CRED_H

typedef struct {
    char password[1080];
    char username[1080];
} cred;

// Declare global variable
extern cred global_credentials;

// Function declarations
void cred_init(void);
void cred_cleanup(void);

#endif
