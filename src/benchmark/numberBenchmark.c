#include <time.h>

#include "benchmark/numberBenchmark.h"
#include "codec/mnist.h"
#include "neuralnet/ForwardPass.h"
#include "training/numberSuite.h"

int benchmarkNumbers(Model model) {
    int ret;
    int batch;
    int input_size;
    float **inputs;
    int test_size;
    float **expecteds;
    
    clock_t start = clock();
    ret = loadInputData(TEST_IMAGES_FILENAME, &batch, &input_size, &inputs);
    if(ret != 0) {
        printf("Error loading input data\n");
        return -1;
    }
    ret = loadTestData(TEST_LABEL_FILENAME, &batch, &test_size, &expecteds);
    if(ret != 0) {
        printf("Error loading test data\n");
        return -1;
    }
    
    int success = 0;
    for(int i = 0 ; i < batch ; i++) {
        float *output_arr = forwardPass(model, inputs[i]);
        int output = determineOutput(output_arr);
        int expected = determineOutput(expecteds[i]);
        if(output == expected) {
            success++;
        }
    }

    clock_t end = clock();

    double total_time = (double)(end - start) / CLOCKS_PER_SEC;
    double avg_time = total_time / batch * 1000.0;
    int minutes = (int)(total_time / 60);
    double seconds = total_time - minutes * 60;
    float accuracyDC = (float)success / batch;

    printf("=== Résultat du benchmark (précision avec determineColor) ===\n");
    printf("Corrects : %d / %d (itérations)\n", success, batch);
    printf("Précision : %.2f%%\n", accuracyDC * 100.0);
    printf("Temps total : %d min %.2f sec\n", minutes, seconds);
    printf("Temps moyen par instance : %.4f ms\n", avg_time);

    return 0;
}
