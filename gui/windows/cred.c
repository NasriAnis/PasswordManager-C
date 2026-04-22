#include <string.h>
#include "../include/cred.h"

cred global_credentials = {0};  // NOT a pointer

void cred_init(void) {
    memset(&global_credentials, 0, sizeof(cred));
}

void cred_cleanup(void) {
    memset(&global_credentials, 0, sizeof(cred));
}
