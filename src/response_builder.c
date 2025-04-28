#include "response_builder.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int send_response_internal(int fd,
                         const char *header,
                         const void *body,
                         size_t body_len) {
    // write header + body
    if (write(fd, header, strlen(header)) < 0) return -1;
    if (body_len > 0 && write(fd, body, body_len) < 0) return -1;
    return 0;
}

int send_response(int fd,
                  int status_code,
                  const char *status_text,
                  const char *content_type,
                  const void *body,
                  size_t body_len) {
    char header[512];
    snprintf(header, sizeof(header),
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "\r\n",
        status_code, status_text,
        content_type,
        body_len);

    return send_response_internal(fd, header, body, body_len);
}

int send_404(int fd) {
    const char *msg = "404 Not Found\n";
    return send_response(fd, 404, "Not Found", "text/plain",
                         msg, strlen(msg));
}

int send_400(int fd, const char *msg) {
    return send_response(fd, 400, "Bad Request",
                         "text/plain", msg, strlen(msg));
}

int send_405(int fd) {
    const char *msg = "405 Method Not Allowed\n";
    return send_response(fd, 405, "Method Not Allowed",
                         "text/plain", msg, strlen(msg));
}

int send_500(int fd) {
    const char *msg = "500 Internal Server Error\n";
    return send_response(fd, 500, "Internal Server Error",
                         "text/plain", msg, strlen(msg));
}

int send_505(int fd) {
    const char *msg = "505 HTTP Version Not Supported\n";
    return send_response(fd, 505, "HTTP Version Not Supported",
                         "text/plain", msg, strlen(msg));
} 