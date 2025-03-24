#ifndef TRAINING_H
#define TRAINING_H

#include "neuralnet/model.h"

/**
 * @brief Entraîne le modèle donné 
 * @param le modèle à entraîner
 * @param training_step représente le taux de changement du modèle après une étape d'entrainement
 * @param batch_size le nombre d'étape d'entrainement
 * @param inputs les données d'entrée à fournir au modèle. Matrice de taille [input_size ; taille couche entrée]
 * @param expecteds les données attendues pour comparer au données du modèle. Matrice de taille [expected_size ; taille couche sortie]
 * @param visualized détermine si le modèle doit être affiché durant l'entrainement
 * @return 0 on success, error code otherwise
 */
int train(Model model, float training_step, int batch_size, float **inputs, int input_size, float **expecteds, int expected_size, int visualized);

#endif //TRAINING_h
