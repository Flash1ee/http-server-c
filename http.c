#include <stdio.h>
#include <string.h>
#include "http.h"
#include "http_request.h"

int http_handler(http_read_t read, http_write_t write, void *data) {

    http_request_t *request = http_request_parse(read, data);
    if (!request) {
        return -1;
    }
    printf("method = %s\n", request->method);
    printf("url = %s\n", request->url);
    printf("protocol = %s\n", request->protocol);
    printf("host = %s\n", request->host);

    if (strcmp("GET", request->method) != 0) {
        http_request_destroy(request);
        return -1;
    }
    int protocol_major, protocol_minor;

    if (sscanf(request->protocol, "HTTP/%d.%d", &protocol_major, &protocol_minor) != 2) {
        http_request_destroy(request);
        return -1;
    }
    if (protocol_major != 1 || (protocol_minor != 0 && protocol_minor != 1)) {
        http_request_destroy(request);
        return -1;
    }
    //filename = root + host + url

    char *host = request->host;
    if (!host) {
        host = "localhost";
    }
    char *url = request->url;
    size_t url_len = strlen(request->url);
    if (url_len == 1 && *request->url == '/') {
        url = "/index.html";
        url_len = strlen(url);
    }


    http_request_destroy(request);

    return 0;
}