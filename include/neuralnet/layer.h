#ifndef LAYER_H
#define LAYER_H

typedef struct layer {
    int n;
    int w;

    float *neurons;
    float *bias;
    float **weight;

    struct layer* previous;
    struct layer* next;
} *Layer;


Layer createLayerRandom(int size, Layer next);
void freeLayer(Layer layer);

#endif
