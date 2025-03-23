#ifndef SPIRAL_SUITE_H
#define SPIRAL_SUITE_H

#include "neuralnet/model.h"

/**
 * @brief trains the given model on the spiral data
 * @param le modèle à entraîner
 * @param training_step représente le taux de changement du modèle après une étape d'entrainement
 * @param batch_size le nombre d'étape d'entrainement
 * @return 0 on success, error code otherwise
 */
int trainOnSpiral(Model model, float training_step, int batch_size);

#endif //SPIRAL_SUITE_H
