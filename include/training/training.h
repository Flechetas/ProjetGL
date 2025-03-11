#ifndef TRAINING_H
#define TRAINING_H

#include "neuralnet/model.h"

int train(Model model, float training_step, int batch_size, float **inputs, int input_size, float **expecteds, int expected_size);

#endif //TRAINING_h
