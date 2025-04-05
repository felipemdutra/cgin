#ifndef __ROUTE_H__
#define __ROUTE_H__

#include "cgin/declarations.h"

/**
 * Adds a new GET route to @param r->routes.
 *
 * @param r The router to add the route to.
 * @param path The route's path.
 * @param route_handler_fn The route's handler function.
 */
void routeGET(router_t *r, char *path, route_handler_fn);

/**
 * Parses client requests using client's file descriptor and returns the
 * requested path.
 *
 * @param clientsock The client's socket.
 * @return The requested path, which can then be used to compare to router_t's
 * routes path's, or NULL on failure.
 */
struct ReqInfo* read_req(client_t *client);

/**
 * This function compares the information given in @param info to all routes
 * associated with @param r. If no route matches, 404 that bitch, else we call
 * the matching route's handler function.
 */
int handle_req(router_t *r, client_t *client, struct ReqInfo* info);

#endif

