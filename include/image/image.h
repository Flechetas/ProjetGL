#ifndef IMAGE_H
#define IMAGE_H

typedef struct image_struct {
    int rows;
    int cols;
    
    // char because a pixel uses a byte
    char *pixels;
} *Image;

Image initImage(int rows, int cols);
void freeImage(Image image);

#endif // IMAGE_H
