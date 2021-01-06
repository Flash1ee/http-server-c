#ifndef HTTP_SERVER_C_HTTP_H
#define HTTP_SERVER_C_HTTP_H
#include <unistd.h>
typedef int (*http_read_t)(void *data, char *buffer, size_t buffer_size);
typedef int (*http_write_t)(void *data, char *buffer, size_t buffer_size);

int http_handler(http_read_t read, http_write_t write, void *data);

#endif //HTTP_SERVER_C_HTTP_H
