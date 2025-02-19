#ifndef MODEL_H
#define MODEL_H

#include "layer.h"

/**
 * @struct model
 * @brief Represents the neural network itself
 */
typedef struct model {
    int layer_n; ///< Number of layers in the model
    Layer input; ///< The first layer of the model
} *Model;

/**
 * @brief Function that creates a random Model based on the number of layers and the sizes of each layer
 * @param layer_n The number of layers in the Model
 * @param ... A sequence of integers representing the number of neurons in each layer
 * @return The new model
 * 
 * @note layer_n must correspond with the number of integers that follow
 */
Model createModelRandom(int layer_n, ...);

/**
 * @brief Frees the resources allocated in the model given as parameter
 * @param model The model in question
 */
void freeModel(Model model);

/**
 * @param model A given model
 * @return The number of layers in the given model
 */
int countLayers(Model model);

#endif
