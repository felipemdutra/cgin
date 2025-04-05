#ifndef __DECLARATIONS_H__
#define __DECLARATIONS_H__

#include <netinet/in.h>
#include <stddef.h>

// Needed for routerGET function pointer
typedef struct router_t router_t;
typedef struct client_t client_t;

typedef int (*route_handler_fn)(client_t*);
typedef void (*routerGET)(router_t*, char*, route_handler_fn);

typedef struct {
    char *method;       // e.g. GET, POST, etc...
    char *path;         // e.g. "/home/user/me"
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

typedef struct client_t {
    int sockfd;
    struct sockaddr_in addr;
    
} client_t;

struct ReqInfo {
    char method[10];
    char path[256];
    char version[20];
};

#endif

