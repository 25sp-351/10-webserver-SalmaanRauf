#ifndef RESPONSE_BUILDER_H
#define RESPONSE_BUILDER_H

#include <stddef.h>

// send_response:
// writes an http/1.1 response with given status code & message,
// content-type, and body of length body_len
int send_response(int fd,
                  int status_code,
                  const char *status_text,
                  const char *content_type,
                  const void *body,
                  size_t body_len);

/* Helpers */
int send_404(int fd);
int send_400(int fd, const char *msg);
int send_405(int fd);
int send_500(int fd);
int send_505(int fd);

#endif