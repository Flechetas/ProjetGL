#ifndef BENCHMARK_H
#define BENCHMARK_H

#import "neuralnet/model.h"

double benchmarkAccuracy(Model model, float **input, int input_size, float **expected, int expected_size, int batch_size);
    
#endif //BENCHMARK_H
