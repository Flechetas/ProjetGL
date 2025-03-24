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
    int step = batch_size / DISPLAY_STEP;
    for(int i = 0 ; i < batch_size ; i++) {
        float cost = backpropagate(model, training_step, inputs[i], expecteds[i]);
        avg_cost += cost;
        if(i % step == 0) {
            log_info("step %d | cost : %0.10f", i, avg_cost / step);
            avg_cost = 0;
    
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
