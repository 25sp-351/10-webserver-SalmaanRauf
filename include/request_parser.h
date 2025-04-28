#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

#define MAX_METHOD_LEN    8
#define MAX_URI_LEN       256
#define MAX_VERSION_LEN   16

typedef struct {
    char method[MAX_METHOD_LEN];
    char uri[MAX_URI_LEN];
    char http_version[MAX_VERSION_LEN];
} Request;

// read_request:
// reads from socket fd until "\r\n\r\n", parses the request-line
// into req->method, req->uri, req->http_version
// returns 0 on success, -1 on error
int read_request(int fd, Request *req);

#endif