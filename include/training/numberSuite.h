#ifndef NUMBER_SUITE_H
#define NUMBER_SUITE_H

#include "neuralnet/model.h"

int loadInputData(const char *filename, int *batch, int *input_size, float ***data);
int loadTestData(const char *filename, int *batch, int *test_size, float ***data);
int trainOnNumbers(Model model, float training_step);
int determineOutput(float *output);

#endif //NUMBER_SUITE_H
