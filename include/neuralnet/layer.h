#ifndef LAYER_H
#define LAYER_H

/**
 * @struct layer
 * @brief Represents the neural network layer
 */
typedef struct layer {
    int n; ///< Number of neurons in the layer
    int w; ///< Number of neurons in the next layer

    float *neurons; ///< Array of neuron values
    float *bias; ///< Array of bias values for each neuron 
    float **weight; ///< 2D array (size n*w) of weight connections

    struct layer* previous; ///< The previous layer in the model
    struct layer* next; ///< The next layer in the model
} *Layer;

/** 
 * @brief Creates a layer with random weights. Neuron values are initalised at 0
 * @param size The number of neurons the new layer will have
 * @param next The next layer in the model
 * @return The new model
 */
Layer createLayerRandom(int size, Layer next);

/**
 * @brief Frees the resources allocated in the layer given as parameter
 * @param layer The layer in question
 */
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
