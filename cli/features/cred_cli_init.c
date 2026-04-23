#include <string.h>
#include "../include/cred_cli.h"

user_t user = {0};  // NOT a pointer

void cred_init(void) {
    memset(&user, 0, sizeof(user_t));
}

void cred_cleanup(void) {
    memset(&user, 0, sizeof(user_t));
}
