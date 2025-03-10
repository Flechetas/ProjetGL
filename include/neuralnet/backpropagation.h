#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include "model.h"

/**
 * @brief Effectue la backpropagation sur un réseau de neurones
 * @param model Le model du réseau de neurones
 * @param training_step représente le taux de changement du modèle après une étape d'entrainement
 * @param input Le vecteur d'entrée (valeur des neurones d'entrés)
 * @param input Le vecteur attendu (valeur des neurones attendus)
 */
void backpropagate(Model model, float training_step, float *input, float *expected);

#endif //BACKPROPAGATION_H
