#ifndef __SOCKET_H__
#define __SOCKET_H__

#define MAX_BACKLOG 10

/**
 * Creates and returns a new AF_INET socket.
 * @return 0 on success, -1 on failure.
 */
int new_socket();

/**
 * Binds the given socket on the specified port.
 *
 * @param sockfd The socket to bind
 * @param port The port to bind the socket to.
 * @return 0 on success, -1 on failure.
 */
int bind_socket(int sockfd, int port);
int sock_listen(int sock);
int sock_accept_conn(int sock);

#endif

