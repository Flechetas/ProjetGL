#ifndef FORWARDPASS_H
#define FORWARDPASS_H

#include <SDL2/SDL.h>

#include "model.h"

/**
 * @brief Transfer function used to put a value between 0 and 1
 * @returns The hyperbolic tangent applied to the parameter x
 */
float activationFunction(float x); // fonction de tranfert

/**
 * @brief Effectue la propagation sur un réseau de neurones
 * @param model Le model du réseau de neurones
 * @param input Le vecteur d'entrée (valeur des neuronnes d'entrés) // random init ?
 * @return Les valeurs (tableau) des neurones de la couche de sortie
 */
float* forwardPass(Model model, float *input);

#endif // FORWARDPASS_H
