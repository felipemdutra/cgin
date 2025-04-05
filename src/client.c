#include "cgin/client.h"

#include <stdlib.h>

client_t* new_client(int client_sock, struct sockaddr_in client_addr) {
    client_t *client = malloc(sizeof(client_t));
    if (!client) {
        return NULL;
    }

    client->sockfd = client_sock;
    client->addr   = client_addr;

    return client;
}

void free_client(client_t *client) {
    free(client);
}

