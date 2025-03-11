#include "training/training.h"
#include "neuralnet/backpropagation.h"
#include "neuralnet/model.h"
#include <stdio.h>


int train(Model model, float training_step, int batch_size, float **inputs, int input_size, float **expecteds, int expected_size) {
    if(firstLayer(model)->n != input_size) {
        return -1;
    }
    if(lastLayer(model)->n != expected_size) {
        return -1;
    }
    
    for(int i = 0 ; i < batch_size ; i++) {
        float cost = backpropagate(model, training_step, inputs[i], expecteds[i]);
        printf("Training step %d | cost : %f\n", i, cost);
    }

    return 0;
}
