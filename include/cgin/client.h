#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <netinet/in.h>

#include "cgin/declarations.h"

client_t* new_client(int client_sock, struct sockaddr_in client_addr);
void free_client(client_t *client);

#endif

