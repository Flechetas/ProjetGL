#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <time.h>

#include "benchmark/circleBenchmark.h"
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

int checkPoints(Point *points, Model model, int len, int corr_index) {
    int xMax = WINDOW_WIDTH;
    int yMax = WINDOW_HEIGHT;
    int nb_correct = 0;

    for (int i = 0; i < len; i++) {
        float input[2];
        input[0] = ((float)points[i].x / (float)xMax);
        input[1] = ((float)points[i].y / (float)yMax);

        float *prediction = forwardPass(model, input);
        int predicted_class = getMaxIndex(prediction, 3);
        
        if (predicted_class == corr_index) { nb_correct++; }
    }

    return nb_correct;
}

void benchmarkCircleAccuracyPoints(Model model, int output_size){

    if (output_size != 3) {
        log_error("Invalid model");
        freePoints();
        exit(EXIT_FAILURE);
    }
    
    Point *red_points = getRedPoints();
    Point *blue_points = getBluePoints();
    Point *green_points = getGreenPoints();
    int red_count = getRlen(), blue_count = getBlen(), green_count = getGlen();

    log_debug("red_count = %d", red_count);
    log_debug("blue_count = %d", blue_count);
    log_debug("green_count = %d", green_count);

    int nb_correct = 0;
    int total = red_count + blue_count + green_count;

    clock_t start = clock();

    //Verification par rapport aux points des cercles
    nb_correct += checkPoints(red_points, model, red_count, 0);
    nb_correct += checkPoints(blue_points, model, blue_count, 1);
    nb_correct += checkPoints(green_points, model, green_count, 2);

    clock_t end = clock();

    double total_time = (double)(end - start) / CLOCKS_PER_SEC;
    double avg_time = total_time / total * 1000.0;
    int minutes = (int)(total_time / 60);
    double seconds = total_time - minutes * 60;
    float accuracy = (float)nb_correct / total;
    printf("=== Résultat du benchmark (précision avec tableau de points) ===\n");
    printf("Corrects : %d / %d (nb points)\n", nb_correct, total);
    printf("Précision : %.2f%%\n", accuracy * 100.0);
    printf("Temps total : %d min %.2f sec\n", minutes, seconds);
    printf("Temps moyen par instance : %.4f ms\n", avg_time);

}

int benchmarkCircle(Model model) {
    if (!draw_isInit()) {
        log_trace("Initialising spiral values...\n");
        initCirclePoints();
        log_trace("Generation complete!\n");
    }
    else {
        log_trace("Spiral values found\n");
    }
    benchmarkCircleAccuracyPoints(model, 3);
    freePoints();

    return 0;
}
