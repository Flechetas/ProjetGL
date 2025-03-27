#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "training/spiralSuite.h"
#include "draw/draw.h"
#include "config/config.h"
#include "training/training.h"
#include "log.h"

#define SPIRAL_VALUE_FILE "spiralFile.txt"
#define COLOR_VALUE_FILE "colorValue.txt"

int trainOnSpiral(Model model, float training_step, int batch_size, int visualized) {
    printf("Start training on spiral suite.\n");
    printf("training_step : %f | batch_size : %d\n", training_step, batch_size);
    
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
    int r=0;
    int b=0;
    int xMax = WINDOW_WIDTH;
    int yMax = WINDOW_HEIGHT;
    
    Point *points;

    float **inputs = malloc(batch_size * sizeof(float *));
    float **expecteds = malloc(batch_size * sizeof(float *));
    for(int i = 0 ; i < batch_size ; i++) {
        int ind = rand() % (getRlen() + getBlen()); 

        if (ind < getRlen()) {
            points = getRedPoints();
            r = 1, b = 0;
        }
        else {
            points = getBluePoints();
            ind -= getRlen();
            r = 0, b = 1;
        }
        if (points[ind].x > xMax || points[ind].y > yMax || points[ind].x < 0 || points[ind].y < 0) {
            log_debug("Current point : x = %d, y = %d, %s", points[ind].x, points[ind].y, (r > b) ? "red" : "blue");
        }

        inputs[i] = malloc(2 * sizeof(float));
        inputs[i][0] = (float)(points[ind].x) / (float)xMax;
        inputs[i][1] = (float)(points[ind].y) / (float)yMax;
        
        if (inputs[i][0] > 1 || inputs[i][1] > 1 || inputs[i][0] < 0 || inputs[i][1] < 0) {
            log_debug("Current input: x = %d, y = %d", inputs[i][0], inputs[i][1]);
        }

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
    int ret = train(model, training_step, batch_size, inputs, 2, expecteds, 2, visualized);
    if(ret != 0) {
        log_error("Error during training. Stopping.\n");
        return -1;
    }
    log_trace("Training complete.\n");

    for(int i = 0 ; i < batch_size ; i++) {
        free(inputs[i]);
        free(expecteds[i]);
    }
    free(inputs);
    free(expecteds);

    return 0;
}
