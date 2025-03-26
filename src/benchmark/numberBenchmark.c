
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
    
    int total = 0;
    int success = 0;
    for(int i = 0 ; i < batch ; i++) {
        float *output_arr = forwardPass(model, inputs[i]);
        int output = determineOutput(output_arr);
        int expected = determineOutput(expecteds[i]);
        if(output == expected) {
            success++;
        }
        total++;
    }

    printf("Total : %d | Success %d\n", total, success);
    printf("Accuracy : %f\n", (float)success / (float)total);
    
    return 0;
}
