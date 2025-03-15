#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "neuralnet/model.h"

int benchmark(Model model, int batch_size, float **input, int input_size, float **expected, int expected_size, float *out_accuracy, int *out_duration);

#endif //BENCHMARK_H
