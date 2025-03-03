#ifndef FORWARDPASS_H
#define FORWARDPASS_H

#include <SDL2/SDL.h>

//void forwardPass(Layer input_layer);
void initNeuron(Layer layer, int index, float value);
void initRandomInputs(float *inputs, int size);
float activationFunction(float x); // fonction de tranfert
void computeNextNeuronValue(Layer currentLayer, int neuronIndex);
void processNeuronLayer(Layer inputLayer, Layer hiddenLayer, float *inputValues, int inputSize);
void initRandomFloatArray(float *array, int size);

/**
 * @brief Effectue la propagation sur un réseau de neurones
 * @param model Le model du réseau de neurones
 * @param input Le vecteur d'entrée (valeur des neuronnes d'entrés) // random init ?
 * @return Les valeurs des neurones de la couche de sortie
 */
float* forwardPass(Model model, float *input);

#endif // FORWARDPASS_H