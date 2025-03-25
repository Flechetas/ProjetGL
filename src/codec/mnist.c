#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include "codec/mnist.h"
#include "log.h"

int parseImageIDX(const char *filename, int *out_count, Image **images) {
    int ret;
    int fd = open(filename, O_RDONLY);
    if(fd <= 0) {
        log_error("Error opening file %s", filename);
        return -1;
    }

    int magic;
    ret = read(fd, &magic, sizeof(int));
    if(ret <= 0) {
        log_error("Error reading magic number");
        return -1;
    }
    magic = __builtin_bswap32(magic);

    int count;
    ret = read(fd, &count, sizeof(int));
    if(ret <= 0) {
        log_error("Error reading count");
        return -1;
    }
    count = __builtin_bswap32(count);
    *out_count = count;

    int rows;
    ret = read(fd, &rows, sizeof(int));
    if(ret <= 0) {
        log_error("Error reading rows");
        return -1;
    }
    rows = __builtin_bswap32(rows);

    int cols;
    ret = read(fd, &cols, sizeof(int));
    if(ret <= 0) {
        log_error("Error reading cols");
        return -1;
    }
    cols = __builtin_bswap32(cols);
    
    int size = count * rows * cols * sizeof(char);
    char *data = malloc(size);
    ret = read(fd, data, size);
    if(ret <= 0) {
        log_error("Error reading data");
        return -1;
    }
    
    Image *result = malloc(count * sizeof(Image));
    *images = result;
    for(int i = 0 ; i < count ; i++) {
        Image img = initImage(rows, cols);
        result[i] = img;

        for(int j = 0 ; j < rows * cols ; j++) {
            int off = i * rows * cols + j;
            img->pixels[j] = data[off];
        }
    }

    return 0;

}

int parseLabelIDX(const char *filename, int *out_count, int **out_labels) {
    int ret;
    int fd = open(filename, O_RDONLY);
    if(fd <= 0) {
        log_error("Error opening file %s", filename);
        return -1;
    }

    int magic;
    ret = read(fd, &magic, sizeof(int));
    if(ret <= 0) {
        log_error("Error reading magic number");
        return -1;
    }
    magic = __builtin_bswap32(magic);

    int count;
    ret = read(fd, &count, sizeof(int));
    if(ret <= 0) {
        log_error("Error reading count");
        return -1;
    }
    count = __builtin_bswap32(count);
    *out_count = count;


    int size = count * sizeof(char);
    char *data = malloc(size);
    ret = read(fd, data, size);
    if(ret <= 0) {
        log_error("Error reading data");
        return -1;
    }

    int *labels = malloc(count * sizeof(int));
    for(int i = 0 ;  i < count ; i++) {
        int label = (int)data[i];
        labels[i] = label;
    }
    *out_labels = labels;

    return 0;
}
