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
 * @brief Function that creates a random Model based on the number of layers and the sizes of each layer
 * @param layer_n The number of layers in the Model
 * @param layer_sizes An array of size layer_n containing the size of each layer of the model.
 * @return The new model
 * 
 * @note layer_n must correspond with the number of integers that follow
 */
Model createModelRandomFromArray(int layer_n, int layer_sizes[]);

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

/**
 * @param model A given model
 * @return The first layer of the model
 */

Layer firstLayer(Model model);
/**
 * @param model A given model
 * @return The last layer of the model
 */
Layer lastLayer(Model model);

#endif
