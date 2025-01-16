#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/network.h"


int countLayers(Model model) {
    int n = 0;
    Layer curr = model->input;
    while(curr != NULL) {
        curr = curr->next;
        n++; 
    }
    return n;
}


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
Layer initLayerRandom(int size, Layer next) {
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
void freeModel(Model model) {
    Layer curr = model->input;
    while(curr != NULL) {
        Layer next = curr->next;
        freeLayer(curr);
        curr = next;
    }
    free(model);
}


float th(float x) {
    return (exp(x) - exp(-x)) / (exp(x) + exp(-x)); 
}
