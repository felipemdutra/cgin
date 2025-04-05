#ifndef __DECLARATIONS_H__
#define __DECLARATIONS_H__

#include <stddef.h>

// Needed for routerGET function pointer
typedef struct router_t router_t;

typedef int (*route_handler_fn)(int client_sock);
typedef void (*routerGET)(router_t*, char*, route_handler_fn);

typedef struct {
    const char *method;       // e.g. GET, POST, etc...
    const char *path;         // e.g. "/home/user/me"
    route_handler_fn handler;
} route_t;

typedef struct router_t {
    int port;
    int sockfd;            // Router's socket file descriptor

    route_t *routes;       // Array of routes
    size_t route_count;    // Current route count
    size_t route_capacity; /* Max routes before having to reallocate memory for 
                              route_t *routes */
    routerGET GET;
} router_t;

struct ReqInfo {
    char method[10];
    char path[256];
    char version[20];
};

#endif

