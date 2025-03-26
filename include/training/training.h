#ifndef TRAINING_H
#define TRAINING_H

#include "neuralnet/model.h"

/**
 * @brief Trains the given model
 * @param model the model to train
 * @param training_step represents the rate of change of the model after each training step
 * @param batch_size the number of training steps
 * @param inputs the input data given to the model. Matrix of size [input_size ; input_layer_size]
 * @param expecteds the expected data used to compare with the model data. Matrix of size [expected_size ; output layer size]
 * @param visualized determines wheteher the model should be drawn during training
 * @return 0 on success, error code otherwise
 */
int train(Model model, float training_step, int batch_size, float **inputs, int input_size, float **expecteds, int expected_size, int visualized);

#endif //TRAINING_h
