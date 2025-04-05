#include <cgin/server.h>
#include <stdio.h>

#include "cgin/declarations.h"

int home_handler(client_t* c) {
    (void)c;
    printf("Welcome home!\n");
    return 0;
}

int main() {
    router_t* r = new_router(8080);

    r->GET(r, "/home", home_handler);

    router_run(r);
    free_router(r);
}

