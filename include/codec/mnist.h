#ifndef MNIST_H
#define MNIST_H

#include "image/image.h"

#define TRAIN_IMAGES_FILENAME "train-images.idx3-ubyte"
#define TRAIN_LABEL_FILENAME  "train-labels.idx1-ubyte"
#define TEST_IMAGES_FILENAME  "t10k-images.idx3-ubyte"
#define TEST_LABEL_FILENAME   "t10k-labels.idx1-ubyte"

/**
 * @brief Parses the images contained in a .idx3-ubyte file
 * @param filename the file to parse
 * @param out_count the number of images returned
 * @param images the images returned from the file
 * @return 0 on success, error code otherwise
 */
int parseImageIDX(const char *filename, int *out_count, Image **images);

int parseLabelIDX(const char *filename, int *out_count, int **labels);

#endif //MNIST_H
