#include <stdio.h>
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

void freeModel(Model model) {
    Layer curr = model->input;
    while(curr != NULL) {
        Layer next = curr->next;
        freeLayer(curr);
        curr = next;
    }
    free(model);
}
