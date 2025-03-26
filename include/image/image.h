#ifndef IMAGE_H
#define IMAGE_H

typedef struct image_struct {
    int rows;
    int cols;
    
    // char because pixels are stored in a single byte
    char *pixels;
} *Image;

/**
 * @brief Creates an image from its row and column sizes
 * @param rows the row number of the image
 * @param cols the columb number of the image
 */
Image initImage(int rows, int cols);


/**
 * @brief Frees the given image
 * @param image the image to be freed
 */
void freeImage(Image image);

#endif // IMAGE_H
