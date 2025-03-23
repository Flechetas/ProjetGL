#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

#include "neuralnet/model.h"


int countLayers(Model model) {
    int n = 0;
    Layer curr = model->input;
    while(curr != NULL) {
        curr = curr->next;
        n++; 
    }
    return n;
}

Layer firstLayer(Model model) {
    return model->input;
}

Layer lastLayer(Model model) {
    Layer current = model->input;
    while(current->next != NULL) {
        current = current->next;
    }
    return current;
}

Model createModelRandom(int layer_n, ...) {
    srand(time(NULL));
    if(layer_n < 2) {
        return NULL;
    }
    int *sizes = malloc(sizeof(int) * layer_n); // represents the sizes of the intermediary layers
    va_list args;
    va_start(args, layer_n);
    for(int i = 0 ; i < layer_n ; i++) {
        sizes[i] = va_arg(args, int);
    }
    va_end(args);
    
    Model model = createModelRandomFromArray(layer_n, sizes);
    return model;
}

Model createModelRandomFromArray(int layer_n, int layer_sizes[]) {
    Layer curr = createLayerRandom(layer_sizes[layer_n-1], NULL);
    for(int i = layer_n-2 ; i >= 0 ; i--) {
        Layer new = createLayerRandom(layer_sizes[i], curr);
        curr->previous = new;
        curr = new;
    }

    Model model = malloc(sizeof(struct model *));
    model->layer_n = layer_n;
    model->input = curr;
    return model;
}

void freeModel(Model model) {
    Layer curr = model->input;
    while(curr != NULL) {
        Layer next = curr->next;
        freeLayer(curr);
        curr = next;
    }
    free(model);
}
