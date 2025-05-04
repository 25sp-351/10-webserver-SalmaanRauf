#ifndef ROUTER_H
#define ROUTER_H

#include "request_parser.h"

// route:
// given a parsed request, picks the right handler
// and writes the response to fd
// returns 0 on success, or negative on error
int route(const Request *req, int fd);

#endif