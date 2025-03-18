#include <stdio.h>
#include "benchmark/benchmark_ForwardPass.h"

int main() {
    int iterations = 1000; // Nombre d'exécutions pour le benchmark
    benchmarkForwardPass(iterations);
    return 0;
}
