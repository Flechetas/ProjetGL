#include <stdio.h>
#include "benchmark/benchmark_ForwardPass.h"
#include "benchmark/benchmark_backPropagation.h"

// Compil : 
/*

gcc -o build/main_benchmark \
    src/benchmark/main_benchmark.c \
    src/benchmark/benchmark_ForwardPass.c \
    src/benchmark/benchmark_BackPropagation.c \
    src/neuralnet/model.c \
    src/neuralnet/ForwardPass.c \
    src/neuralnet/layer.c \
    src/neuralnet/backpropagation.c \
    -Iinclude -lm
    &&
    ./build/main_benchmark

*/
/*
int main() {    
    int iterations = 1000;      // Nombre d'exécutions pour le benchmark
    int nb_layer = 3;           // Nombre de couches
    int input_size = 10;        // Nombre de neuronnes de la couche d'entrée
    int hidden_size = 20;       // Nombre de neuronnes de la/les couche cachée
    int output_size = 5;        // Nombre de neuronnes de la couche de sortie
    int training_step = 0.1;    // Pas d'apprentissage
    
    benchmarkForwardPass(iterations, nb_layer, input_size, hidden_size, output_size);
    benchmarkBackpropagation(iterations, nb_layer, input_size, hidden_size, output_size, training_step);
    
    return 0;
}*/