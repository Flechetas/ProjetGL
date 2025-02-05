#ifndef MODEL_H
#define MODEL_H

#include "layer.h"

typedef struct model {
    int layer_n;
    Layer input;
} *Model;

/**
 * @brief Function that creates a random Model based on the number of layers and the sizes of each layer
 * @param layer_n The number of layers in the Model
 */
Model createModelRandom(int layer_n, ...);
void freeModel(Model model);
int countLayers(Model model);

#endif
