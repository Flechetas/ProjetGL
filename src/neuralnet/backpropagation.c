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
    float *cost = malloc(len);
    
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
    int step = countLayers(model) - 1;
    float **costs = malloc(sizeof(float*) * model->layer_n);
    
    forwardPass(model, input);
    Layer layer = lastLayer(model);
    
    costs[step] = outputCost(layer, expected);
    layer = layer->previous;
    step--;
    while(layer->previous != NULL) {
        costs[step] = layerCost(layer, costs[step+1]);
        layer = layer->previous;
        step--;
    }

    float correction = 0;
    while(layer->next != NULL) {
        int len = layer->n;
        int w = layer->w;
        for(int i = 0 ; i < len ; i++) {
            for(int j = 0 ; j < w ; j++) {
                float diff = training_step * costs[step][i] * activationFunction(layer->neurons[i] * layer->weight[i][j]);
                layer->weight[i][j] += diff;
                correction += diff;
            }
        }
        layer = layer->next;
        step++;
    }

    for(int i = 0 ; i < model->layer_n ; i++) {
        free(costs[i]);
    }
    free(costs);

    return correction;
}
