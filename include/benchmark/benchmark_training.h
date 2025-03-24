#ifndef BENCHMARK_TRAINING_H
#define BENCHMARK_TRAINING_H

#include "neuralnet/model.h"

/**
 * @brief trains the given model on the spiral data (with benchmarks)
 * @param model modèle à entraîner
 * @param training_step représente le taux de changement du modèle après une étape d'entrainement
 * @param batch_size le nombre d'étape d'entrainement
 * @param visualized détermine si le modèle doit être affiché durant l'entrainement
 * @return 0 on success, error code otherwise
 */
int benchmark_trainOnSpiral(Model model, float training_step, int batch_size, int visualized);

#endif //BENCHMARK_TRAINING_H
