#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "training/circleSuite.h"
#include "draw/draw.h"
#include "config/config.h"
#include "training/training.h"
#include "log.h"


int trainOnCircles(Model model, float training_step, int batch_size, int visualized) {
    log_info("Start training on circle suite.");
    log_info("training_step : %f | batch_size : %d", training_step, batch_size);
    
    if (!draw_isInit()) {
        log_trace("Initialising spiral values...");
        initCirclePoints();
        log_trace("Generation complete!");
    }
    else {
        log_trace("Circle values found");
    }

    log_trace("Precomputing training values...");
    srand(time(NULL));
    int r=0, g=0, b=0;

    int xMax = WINDOW_WIDTH;
    int yMax = WINDOW_HEIGHT;
    
    Point *points;

    float **inputs = malloc(batch_size * sizeof(float *));
    float **expecteds = malloc(batch_size * sizeof(float *));
    for(int i = 0 ; i < batch_size ; i++) {
        int ind = rand() % (getRlen() + getBlen() + getGlen()); 

        if (ind < getRlen()) {
            points = getRedPoints();
            r = 1, g= 0, b = 0;
        }
        else if (ind < getRlen() + getBlen()) {
            points = getBluePoints();
            ind -= getRlen();
            r = 0, g = 0, b = 1;
        }
        else {
            points = getGreenPoints();
            ind -= (getRlen() + getBlen());
            r = 0, g = 1, b = 0;
        }

        if (points[ind].x > xMax || points[ind].y > yMax || points[ind].x < 0 || points[ind].y < 0) {
            log_debug("Current point : x = %d, y = %d, %s", points[ind].x, points[ind].y);
        }

        inputs[i] = malloc(2 * sizeof(float));
        inputs[i][0] = (float)(points[ind].x) / (float)xMax;
        inputs[i][1] = (float)(points[ind].y) / (float)yMax;
        
        if (inputs[i][0] > 1 || inputs[i][1] > 1 || inputs[i][0] < 0 || inputs[i][1] < 0) {
            log_debug("Current input: x = %d, y = %d", inputs[i][0], inputs[i][1]);
        }

        expecteds[i] = malloc(3 * sizeof(float));
        
        expecteds[i][0] = (float)r;
        expecteds[i][1] = (float)b;
        expecteds[i][2] = (float)g;
        
    }
    log_trace("Precomputing complete.");

    log_trace("Training...\n");
    int ret = train(model, training_step, batch_size, inputs, 2, expecteds, 3, visualized);
    if(ret != 0) {
        log_error("Error during training. Stopping.");
        return -1;
    }
    log_trace("Training complete.");

    for(int i = 0 ; i < batch_size ; i++) {
        free(inputs[i]);
        free(expecteds[i]);
    }
    free(inputs);
    free(expecteds);
    freePoints();

    return 0;
}
