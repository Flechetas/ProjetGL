#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "neuralnet/model.h"
#include "neuralnet/ForwardPass.h"
#include "benchmark/benchmark_ForwardPass.h"


void benchmarkForwardPass(int iterations, int nb_layer,int input_size, int hidden_size, int output_size) {

    // Création d'un modèle de réseau de neurones avec des tailles aléatoires
    Model model = createModelRandom(nb_layer, input_size, hidden_size, output_size);
    
    // Initialisation des valeurs d'entrée
    float input[input_size];
    for (int i = 0; i < input_size; i++) {
        input[i] = ((float) rand() / RAND_MAX) * 2.0 - 1.0; // Valeurs entre -1 et 1
    }

    // Capture du temps avant l'exécution des itérations
    clock_t start = clock();
    
    for (int i = 0; i < iterations; i++) {
        forwardPass(model, input);
    }
    
    // Capture du temps après l'exécution
    clock_t end = clock();

    // Calcul du temps total (différence entre le temps de fin et de début en ms) 
    double total_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
    printf("\n=== Benchmark de la propagation (ForwardPass) ===\n");
    printf("Nombre d'itérations : %d\n", iterations);
    printf("Model utilisé : %d couches (Nb neuronnes -> Entrée: %d, Cachée: %d, Sortie: %d)\n\n", nb_layer, input_size, hidden_size, output_size);
    printf("Temps total : %.4f ms\n", total_time);
    printf("Temps moyen par itération : %.4f ms\n\n", total_time / iterations);
    
    freeModel(model);
}
