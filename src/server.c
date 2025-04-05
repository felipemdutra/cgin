#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cgin/declarations.h"
#include "cgin/utils/socket.h"
#include "cgin/server.h"
#include "cgin/route.h"
#include "cgin/client.h"

#define INITIAL_ROUTE_CAPACITY 5 

router_t* new_router(const int port) {
    router_t *r = malloc(sizeof(router_t));
    if (!r) {
        return NULL;
    }

    // Create and bind new router's socket.
    r->sockfd = new_socket();
    if (r->sockfd < 0) {
        return NULL;
    }

    if (bind_socket(r->sockfd, port) < 0) {
        return NULL;
    }

    r->port = port;

    // Set initial capacity. We need to reallocate memory for r->routes 
    // everytime route_count is greater than this.
    r->route_capacity = INITIAL_ROUTE_CAPACITY;
    r->route_count = 0;

    r->routes = malloc(r->route_capacity * sizeof(route_t));

    r->GET = routeGET;
    
    return r;
}

void free_router(router_t *r) {
    free(r);
    r = NULL;
}

int router_run(router_t* r) {
    while (1) {
        if (sock_listen(r->sockfd) < 0) {
            printf("failed to listen for connections: %s\n", strerror(errno));
            continue;
        }

        client_t *client = sock_accept_conn(r->sockfd);
        if (client->sockfd < 0) {
            printf("failed to accept connection: %s\n", strerror(errno));
            continue;
        }

        // Allocating and freeing memory for every request might not be the
        // best way of doing this but oh well...
        struct ReqInfo* info = read_req(client);
        if (!info) {
            free_client(client);
            return -1;
        }

        if (handle_req(r, client, info) < 0) {
            free_client(client);
            free(info);
            continue;
        }

        free(info);
        free(client);
    } 
    
    return 0;
}

