#include "../../include/handlers/calc_handler.h"
#include "../../include/response_builder.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// handles calc requests like "/calc/<op>/<n1>/<n2>"
// does add, mul, div and returns plain-text result
int handle_calc(const Request *req, int fd) {
    // copy uri suffix for tokenization
    char tmp[256];
    strncpy(tmp, req->uri + 6, sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0';

    char *saveptr = NULL;
    char *op = strtok_r(tmp, "/", &saveptr);
    char *s1 = strtok_r(NULL, "/", &saveptr);
    char *s2 = strtok_r(NULL, "/", &saveptr);
    char *extra = strtok_r(NULL, "/", &saveptr);

    if (!op || !s1 || !s2 || extra) {
        return send_400(fd, "400 Bad Request\n");
    }

    char *endptr;
    double n1 = strtod(s1, &endptr);
    if (*endptr) return send_400(fd, "400 Bad Request\n");
    double n2 = strtod(s2, &endptr);
    if (*endptr) return send_400(fd, "400 Bad Request\n");

    double result;
    if (strcmp(op, "add") == 0) {
        result = n1 + n2;
    } else if (strcmp(op, "mul") == 0) {
        result = n1 * n2;
    } else if (strcmp(op, "div") == 0) {
        if (n2 == 0.0) {
            return send_400(fd, "400 Bad Request: Division by zero\n");
        }
        result = n1 / n2;
    } else {
        return send_404(fd);
    }

    // format result as text
    char body[128];
    int len = snprintf(body, sizeof(body), "%g\n", result);
    return send_response(fd, 200, "OK", "text/plain", body, len);
} 