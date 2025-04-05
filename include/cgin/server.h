#ifndef __SERVER_H__
#define __SERVER_H__

#include <stddef.h>

#include "cgin/route.h"

typedef void (*router_get)(char*, char*, route_handler_fn);

typedef struct {
    int port;
    int sockfd;            // Router's socket file descriptor

    route_t *routes;       // Array of routes
    size_t route_count;    // Current route count
    size_t route_capacity; /* Max routes before having to reallocate memory for 
                              route_t *routes */
    router_get GET;
} router_t;

/**
 * Allocates memory for a router_t 
 *
 * @param port The port the router is going to listen in.
 * @return A pointer to the allocated router_t
 */
router_t* new_router(const int port);

/**
 * Frees the memory allocated for given router_t
 *
 * @param The router that's going to be freed
 */
void free_router(router_t *r);

int router_run(router_t* r);
 
#endif

