#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../include/neuralnet/model.h"
#include "../include/neuralnet/ForwardPass.h"
#include "../include/benchmark/benchmark_function.h"
#include "../include/draw/draw.h"    
#include "../include/config/config.h"  

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

/** 
* @brief Retourne les valeurs de la couche de sortie
*/
float* getOutputValues(Model model) {
    return lastLayer(model)->neurons;
}

// métrique temporel
void benchmarkTIME(clock_t start, clock_t end, int nb_samples){

    double total_time = (double)(end - start) / CLOCKS_PER_SEC;
    double avg_time = total_time / nb_samples * 1000.0;
    int minutes = (int)(total_time / 60);
    double seconds = total_time - minutes * 60;

    printf("=== Résultat du benchmark (temps) ===\n");
    printf("Temps total : %d min %.2f sec\n", minutes, seconds);
    printf("Temps moyen par instance : %.4f ms\n", avg_time);
}

void benchmarkAccuracyBRUT(Model model, float **inputs, float **expected_outputs, int nb_samples, int output_size) {
    int correct = 0;

    for (int i = 0; i < nb_samples; i++) {
        //float *prediction = forwardPass(model, inputs[i]);
        float *prediction = getOutputValues(model);
        int predicted_index = getMaxIndex(prediction, output_size);
        int expected_index = getMaxIndex(expected_outputs[i], output_size);

        // DEBUG
        /*printf("Exemple %d:\n", i);
        printf("  Entrée           : [%.2f, %.2f]\n", inputs[i][0], inputs[i][1]);
        printf("  Prédit           : [%f, %f] => classe %d\n", prediction[0], prediction[1], predicted_index);
        printf("  Sortie attendue  : [%f, %f] => classe %d\n\n", expected_outputs[i][0], expected_outputs[i][1], expected_index);*/

        if (predicted_index == expected_index) {
            correct++;
        }

        //DEBUG
        /*if ((i + 1) % 50000 == 0) {
            printf("Pause à l'exemple %d. Appuyez sur Entrée pour continuer...\n", i + 1);
            getchar(); 
        }*/
    }

    float accuracy = (float)correct / nb_samples;
    printf("=== Résultat du benchmark (précision expected_outputs) ===\n");
    printf("Corrects : %d / %d (ittérations)\n", correct, nb_samples);
    printf("Précision : %.2f%%\n", accuracy * 100.0);

}

void benchmarkAccuracyPoints(Model model, int output_size){
    
    //initSpiralValues(); 

    int xMax = WINDOW_WIDTH;
    int yMax = WINDOW_HEIGHT;

    Point *red_points = getRedPoints();
    Point *blue_points = getBluePoints();
    int red_count = getRlen();
    int blue_count = getBlen();
    printf("red_count = %d\n", red_count);
    printf("blue_count = %d\n", blue_count);
    int correctSpi = 0;
    int total = red_count + blue_count;

    //Par rapport aux points de la spirale
    // points rouges
    for (int i = 0; i < red_count; i++) {
        float input[2];
        input[0] = ((float)red_points[i].x / (float)xMax);
        input[1] = ((float)red_points[i].y / (float)yMax);

        float *prediction = forwardPass(model, input);
        int predicted_class = getMaxIndex(prediction, output_size);

        if (predicted_class == 0) correctSpi++; 

        //DEBUG
        /*if ((i + 1) % 50000 == 0) {
            printf("Pause à l'exemple %d. Appuyez sur Entrée pour continuer...\n", i + 1);
            getchar(); 
        }*/
    }

    // points bleus
    for (int i = 0; i < blue_count; i++) {
        float input[2];
        input[0] = ((float)blue_points[i].x / (float)xMax);
        input[1] = ((float)blue_points[i].y / (float)yMax);

        float *prediction = forwardPass(model, input);
        int predicted_class = getMaxIndex(prediction, output_size);

        if (predicted_class == 1) correctSpi++; 

        //DEBUG
        /*if ((i + 1) % 50000 == 0) {
            printf("Pause à l'exemple %d. Appuyez sur Entrée pour continuer...\n", i + 1);
            getchar(); 
        }*/
    }

    float accuracySpi = (float)correctSpi / total;
    printf("=== Résultat du benchmark (précision avec tableau de points) ===\n");
    printf("Corrects : %d / %d (nb points)\n", correctSpi, total);
    printf("Précision : %.2f%%\n", accuracySpi * 100.0);

}

void benchmarkAccuracyDetermineColor(Model model, float **inputs, int nb_samples, int output_size){

    int xMax = WINDOW_WIDTH;
    int yMax = WINDOW_HEIGHT;

    int correctDC = 0;
    for (int i = 0; i < nb_samples; i++) {

        float *prediction = forwardPass(model, inputs[i]);
        int predicted_index = getMaxIndex(prediction, output_size);
        int px = (int)((inputs[i][0]) * (float)xMax);
        int py = (int)((inputs[i][1]) * (float)yMax);

        int r, b;
        determineColor(px, py, &r, &b);
        int expected_indexDC = (r > b) ? 0 : 1;

        //DEBUG
        /*printf("Exemple DT %d:\n", i);
        printf("  Entrée           : [%.2f, %.2f] (px: %d, %d)\n", inputs[i][0], inputs[i][1], px, py);
        printf("  Prédiction réseau: [%f, %f] => classe %d\n", prediction[0], prediction[1], predicted_index);
        printf("  Référence spirale: R=%d B=%d => classe %d\n\n", r, b, expected_indexDC);*/

        if (predicted_index == expected_indexDC) {
            correctDC++;
        }
        //DEBUG
        /*if ((i + 1) % 50000 == 0) {
            printf("Pause à l'exemple %d. Appuyez sur Entrée pour continuer...\n", i + 1);
            getchar(); 
        }*/
    }
    float accuracyDC = (float)correctDC / nb_samples;

    printf("=== Résultat du benchmark (précision avec determineColor) ===\n");
    printf("Corrects : %d / %d (ittérations)\n", correctDC, nb_samples);
    printf("Précision : %.2f%%\n", accuracyDC * 100.0);
}

void benchmarkAccuracyAndTime(Model model, float **inputs, int nb_samples, float **expected_outputs, int output_size, clock_t start, clock_t end) {

    // Accuracy par points 
    benchmarkAccuracyPoints(model, output_size);

    // Accuracy tab expected
    benchmarkAccuracyBRUT(model, inputs, expected_outputs, nb_samples, output_size);

    // Accuracy avec DetermineColor()
    benchmarkAccuracyDetermineColor(model, inputs, nb_samples, output_size);

    // Métrique temporel 
    benchmarkTIME(start, end, nb_samples);

    /* // Recap affichage

    // métrique précision

    printf("=== Résultat du benchmark (précision avec tableau de points) ===\n");
    printf("Corrects : %d / %d (nb points)\n", correctSpi, total);
    printf("Précision : %.2f%%\n", accuracySpi * 100.0);

    printf("=== Résultat du benchmark (précision expected_outputs) ===\n");
    printf("Corrects : %d / %d\n", correct, nb_samples);
    printf("Précision : %.2f%%\n", accuracy * 100.0);

    printf("=== Résultat du benchmark (précision avec determineColor) ===\n");
    printf("Corrects : %d / %d\n", correctDC, nb_samples);
    printf("Précision : %.2f%%\n", accuracyDC * 100.0);

    // métrique temps

    printf("=== Résultat du benchmark (temps) ===\n");
    printf("Temps total : %d min %.2f sec\n", minutes, seconds);
    printf("Temps moyen par instance : %.4f ms\n", avg_time);
    */
}
