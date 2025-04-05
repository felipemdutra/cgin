#include "cgin/client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

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

int serve_html(client_t *client, const char *file_path) {
    printf("HELLO!\n");
    FILE *file = fopen(file_path, "r");
    if (!file) {
        perror("FAILED TO OPEN FILE");
        const char *html_not_found = "<html><body><h1>404 Not Found</h1></body></html>";
        size_t not_found_len = strlen(html_not_found);
        char response[1024];
        int res_len = snprintf(response, sizeof(response), 
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/html\r\n"
                "Content-Length: %zu\r\n\r\n"
                "%s", not_found_len, html_not_found);
        if (send(client->sockfd, response, res_len, 0) < 0) {
            printf("HELLO THERE!\n");
            perror("FAILED TO SEND RESPONSE TO CLIENT");
            return -1;
        }

        printf("WHATS UP\n");
        return -1;
    }

    // sets cursor to the end of the file
    fseek(file, 0, SEEK_END);
    // gets the position of the cursor;
    long file_len = ftell(file);
    rewind(file);

    printf("HUH\n");
    char *html_content = malloc(file_len);
    if (!html_content) {
        fclose(file);
        printf("WEIRD\n");
        return -1;
    }

    size_t bytes_read = fread(html_content, 1, file_len, file);
    if (bytes_read != (size_t)file_len) {
        perror("FAILED TO READ FILE");
        free(html_content);
        return -1;
    }

    char headers[1024];

    int header_len = snprintf(headers, sizeof(headers), 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: %ld\r\n\r\n", file_len);

    // send file
    if (send(client->sockfd, headers, header_len, 0) < 0) {
        perror("FAILED TO SEND HEADERS TO CLIENT\n");
        free(html_content);
        return -1;
    }

    if (send(client->sockfd, html_content, file_len, 0) < 0) {
        perror("FAILED TO SEND FILE TO CLIENT\n");
        free(html_content);
        return -1;
    }

    free(html_content);
    fclose(file);
    printf("BYE BYE\n");
    return 0;
}

