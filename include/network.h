#ifndef NETWORK_H
#define NETWORK_H

typedef struct layer {
    int n;
    int w;

    float *neurons;
    float *bias;
    float **weight;

    struct layer* previous;
    struct layer* next;
} *Layer;

typedef struct model {
    Layer input;
} *Model;


Layer initLayerRandom(int size, Layer next);
void freeLayer(Layer layer);
int countLayers(Model model);

#endif
