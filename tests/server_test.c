#include <cgin/server.h>

int main() {
    router_t* r = new_router(8080);

    router_run(r);
    free_router(r);
}

