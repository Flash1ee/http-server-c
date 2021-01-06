#include <stdio.h>
#include <unistd.h>

#include "http.h"

typedef struct {
    int in;
    int out;
} hserver_data_t;

int hserver_read(void *pdata, char *buffer, size_t buffer_size) {
    hserver_data_t *data = (hserver_data_t *)pdata;
    return read(data->in, buffer, buffer_size);
}

int hserver_write(void *pdata, char *buffer, size_t buffer_size) {
    hserver_data_t *data = (hserver_data_t *)pdata;
    return write(data->out, buffer, buffer_size);
}

int main(int argc, char *argv[]) {

    hserver_data_t data = {
            .in = STDIN_FILENO,
            .out = STDOUT_FILENO,
    };
    return http_handler(hserver_read, hserver_write, &data); // Обработка http запроса
}
