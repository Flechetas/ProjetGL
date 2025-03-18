#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "neuralnet/model.h"
#include "neuralnet/ForwardPass.h"
#include "benchmark/benchmark_ForwardPass.h"

#define NB_LAYER 3  // Nombre de couches

// Nombres de neurones pour chaque couche
#define INPUT_SIZE 10  // Nombre de neurones en entrée
#define HIDDEN_SIZE 20  // Nombre de couche cachée
#define OUTPUT_SIZE 5  // Nombre de neurones en sortie


void benchmarkForwardPass(int iterations) {
    // Création d'un modèle de réseau de neurones avec des tailles aléatoires
    Model model = createModelRandom(NB_LAYER, INPUT_SIZE, HIDDEN_SIZE, OUTPUT_SIZE); // 3 couches (entrée:10, cachée:20, sortie:5)
    
    // Initialisation des valeurs d'entrée
    float input[INPUT_SIZE];
    for (int i = 0; i < INPUT_SIZE; i++) {
        input[i] = ((float) rand() / RAND_MAX) * 2.0 - 1.0; // Valeurs entre -1 et 1
    }

    // Capture du temps avant l'exécution des itérations
    clock_t start = clock();
    
    for (int i = 0; i < iterations; i++) {
        forwardPass(model, input);
    }
    
    // Capture du temps après l'exécution
    clock_t end = clock();

    // Calcul du temps moyen par itération en millisecondes
    double total_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
    printf("Temps total pour %d exécutions: %.4f ms\n", iterations, total_time);
    printf("Temps moyen par exécution: %.4f ms\n", total_time / iterations);
    
    // Libération de la mémoire
    freeModel(model);
}
