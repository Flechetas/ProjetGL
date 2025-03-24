#ifndef BENCHMARK_FORWARDPASS_H
#define BENCHMARK_FORWARDPASS_H

/**
 * @brief Benchmarks the forward pass of a neural network
 * @param iterations The number of iterations to run the benchmark
 * @param nb_layer The number of layers in the neural network
 * @param input_size The size of the input layer
 * @param hidden_size The size of the hidden layer
 * @param output_size The size of the output layer
 * @return void (prints the results of the benchmark)
*/
 void benchmarkForwardPass(int iterations, int nb_layer,int input_size, int hidden_size, int output_size); ;

#endif // BENCHMARK_FORWARDPASS_H
