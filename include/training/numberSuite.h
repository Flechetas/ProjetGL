#ifndef NUMBER_SUITE_H
#define NUMBER_SUITE_H

#include "neuralnet/model.h"

/**
 * @brief loads the image input data and gives informations about it
 * @param filename the file to read data from
 * @param batch the number of elements read
 * @param input_size the number of pixels in each image
 * @param data the images read from file, in a format readable by the model
 * @return 0 on success, error code otherwise
 */
int loadInputData(const char *filename, int *batch, int *input_size, float ***data);

/**
 * @brief loads the label input data and gives informations about it
 * @param filename the file to read data from
 * @param batch the number of elements read
 * @param test_size the number of digits possible
 * @param data the labels read from file, in a format readable by the model
 * @return 0 on success, error code otherwise
 */
int loadTestData(const char *filename, int *batch, int *test_size, float ***data);

/**
 * @brief trains the given model on the number data
 * @param model the model to train
 * @param training_step represents the rate of change of the model after each training step
 * @return 0 on success, error code otherwise
 */
int trainOnNumbers(Model model, float training_step);

/**
 * @brief determines which number has been chosen by the model given the output value
 * @param the model output value
 * @return the chosen number
 */
int determineOutput(float *output);

#endif //NUMBER_SUITE_H
