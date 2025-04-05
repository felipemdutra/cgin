#include <cgin/server.h>
#include <stdio.h>

#include "cgin/client.h"
#include "cgin/declarations.h"

int home_handler(client_t* c) {
    printf("HI THERE!\n");
    serve_html(c, "./html/homePage.html");

    return 0;
}

int main() {
    router_t* r = new_router(8080);

    r->GET(r, "/home", home_handler);

    router_run(r);
    free_router(r);
}

