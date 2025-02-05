#ifndef LAYER_H
#define LAYER_H

typedef struct layer {
    int n; // number of neurones
    int w; // number of neurones in next layer

    float *neurons;
    float *bias;
    float **weight;

    struct layer* previous;
    struct layer* next;
} *Layer;


Layer createLayerRandom(int size, Layer next);
void freeLayer(Layer layer);

/// @brief Calculates the hyperbolic tangent for the value x
/// @param x 
/// @return hyperbolic tangent for x
float layer_hypTangent(float x);

/// @brief Calculates the sum of the value of each neurons[i] in the layer times the weight[i][ind]
/// @param l The current layer
/// @param ind The index of the neurone in the next layer
/// @return Sum for i = 0 to n-1 of neurons[i]*weight[i][ind]
float layer_neuronSum(Layer l, int ind);

/// @brief Applies the 2 previous functions to calculate the value of the neuron l->next->neurons[ind]
/// @param l The current layer
/// @param ind The index of the neuron in the next layer
void layer_neuronVal(Layer l, int ind);


#endif
