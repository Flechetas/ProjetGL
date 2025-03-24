#ifndef BENCHMARK_ACCURACY_H
#define BENCHMARK_ACCURACY_H

#include "../neuralnet/model.h"

/**  
* @brief Benchmark métrique temporel
* @param start Enregistrement du temps pris avant un test
* @param end Enregistrement du temps pris après un test
* @param nb_samples Nombre d'échantillons à évaluer
*/
void benchmarkTIME(clock_t start, clock_t end, int nb_samples);

/**  
* @brief Calcule la précision d’un modèle en comparant les sorties prédites et les sorties attendues
* @param model Le modèle entraîné
* @param inputs Tableau de vecteurs d'entrée
* @param expected_outputs Tableau de vecteurs de sortie attendue
* @param nb_samples Nombre d’échantillons à évaluer
* @param output_size Nombre de neurones en sortie (taille du vecteur de sortie)
*/
void benchmarkAccuracyBRUT(Model model, float **inputs, float **expected_outputs, int nb_samples, int output_size);

/**  
* @brief Calcule la précision d’un modèle en comparant les sorties prédites avec les points en dures de la spirale
*/
void benchmarkAccuracyPoints(Model model, int output_size);

/**  
* @brief Calcule la précision d’un modèle en comparant les sorties prédites et les sorties attendues par DetermineColor
*/
void benchmarkAccuracyDetermineColor(Model model, float **inputs, int nb_samples, int output_size);

/**  
* @brief Benchmark global qui appelle les 3 fonctions d'accuracy et le temps pris par l'entrainement
*/
void benchmarkAccuracyAndTime(Model model, float **inputs, int nb_samples, float **expected_outputs, int output_size, clock_t start, clock_t end);

#endif
