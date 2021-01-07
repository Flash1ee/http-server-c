#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "http_request.h"
#include "http.h"

static http_request_t  *http_request_create() {
    return calloc(1, sizeof(http_request_t));
}
void http_request_destroy(http_request_t *request) {
    free(request->method);
    free(request->url);
    free(request->protocol);
    free(request->host);
    free(request);
}

#define BUFFER_SIZE 4096

static int readline(http_read_t read, void *data, char *buffer, size_t buffer_size) {
    int i = 0;
    while (i < BUFFER_SIZE) {
        char c;
        int r = read(data, &c, sizeof(c));
        if (r <= 0) {
            return -1;
        }
        if (c == '\n') {
            break;
        }
        buffer[i++] = c;
    }
    if (i > 0 && buffer[i - 1] == '\r') {
        i--;
    }
    buffer[i] = '\0';
    return i;
}

http_request_t *http_request_parse(http_read_t read, void *data) {

    http_request_t *request = http_request_create();

    char buffer[BUFFER_SIZE];
    int buf_len = readline(read, data, buffer, sizeof(buffer));
    if (buf_len <= 0) {
        http_request_destroy(request);
        return NULL;
    }
    char *method_beg = buffer;
    char *method_end = strchr(method_beg, ' ');
    if (!method_end) {
        http_request_destroy(request);
        return NULL;
    }
    request->method = strndup(method_beg, method_end - method_beg);

    char *url_beg = method_end + 1;
    while (isspace(*url_beg)) {
        url_beg++;
    }
    char *url_end = strchr(url_beg, ' ');
    if (!url_end) {
        http_request_destroy(request);
        return NULL;
    }
    request->url = strndup(url_beg, url_end - url_beg);

    char *protocol_beg = url_end + 1;
    while (isspace(*url_beg)) {
        url_beg++;
    }
    char *protocol_end = buffer + buf_len;

    request->protocol = strndup(protocol_beg, protocol_beg - protocol_end);

    while (true) {
        char buffer[BUFFER_SIZE];
        int buffer_len = readline(read, data, buffer, sizeof(buffer));
        if (buffer_len == -1) {
            return NULL;
        }
        if (buffer_len == 0) {
            break;
        }
        // NAME: VALUE
        char *header_beg = buffer;
        char *header_end = strchr(header_beg, ':');
        if (!header_end) {
            continue;
        }
        char *value_beg = header_end + 1;
        while (isspace(*value_beg)) {
            value_beg++;
        }
        char *value_end = buffer + buf_len;
        if (strncmp(header_beg, "Host", header_end - header_beg) == 0) {
            request->host = strndup(value_beg, value_end - value_beg);
        }
    }
    return request;
}