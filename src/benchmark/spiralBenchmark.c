#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <time.h>

#include "neuralnet/model.h"
#include "neuralnet/forwardpass.h"
#include "draw/draw.h"    
#include "config/config.h"  
#include "draw/draw.h"
#include "config/config.h"
#include "log.h"

#define SAMPLE_SIZE 1000

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

void benchmarkAccuracyBRUT(Model model, float **inputs, float **expected_outputs, int nb_samples, int output_size) {
    int correct = 0;

    clock_t start = clock();
    for (int i = 0; i < nb_samples; i++) {
        //float *prediction = forwardPass(model, inputs[i]);
        float *prediction = getOutputValues(model);
        int predicted_index = getMaxIndex(prediction, output_size);
        int expected_index = getMaxIndex(expected_outputs[i], output_size);

        if (predicted_index == expected_index) {
            correct++;
        }
    }


    clock_t end = clock();

    double total_time = (double)(end - start) / CLOCKS_PER_SEC;
    double avg_time = total_time / nb_samples * 1000.0;
    int minutes = (int)(total_time / 60);
    double seconds = total_time - minutes * 60;
    float accuracy = (float)correct / nb_samples;
    printf("=== Résultat du benchmark (précision expected_outputs) ===\n");
    printf("Corrects : %d / %d (itérations)\n", correct, nb_samples);
    printf("Précision : %.2f%%\n", accuracy * 100.0);
    printf("Temps total : %d min %.2f sec\n", minutes, seconds);
    printf("Temps moyen par instance : %.4f ms\n", avg_time);

}

void benchmarkAccuracyPoints(Model model, int output_size){
    
    //initSpiralPoints(); 

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

    clock_t start = clock();

    //Par rapport aux points de la spirale
    // points rouges
    for (int i = 0; i < red_count; i++) {
        float input[2];
        input[0] = ((float)red_points[i].x / (float)xMax);
        input[1] = ((float)red_points[i].y / (float)yMax);

        float *prediction = forwardPass(model, input);
        int predicted_class = getMaxIndex(prediction, output_size);

        if (predicted_class == 0) correctSpi++; 
    }

    // points bleus
    for (int i = 0; i < blue_count; i++) {
        float input[2];
        input[0] = ((float)blue_points[i].x / (float)xMax);
        input[1] = ((float)blue_points[i].y / (float)yMax);

        float *prediction = forwardPass(model, input);
        int predicted_class = getMaxIndex(prediction, output_size);

        if (predicted_class == 1) correctSpi++; 
    }

    clock_t end = clock();

    double total_time = (double)(end - start) / CLOCKS_PER_SEC;
    double avg_time = total_time / total * 1000.0;
    int minutes = (int)(total_time / 60);
    double seconds = total_time - minutes * 60;
    float accuracySpi = (float)correctSpi / total;
    printf("=== Résultat du benchmark (précision avec tableau de points) ===\n");
    printf("Corrects : %d / %d (nb points)\n", correctSpi, total);
    printf("Précision : %.2f%%\n", accuracySpi * 100.0);
    printf("Temps total : %d min %.2f sec\n", minutes, seconds);
    printf("Temps moyen par instance : %.4f ms\n", avg_time);

}

void benchmarkAccuracyDetermineColor(Model model, float **inputs, int nb_samples, int output_size){

    int xMax = WINDOW_WIDTH;
    int yMax = WINDOW_HEIGHT;

    int correctDC = 0;
    clock_t start = clock();
    for (int i = 0; i < nb_samples; i++) {

        float *prediction = forwardPass(model, inputs[i]);
        int predicted_index = getMaxIndex(prediction, output_size);
        int px = (int)((inputs[i][0]) * (float)xMax);
        int py = (int)((inputs[i][1]) * (float)yMax);

        int r, b;
        determineColor(px, py, &r, &b);
        int expected_indexDC = (r > b) ? 0 : 1;

        if (predicted_index == expected_indexDC) {
            correctDC++;
        }
    }

    clock_t end = clock();

    double total_time = (double)(end - start) / CLOCKS_PER_SEC;
    double avg_time = total_time / nb_samples * 1000.0;
    int minutes = (int)(total_time / 60);
    double seconds = total_time - minutes * 60;
    float accuracyDC = (float)correctDC / nb_samples;

    printf("=== Résultat du benchmark (précision avec determineColor) ===\n");
    printf("Corrects : %d / %d (itérations)\n", correctDC, nb_samples);
    printf("Précision : %.2f%%\n", accuracyDC * 100.0);
    printf("Temps total : %d min %.2f sec\n", minutes, seconds);
    printf("Temps moyen par instance : %.4f ms\n", avg_time);
}

void benchmarkAccuracyAndTime(Model model, float **inputs, int nb_samples, float **expected_outputs, int output_size, clock_t start, clock_t end) {

    // Accuracy par points 
    benchmarkAccuracyPoints(model, output_size);

    // Accuracy tab expected
    benchmarkAccuracyBRUT(model, inputs, expected_outputs, nb_samples, output_size);

    // Accuracy avec DetermineColor()
    benchmarkAccuracyDetermineColor(model, inputs, nb_samples, output_size);
}

int benchmarkSpiral(Model model) {
    if (!draw_isInit()) {
        log_trace("Initialising spiral values...\n");
        initSpiralPoints();
        log_trace("Generation complete!\n");
    }
    else {
        log_trace("Spiral values found\n");
    }

    log_trace("Precomputing training values...\n");
    srand(time(NULL));
    int r;
    int b;
    int xMax = WINDOW_WIDTH;
    int yMax = WINDOW_HEIGHT;
    float **inputs = malloc(SAMPLE_SIZE * sizeof(float *));
    float **expecteds = malloc(SAMPLE_SIZE * sizeof(float *));
    for(int i = 0 ; i < SAMPLE_SIZE ; i++) {
        float x = rand() % xMax;
        float y = rand() % yMax;
        inputs[i] = malloc(2 * sizeof(float));
        inputs[i][0] = x / (float)xMax;
        inputs[i][1] = y / (float)yMax;
        
        determineColor(x, y, &r, &b);
        expecteds[i] = malloc(2 * sizeof(float));
        if(r > b) {
            expecteds[i][0] = 1.0;
            expecteds[i][1] = 0.0;
        } else {
            expecteds[i][0] = 0.0;
            expecteds[i][1] = 1.0;
        }
    }
    log_trace("Precomputing complete.\n");

    clock_t start = clock();
    clock_t end = clock();
    benchmarkAccuracyAndTime(model, inputs, SAMPLE_SIZE, expecteds, 2, start, end);

    for(int i = 0 ; i < SAMPLE_SIZE ; i++) {
        free(inputs[i]);
        free(expecteds[i]);
    }
    free(inputs);
    free(expecteds);

    return 0;
}
