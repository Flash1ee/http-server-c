#include <string.h>
#include <ctype.h>
#include "http.h"

#define BUFFER_SIZE 4096

int readline(http_read_t read, void *data, char *buffer, size_t buffer_size) {
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

int http_handler(http_read_t read, http_write_t write, void *data) {
    char buffer[BUFFER_SIZE];
    int buf_len = readline(read, data, buffer, sizeof(buffer));
    if (buf_len <= 0) {
        return -1;
    }
    char *method_beg = buffer;
    char *method_end = strchr(method_beg, ' ');
    if (!method_end) {
        return -1;
    }

    printf("method = %s\n", strndup(method_beg, method_end - method_beg));

    char *url_beg = method_end + 1;
    while (isspace(url_beg)) {
        url_beg++;
    }
    char *url_end = strchr(url_beg, ' ');
    if (!url_end) {
        return -1;
    }
    printf("url = %s\n", strndup(url_beg, url_end - url_beg));

    char *protocol_beg = url_end + 1;
    while (isspace(url_beg)) {
        url_beg++;
    }
    char *protocol_end = buffer + buffer_len;

    printf("protocol = %s\n", strndup(protocol_beg, protocol_beg - protocol_end));

    return 0;
}