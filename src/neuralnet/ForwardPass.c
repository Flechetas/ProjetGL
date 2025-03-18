#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "neuralnet/model.h"
#include "neuralnet/layer.h"
#include "neuralnet/ForwardPass.h"


// Fonction d'initialisation d'un neurone pour un pixel donné 
void initNeuron(Layer layer, int index, float value) 
{
    if (index < layer->n) {
        layer->neurons[index] = value;
    }
}

// initialise les entrées aléatoirement entre -1 et 1
void initRandomInputs(float *inputs, int size) {
    for (int i = 0; i < size; i++) {
        inputs[i] = ((float)rand() / RAND_MAX) * 2.0 - 1.0;
    }
}

// Fonction de transfert (tangente hyperbolique)
float activationFunction(float x)
{ 
    return (expf(x) - expf(-x)) / (expf(x) + expf(-x));
}


// Fonction qui calcule la valeur du neurone suivant dans la couche cachée
void computeNextNeuronValue(Layer currentLayer, int neuronIndex) {
    if (currentLayer->next == NULL) {
        printf("Erreur: la couche suivante n'existe pas.\n");
        return;
    }
    
    float sum = 0.0;
    for (int i = 0; i < currentLayer->n; i++) {
        sum += currentLayer->neurons[i] * currentLayer->weight[i][neuronIndex];
    }
    
    currentLayer->next->neurons[neuronIndex] = activationFunction(sum);
}

// Fonction qui initialise les neurones et calcule les valeurs pour la couche cachée
void processNeuronLayer(Layer inputLayer, Layer hiddenLayer, float *inputValues, int inputSize) {
    if (inputSize != inputLayer->n) {
        printf("Erreur: La taille des entrées ne correspond pas au nombre de neurones de la couche d'entrée.\n");
        return;
    }
    
    // Initialisation des neurones de la couche d'entrée
    for (int i = 0; i < inputSize; i++) {
        initNeuron(inputLayer, i, inputValues[i]);
    }
    
    // Calcul des valeurs des neurones de la couche cachée
    for (int i = 0; i < hiddenLayer->n; i++) {
        computeNextNeuronValue(inputLayer, i);
    }
}

void initRandomFloatArray(float *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = ((float)rand() / RAND_MAX) * 2.0 - 1.0;
    }
}

// Initialise les neurones d'une couche avec un tableau de valeurs
void initializeLayerNeurons(Layer layer, float *values) {
    for (int i = 0; i < layer->n; i++) {
        layer->neurons[i] = values[i];
    }
}

// Effectue la propagation d'une couche à la suivante
void propagateLayer(Layer current) {
    if (current->next == NULL) {
        return;
    }
    Layer next = current->next;
    for (int j = 0; j < next->n; j++) {
        float sum = 0.0;
        for (int i = 0; i < current->n; i++) {
            sum += current->neurons[i] * current->weight[i][j];
        }
        next->neurons[j] = activationFunction(sum);
    }
}

// Effectue la propagation sur un réseau de neurones
float* forwardPass(Model model, float *input) {
    // Affectation des valeurs d'entrée à la couche d'entrée
    Layer current = model->input;
    initializeLayerNeurons(current, input);
    
    // Propagation vers toutes les couches jusqu'à la couche de sortie
    while (current->next != NULL) {
        propagateLayer(current);
        current = current->next;
    }
    
    // Retourne les valeurs des neurones de la couche de sortie
    return current->neurons;
}


 // Old version (all in one)
 /*
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

    // Retourne les valeurs des neurones de la couche de sortie
    return current->neurons;
}
 */
