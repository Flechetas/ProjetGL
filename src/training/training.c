#include "training/training.h"
#include "neuralnet/backpropagation.h"
#include "neuralnet/model.h"
#include "log.h"
#include "draw/draw.h"

#define DISPLAY_STEP 20

int train(Model model, float training_step, int batch_size, float **inputs, int input_size, float **expecteds, int expected_size, int visualized) {
    if(firstLayer(model)->n != input_size) {
        return -1;
    }
    if(lastLayer(model)->n != expected_size) {
        return -1;
    }
    if(visualized) {
        displaySetup();
    }
    
    float avg_cost = 0;
    float avg_diff = 0;
    int step = batch_size / DISPLAY_STEP;
    for(int i = 0 ; i < batch_size ; i++) {
        float cost = 0;
        float diff = 0;
        backpropagate(model, training_step, inputs[i], expecteds[i], &cost, &diff);
        avg_cost += cost;
        avg_diff += diff;
        if(i % step == step-1) {
            log_info("step %d | cost : %0.10f | diff : %0.10f", i+1, avg_cost / (float)step, avg_diff / (float)step);
            avg_cost = 0;
            avg_diff = 0;
    
            if(visualized) {
                drawModelResults(model);
            }
        }
    }
    
    if(visualized) {
        displayClear();
    }
    return 0;
}
