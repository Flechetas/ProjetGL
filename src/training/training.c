#include "training/training.h"
#include "neuralnet/backpropagation.h"
#include "neuralnet/model.h"
#include <stdio.h>

#define DISPLAY_STEP 100

int train(Model model, float training_step, int batch_size, float **inputs, int input_size, float **expecteds, int expected_size) {
    if(firstLayer(model)->n != input_size) {
        return -1;
    }
    if(lastLayer(model)->n != expected_size) {
        return -1;
    }
    
    float avg_cost = 0;
    int step = batch_size / DISPLAY_STEP;
    for(int i = 0 ; i < batch_size ; i++) {
        float cost = backpropagate(model, training_step, inputs[i], expecteds[i]);
        avg_cost += cost;
        if(i % step == 0) {
            printf("Training step %d | cost : %0.10f\n", i, avg_cost / step);
            avg_cost = 0;
        }
    }

    return 0;
}
