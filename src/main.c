#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#include "request_parser.h"
#include "router.h"

#define BACKLOG 128

// handle_connection:
// thread entry: reads one request, routes it, then closes socket
static void *handle_connection(void *arg) {
    int client_fd = *(int *)arg;
    free(arg);

    Request req;
    if (read_request(client_fd, &req) == 0) {
        route(&req, client_fd);
    }

    close(client_fd);
    return NULL;
}

// parse_args:
// processes -p <port> and -h for help
// defaults to port 80 if none given
static uint16_t parse_args(int argc, char **argv) {
    int opt;
    uint16_t port = 80;

    while ((opt = getopt(argc, argv, "p:h")) != -1) {
        switch (opt) {
            case 'p':
                port = (uint16_t)atoi(optarg);
                break;
            case 'h':
            default:
                fprintf(stderr,
                        "Usage: %s [-p port]\n"
                        "  -p port   Listen port (default 80)\n",
                        argv[0]);
                exit(opt == 'h' ? 0 : 1);
        }
    }

    return port;
}

int main(int argc, char **argv) {
    uint16_t port = parse_args(argc, argv);

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        perror("socket");
        return 1;
    }

    int opt = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr   = { .s_addr = INADDR_ANY },
        .sin_port   = htons(port)
    };

    if (bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        return 1;
    }
    if (listen(listen_fd, BACKLOG) < 0) {
        perror("listen");
        return 1;
    }

    printf("Server listening on port %u\n", port);

    while (1) {
        struct sockaddr_in cli_addr;
        socklen_t cli_len = sizeof(cli_addr);
        int *pclient = malloc(sizeof(int));
        if (!pclient) continue;

        *pclient = accept(listen_fd,
                          (struct sockaddr *)&cli_addr,
                          &cli_len);
        if (*pclient < 0) {
            free(pclient);
            continue;
        }

        pthread_t tid;
        pthread_create(&tid, NULL, handle_connection, pclient);
        pthread_detach(tid);
    }

    close(listen_fd);
    return 0;
} 