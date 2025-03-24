#ifndef BENCHMARK_BACKPROPAGATION_H
#define BENCHMARK_BACKPROPAGATION_H

#include "neuralnet/model.h"

/**
 * @brief Benchmarks the backpropagation of a neural network
 * @param iterations The number of iterations to run the benchmark
 * @param nb_layer The number of layers in the neural network
 * @param input_size The size of the input layer
 * @param hidden_size The size of the hidden layer
 * @param output_size The size of the output layer
 * @return void (prints the results of the benchmark)
 */
void benchmarkBackpropagation(int iterations, int nb_layer, int input_size, int hidden_size, int output_size, float training_step);

#endif // BENCHMARK_BACKPROPAGATION_H