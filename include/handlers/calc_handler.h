#ifndef CALC_HANDLER_H
#define CALC_HANDLER_H

#include "../request_parser.h"

// handle_calc:
// parses /calc/<op>/<n1>/<n2>, does the operation (add, mul, div),
// and responds with plain-text result or error
// returns 0 on success, negative on error
int handle_calc(const Request *req, int fd);

#endif