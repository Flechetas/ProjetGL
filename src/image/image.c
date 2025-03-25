#include <stdlib.h>

#include "image/image.h"

Image initImage(int rows, int cols) {
    Image img = malloc(sizeof(struct image_struct));
    img->rows = rows;
    img->cols = cols;
    img->pixels = malloc(rows * cols * sizeof(char *));
    return img;
}

void freeImage(Image image) {
    free(image->pixels);
    free(image);
}
