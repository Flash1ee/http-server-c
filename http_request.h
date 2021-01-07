#ifndef HTTP_SERVER_C_HTTP_REQUEST_H
#define HTTP_SERVER_C_HTTP_REQUEST_H

#include "http.h"

typedef struct {
    char *method;
    char *url;
    char *protocol;
    char *host;
} http_request_t;

void http_request_destroy(http_request_t *request);
http_request_t  *http_request_parse(http_read_t read, void *data);

#endif //HTTP_SERVER_C_HTTP_REQUEST_H
