#ifndef __ROUTE_H__
#define __ROUTE_H__

typedef int (*route_handler_fn)(int client_sock);

typedef struct {
    const char *method;       // e.g. GET, POST, etc...
    const char *path;         // e.g. "/home/user/me"
    route_handler_fn handler;
} route_t;

#endif

