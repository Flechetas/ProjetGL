#ifndef NUMBER_BENCHMARK_H
#define NUMBER_BENCHMARK_H

#include "neuralnet/model.h"

/**
 * @brief Executes the benchmark of a number model.
 * @param model the model used for the benchmark
 * @return 0 on success, error code otherwise
 */
int benchmarkNumbers(Model model);

#endif //NUMBER_BENCHMARK_H
