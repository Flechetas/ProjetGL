#ifndef FORWARDPASS_H
#define FORWARDPASS_H

#include <SDL2/SDL.h>
#include "model.h"

/**
 * @brief Sets the value of a neuron in the layer
 * @param layer The layer where the neuron will be changed
 * @param index The index of the neuron in the layer->neurons table where
 * @param value The value of the neuron
 */
void initNeuron(Layer layer, int index, float value);

/**
 * @brief Initialises the input values with a random number between 0 and 1
 * @param inputs The initial values of the 
 */
void initRandomInputs(float *inputs, int size);

/**
 * @brief Transfer function used to put a value between 0 and 1
 * @returns The hyperbolic tangent applied to the parameter x
 */
float activationFunction(float x); // fonction de tranfert

/**
 * @brief Calculates the value of a neuron in the next layer
 * @param neuronIndex The index of the neuron in the next layer
 */
void computeNextNeuronValue(Layer currentLayer, int neuronIndex);

void processNeuronLayer(Layer inputLayer, Layer hiddenLayer, float *inputValues, int inputSize);

/**
 * @brief Initialises a pre-allocated array of floats of a given size with random numbers
 * @param array Pointer to the float array
 * @param size The size of the array
 */
void initRandomFloatArray(float *array, int size);

/**
 * @brief Effectue la propagation sur un réseau de neurones
 * @param model Le model du réseau de neurones
 * @param input Le vecteur d'entrée (valeur des neuronnes d'entrés) // random init ?
 * @return Les valeurs des neurones de la couche de sortie
 */
float* forwardPass(Model model, float *input);

#endif // FORWARDPASS_H
