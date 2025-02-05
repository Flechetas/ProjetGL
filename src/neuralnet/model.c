#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "../../include/neuralnet/model.h"


int countLayers(Model model) {
    int n = 0;
    Layer curr = model->input;
    while(curr != NULL) {
        curr = curr->next;
        n++; 
    }
    return n;
}

Model createModelRandom(int layer_n, ...) {
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

    Layer curr = createLayerRandom(sizes[layer_n-1], NULL);
    for(int i = layer_n-2 ; i >= 0 ; i--) {
        Layer new = createLayerRandom(sizes[i], curr);
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
