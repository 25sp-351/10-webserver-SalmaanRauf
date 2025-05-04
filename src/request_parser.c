#include "request_parser.h"
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>

#define MAX_REQ_SIZE 8192

int read_request(int fd, Request *req) {
    char buf[MAX_REQ_SIZE + 1];
    int total = 0, n;

    // read until end of headers ("\r\n\r\n")
    while (total < MAX_REQ_SIZE) {
        n = recv(fd, buf + total, MAX_REQ_SIZE - total, 0);
        if (n <= 0) return -1;
        total += n;
        buf[total] = '\0';
        if (strstr(buf, "\r\n\r\n")) break;
    }

    // parse request-line
    char *line_end = strstr(buf, "\r\n");
    if (!line_end) return -1;
    *line_end = '\0';

    if (sscanf(buf, "%7s %255s %15s",
               req->method,
               req->uri,
               req->http_version) != 3) {
        return -1;
    }
    return 0;
}