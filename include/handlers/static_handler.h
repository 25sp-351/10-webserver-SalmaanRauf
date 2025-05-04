#ifndef STATIC_HANDLER_H
#define STATIC_HANDLER_H

#include "../request_parser.h"

// handle_static:
// serves files under "./static". rejects paths with ".."
// returns 0 on success, negative on error
int handle_static(const Request *req, int fd);

#endif