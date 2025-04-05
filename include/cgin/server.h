#ifndef __SERVER_H__
#define __SERVER_H__

#include <stddef.h>

#include "cgin/declarations.h"

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

