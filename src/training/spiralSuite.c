#include "training/spiralSuite.h"
#include "draw/draw.h"
#include "config/config.h"
#include "training/training.h"
#include "log.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SPIRAL_VALUE_FILE "spiralFile.txt"
#define COLOR_VALUE_FILE "colorValue.txt"

int trainOnSpiral(Model model, float training_step, int batch_size) {
    printf("Start training on spiral suite.\n");
    printf("training_step : %f | batch_size : %d\n", training_step, batch_size);
    
    // // If there is no precomputed spiral file...
    // if(access(SPIRAL_VALUE_FILE, F_OK) != 0) {
    //     printf("Generating spiral values...\n");
    //     computeSpiralValues(SPIRAL_VALUE_FILE);
    //     printf("Generation complete.\n");
    // } else {
    //     printf("Cached spiral values found.\n"); 
    // }
    // 
    // // If there is not precomputed color file...
    // if(access(COLOR_VALUE_FILE, F_OK) != 0) {
    //     printf("Generating color values...\n");
    //     generateColorFile(COLOR_VALUE_FILE);
    //     printf("Generation complete\n");
    // } else {
    //     printf("Cached color values found.\n");
    // }
    if (!isInit()) {
        log_trace("Initialising spiral values...\n");
        initSpiralValues();
        log_trace("Generation complete!\n");
    }
    else {
        log_trace("Spiral values found\n");
    }

    log_trace("Precomputing training values...\n");
    srand(time(NULL));
    float **inputs = malloc(batch_size * sizeof(float *));
    float **expecteds = malloc(batch_size * sizeof(float *));
    for(int i = 0 ; i < batch_size ; i++) {
        printf("batch step : %d\n", i);

        int xMax = WINDOW_WIDTH;
        int yMax = WINDOW_HEIGHT;

        float x = (rand() % xMax) / (float)xMax;
        float y = (rand() % yMax) / (float)yMax;
        inputs[i] = malloc(2 * sizeof(float));
        inputs[i][0] = x;
        inputs[i][1] = y;
        
        int r;
        int b;
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

    log_trace("Training...\n");
    int ret = train(model, training_step, batch_size, inputs, 2, expecteds, 2);
    if(ret != 0) {
        log_error("Error during training. Stopping.\n");
        return -1;
    }
    log_trace("Training complete.\n");

    return 0;
}
