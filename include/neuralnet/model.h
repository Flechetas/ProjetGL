#ifndef MODEL_H
#define MODEL_H

#include "layer.h"

typedef struct model {
    int layer_n;
    Layer input;
} *Model;

Model createModelRandom(int layer_n, ...);
void freeModel(Model model);
int countLayers(Model model);

#endif
