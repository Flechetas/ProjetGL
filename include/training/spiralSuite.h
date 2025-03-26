#ifndef SPIRAL_SUITE_H
#define SPIRAL_SUITE_H

#include "neuralnet/model.h"

/**
 * @brief trains the given model on the spiral data
 * @param model the model to train
 * @param training_step represents the rate of change of the model after each training step
 * @param batch_size the number of training steps
 * @param visualized determines wheteher the model should be drawn during training
 * @return 0 on success, error code otherwise
 */
int trainOnSpiral(Model model, float training_step, int batch_size, int visualized);

#endif //SPIRAL_SUITE_H
