#include "http.h"

#define BUFFER_SIZE 4096

int http_handler(http_read_t read, http_write_t write, void *data) {
    char buffer[BUFFER_SIZE];
    int r = read(data, buffer, sizeof(buffer));
    write(data, buffer, r);
    return 0;
}