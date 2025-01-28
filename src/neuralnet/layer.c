#include <stdio.h>
#include <stdlib.h>
#include "../../include/neuralnet/layer.h"


float **initRandomWeights(int sizex, int sizey) {
    float **weights = malloc(sizeof(float*) * sizex);
    for(int i = 0 ; i < sizex ; i++) {
        weights[i] = malloc(sizeof(float) * sizey);
        for(int j = 0 ; j < sizey ; j++) {
            weights[i][j] = (float)rand()/(float)RAND_MAX;
        }
    }
    return weights;
}
float *initRandomBiases(int size) {
    float *bias = malloc(sizeof(float) * size);
    for(int i = 0 ; i < size ; i++) {
        bias[i] = (float)rand()/(float)RAND_MAX;
    }
    return bias;
}
Layer createLayerRandom(int size, Layer next) {
    Layer layer = malloc(sizeof(struct layer));
    layer->n = size;
    layer->neurons = malloc(sizeof(float) * size);
    layer->next = next;
    if(next == NULL) {
        return layer;
    }
    layer->w = next->n;
    layer->weight = initRandomWeights(layer->n, layer->w);
    layer->bias = initRandomBiases(layer->n);
    return layer;
}
void freeLayer(Layer layer) {
    int n = layer->n;
    free(layer->neurons);
    if(layer->next != NULL) {
        free(layer->bias);
        for(int i = 0 ; i < n ; i++) {
            free(layer->weight[i]);
        }
        free(layer->weight);
    }
    free(layer);
}
