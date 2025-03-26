#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include "model.h"

/**
 * @brief Effectue la backpropagation sur un réseau de neurones
 * @param model The model to train
 * @param training_step represents the rate of change of the model after each training step
 * @param input the input data
 * @param input the expected data (to be compared with the model data)
 * @param out_cost the cost of the output data compared to expected data
 * @param out_diff the amount of change of the model after the training step
 */
void backpropagate(Model model, float training_step, float *input, float *expected, float *out_cost, float *out_diff);

#endif //BACKPROPAGATION_H
