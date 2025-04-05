#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "cgin/utils/socket.h"
#include "cgin/client.h"
#include "cgin/declarations.h"

static int enable_so_reuseaddr(int sock) {
    const int opt = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        return -1;
    }

    return 0;
}

int new_socket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        return -1;
    }

    // Allow socket to reuse the same address
    // This is needed for avoiding "Address already in use" errors.
    if (enable_so_reuseaddr(sock) < 0) {
        return -1;
    }

    return sock;
}

int bind_socket(int sockfd, int port) {
    struct sockaddr_in sock_addr;

    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    sock_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) < 0) {
        return -1;
    }

    return 0;
}

int sock_listen(int sock) {
    printf("Listening for connections...\n");
    if (listen(sock, MAX_BACKLOG) < 0) {
        return -1;
    }

    return 0;
}

client_t* sock_accept_conn(int sock) {
    int client_sock;
    
    struct sockaddr_in client_addr;

    socklen_t client_addr_len = sizeof(client_addr);

    client_sock = accept(sock, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_sock < 0) {
        return NULL;
    }

    client_t *client = new_client(client_sock, client_addr);
    if (!client) {
        perror("FAILED TO CREATE NEW CLIENT");
    }

    printf("Client successfully connected!\n");

    return client;
}

