#ifndef UTIL_H
#define UTIL_H

// get_mime_type:
// returns a mime string based on file extension
// defaults to "application/octet-stream"
const char *get_mime_type(const char *path);

#endif