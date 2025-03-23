#ifndef BENCHMARK_ACCURACY_H
#define BENCHMARK_ACCURACY_H

#include "../neuralnet/model.h"

/**  
* @brief Calcule la précision d’un modèle en comparant les sorties prédites et les sorties attendues
* @param model Le modèle entraîné
* @param inputs Tableau de vecteurs d'entrée
* @param expected_outputs Tableau de vecteurs de sortie attendue
* @param nb_samples Nombre d’échantillons à évaluer
* @param output_size Nombre de neurones en sortie (taille du vecteur de sortie)
* @return précision entre 0.0 et 1.0
*/
float benchmarkAccuracy(Model model, float **inputs, float **expected_outputs, int nb_samples, int output_size);

#endif
