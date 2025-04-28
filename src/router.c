#include "router.h"
#include "response_builder.h"
#include "handlers/static_handler.h"
#include "handlers/calc_handler.h"
#include <string.h>

int send_505(int fd) {
    const char *msg = "505 HTTP Version Not Supported\n";
    return send_response(fd, 505, "HTTP Version Not Supported", 
                         "text/plain", msg, strlen(msg));
}

int route(const Request *req, int fd) {
    // check http version - only support http/1.1
    if (strcmp(req->http_version, "HTTP/1.1") != 0) {
        return send_505(fd);
    }

    // only get is supported
    if (strcmp(req->method, "GET") != 0) {
        return send_405(fd);
    }

    // static files: /static/...
    if (strncmp(req->uri, "/static/", 8) == 0) {
        return handle_static(req, fd);
    }

    // calculation: /calc/...
    if (strncmp(req->uri, "/calc/", 6) == 0) {
        return handle_calc(req, fd);
    }

    // not found otherwise
    return send_404(fd);
} 