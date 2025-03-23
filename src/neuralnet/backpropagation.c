#include <stdlib.h>

#include "neuralnet/backpropagation.h"
#include "neuralnet/ForwardPass.h"

float *outputCost(Layer layer, float *expected) {
    int len = layer->n;
    float *actual = layer->neurons;
    float *cost = malloc(sizeof(float) * len);

    for(int i = 0 ; i < len ; i++) {
        cost[i] = (1 - actual[i] * actual[i]) * (expected[i] - actual[i]);
    }
    
    return cost;
}

float *layerCost(Layer layer, float *expected) {
    int len = layer->n;
    float *cost = malloc(len * sizeof(float));
    
    for(int i = 0 ; i < len ; i++) {
        float sum = 0;
        int expected_len = layer->w;
        for(int j = 0 ; j < expected_len ; j++) {
            sum += expected[j] * layer->weight[i][j];
        }
        float actual = layer->neurons[i];
        cost[i] = (1 - actual * actual) * sum;
    }
    return cost;
}

float backpropagate(Model model, float training_step, float *input, float *expected) {
    float outCost = 0;
    int step = countLayers(model) - 2;
    float **costs = malloc(sizeof(float*) * (model->layer_n-1));
    
    forwardPass(model, input);
    Layer layer = lastLayer(model);
    costs[step] = outputCost(layer, expected);
    for(int i = 0 ; i < layer->n ; i++) {
        outCost += costs[step][i];
    }
    
    layer = layer->previous;
    step--;
    while(layer->previous != NULL) {
        costs[step] = layerCost(layer, costs[step+1]);
        layer = layer->previous;
        step--;
    }

    step = 0;
    layer = firstLayer(model)->next;
    while(layer != NULL) {
        int len = layer->n;
        for(int i = 0 ; i < len ; i++) {
            for(int j = 0 ; j < layer->previous->n ; j++) {
                float diff = training_step * costs[step][i] * layer->previous->neurons[j];
                layer->previous->weight[j][i] += diff;
            }
        }
        layer = layer->next;
        step++;
    }

    for(int i = 0 ; i < model->layer_n-1 ; i++) {
        free(costs[i]);
    }
    free(costs);

    return outCost;
}
