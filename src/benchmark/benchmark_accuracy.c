#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/neuralnet/model.h"
#include "../include/neuralnet/ForwardPass.h"
#include "../include/benchmark/benchmark_accuracy.h"

/** 
* @brief Retourne l’indice de la valeur maximale dans un tableau
*/
static int getMaxIndex(float *array, int size) {
    int max_index = 0;
    for (int i = 1; i < size; i++) {
        if (array[i] > array[max_index]) {
            max_index = i;
        }
    }
    return max_index;
}


float benchmarkAccuracy(Model model, float **inputs, float **expected_outputs, int nb_samples, int output_size) {
    int correct = 0;

    for (int i = 0; i < nb_samples; i++) {
        float *prediction = forwardPass(model, inputs[i]);
        int predicted_index = getMaxIndex(prediction, output_size);
        int expected_index = getMaxIndex(expected_outputs[i], output_size);

        // DEBUG : afficher les valeurs
        printf("Exemple %d:\n", i);
        printf("  Entrée           : [%.2f, %.2f]\n", inputs[i][0], inputs[i][1]);
        printf("  Prédit           : [%f, %f] => classe %d\n", prediction[0], prediction[1], predicted_index);
        printf("  Sortie attendue  : [%f, %f] => classe %d\n\n", expected_outputs[i][0], expected_outputs[i][1], expected_index);

        if (predicted_index == expected_index) {
            correct++;
        }
    }

    float accuracy = (float)correct / nb_samples;
    printf("=== Résultat du benchmark ===\n");
    printf("Corrects : %d / %d\n", correct, nb_samples);
    printf("Précision : %.2f%%\n", accuracy * 100.0f);

    return accuracy;
}
