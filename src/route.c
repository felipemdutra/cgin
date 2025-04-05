#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "cgin/route.h"
#include "cgin/declarations.h"

void routeGET(router_t* r, char *path, route_handler_fn handler_fn) {
    // If we reach max routes, allocate more memory.
    if (r->route_count >= r->route_capacity) {
        // Set realloc return to temporary variable, to avoid memory leaks.
        size_t new_capacity = r->route_capacity * 2;

        route_t* temp_arr = realloc(r->routes, new_capacity * sizeof(route_t));

        if (!temp_arr) {
            printf("FAILED TO REALLOCATE MEMORY FOR ROUTES ARRAY: %s\n", strerror(errno));
            return;
        } else {
            r->routes = temp_arr;
            r->route_capacity = new_capacity;
        }
    }

    // create new route
    route_t new_route;
    
    strcpy(new_route.path, path);
    new_route.method = "GET";
    new_route.handler = handler_fn;

    r->routes[r->route_count] = new_route;

    // route_count holds the index of the next route, which is why we add the 
    // new route, then increment the value.
    r->route_count++;
}

struct ReqInfo* read_req(client_t *client) {
    char buffer[512], method[10], path[256], version[20];
    struct ReqInfo *info = malloc(sizeof(struct ReqInfo));
    if (!info) {
        return NULL;
    }

    if (read(client->sockfd, buffer, sizeof(buffer)) < 0) {
        printf("FAILED TO READ CLIENT SOCK: %s\n", strerror(errno));
        free(info);
        return NULL;
    }

    if (sscanf(buffer, "%s %s %s", method, path, version) != 3) {
        printf("FAILED TO PARSE REQUEST\n");
        free(info);
        return NULL;
    }

    strcpy(info->path, path);
    strcpy(info->method, method);
    strcpy(info->version, version);

    return info;
}

int handle_req(router_t *r, client_t *client, struct ReqInfo* info) {
    /* Check if info's path exists in r's routes array */
    for (size_t i = 0; i < r->route_count; ++i) {

        // Reference route for cleaner code.
        route_t *route = &r->routes[i];

        // Both needs to be zero
        int is_path_equal = strcmp(route->path, info->path);
        int is_method_equal = strcmp(route->method, info->method);

        // We found the matching route, execute it's handler function
        if (is_path_equal == 0 && is_method_equal == 0) {
            route->handler(client);
            return 0;
        }
    }

    return -1;
}

