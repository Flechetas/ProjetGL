#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "neuralnet/model.h"
#include "neuralnet/layer.h"
#include "neuralnet/ForwardPass.h"

// Fonction de transfert (tangente hyperbolique)
float activationFunction(float x)
{
    return tanhf(x);
}

float* forwardPass(Model model, float *input) {
    // Affectation des valeurs d'entrée à la couche d'entrée
    Layer current = model->input;
    for (int i = 0; i < current->n; i++) {
        current->neurons[i] = input[i];
    }
    
    // Propagation vers toutes les couches jusqu'à la couche de sortie
    while (current->next != NULL) {
        Layer next = current->next;
        // Pour chaque neurone de la couche suivante
        for (int j = 0; j < next->n; j++) {
            float sum = 0.0;
            // Calcul de la somme pondérée (couche actuel)
            for (int i = 0; i < current->n; i++) {
                sum += current->neurons[i] * current->weight[i][j];
            }
            // Application de la fonction de transfert sur la somme
            next->neurons[j] = activationFunction(sum);
        }
        current = next;
    }
    // Traitement de la couche sortie
    for (int i = 0; i < current->n; i++) {
        current->neurons[i] = (current->neurons[i] + 1) / 2;
    }

    // Retourne les valeurs des neurones de la couche de sortie
    return current->neurons;
}
