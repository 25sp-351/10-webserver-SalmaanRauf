#include "../../include/handlers/static_handler.h"
#include "../../include/response_builder.h"
#include "../../include/util.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// serves "./static<uri>". rejects any path with ".."
int handle_static(const Request *req, int fd) {
    // disallow directory traversal
    if (strstr(req->uri, "..")) {
        return send_400(fd, "400 Bad Request\n");
    }

    // build filesystem path: "./static" + uri suffix
    char path[512];
    snprintf(path, sizeof(path), ".%s", req->uri);

    int f = open(path, O_RDONLY);
    if (f < 0) {
        return send_404(fd);
    }

    struct stat st;
    if (fstat(f, &st) < 0) {
        close(f);
        return send_500(fd);
    }

    size_t len = st.st_size;
    char *buf = malloc(len);
    if (!buf) {
        close(f);
        return send_500(fd);
    }

    if (read(f, buf, len) != (ssize_t)len) {
        free(buf);
        close(f);
        return send_500(fd);
    }
    close(f);

    const char *mime = get_mime_type(path);
    int rc = send_response(fd, 200, "OK", mime, buf, len);

    free(buf);
    return rc;
}