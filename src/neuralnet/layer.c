#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "neuralnet/layer.h"


float **initRandomWeights(int sizex, int sizey) {
    srand(time(NULL));
    float **weights = malloc(sizeof(float*) * sizex);
    for(int i = 0 ; i < sizex ; i++) {
        weights[i] = malloc(sizeof(float) * sizey);
        for(int j = 0 ; j < sizey ; j++) {
            // Random float €[-1,1]
            float w = (float)rand()/(float)RAND_MAX*2-1;
            weights[i][j] = w;
        }
    }
    return weights;
}
Layer createLayerRandom(int size, Layer next) {
    Layer layer = malloc(sizeof(struct layer));
    layer->n = size;
    layer->neurons = malloc(sizeof(float) * size);
    for(int i = 0 ; i < size ; i++) {
        layer->neurons[i] = 0;
    }
    layer->next = next;
    if(next == NULL) {
        return layer;
    }
    layer->w = next->n;
    layer->weight = initRandomWeights(layer->n, layer->w);
    return layer;
}
void freeLayer(Layer layer) {
    int n = layer->n;
    free(layer->neurons);
    if(layer->next != NULL) {
        for(int i = 0 ; i < n ; i++) {
            free(layer->weight[i]);
        }
        free(layer->weight);
    }
    free(layer);
}

float layer_hypTangent(float x) {
    
    return exp(x) - exp(-x) / exp(x) + exp(-x);
}

float layer_neuronSum(Layer l, int ind) {
    float sum = 0.0;
    for (int i = 0; i < l->n; i++) {
        sum += l->neurons[i] * l->weight[i][ind]; 
        // ind represents which neurone we are trying to calculate for
    }

    return sum;
}

void layer_neuronVal(Layer l, int ind) {
    
    l->next->neurons[ind] = layer_hypTangent(layer_neuronSum(l, ind));
}
