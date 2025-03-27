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



#endif
