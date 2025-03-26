#include <stdio.h>
#include <stdlib.h>

#include "codec/mnist.h"
#include "image/image.h"
#include "training/training.h"
#include "neuralnet/model.h"
#include "log.h"



int loadInputData(const char *filename, int *batch, int *input_size, float ***data) {
    int ret;
    int train_count;
    Image *train_images;
    float **values;

    ret = parseImageIDX(filename, &train_count, &train_images);
    if(ret == -1) {
        return -1;
    }

    values = malloc(train_count * sizeof(float *));
    for(int i = 0 ; i < train_count ; i++) {
        Image img = train_images[i];
        int len = img->rows * img->cols;
        values[i] = malloc(len * sizeof(float));
        for(int j = 0 ; j < len ; j++) {
            values[i][j] = (float)img->pixels[j] / 255.0; 
        }
    }

    *batch = train_count;
    *input_size = train_images[0]->rows * train_images[1]->cols;
    *data = values;

    for(int i = 0 ; i < train_count ; i++) {
        freeImage(train_images[i]);
    }

    return 0;
}

int determineOutput(float *output) {
    float max = output[0];
    int maxind = 0;
    for(int i = 1 ; i < 10 ; i++) {
        if(output[i] > max) {
            max = output[i];
            maxind = i;
        }
    }
    return maxind;
}

int loadTestData(const char *filename, int *batch, int *test_size, float ***data) {
    int ret;
    int train_count;
    int *train_labels;
    float **values;

    ret = parseLabelIDX(filename, &train_count, &train_labels);
    if(ret == -1) {
        return -1;
    }

    values = malloc(train_count * sizeof(float *));
    for(int i = 0 ; i < train_count ; i++) {
        int index = train_labels[i];
        values[i] = malloc(10 * sizeof(float));
        for(int j = 0 ; j < 10 ; j++) {
            values[i][j] = 0.0;
        }
        values[i][index] = 1.0;
    }

    *batch = train_count;
    *test_size = 10;
    *data = values;

    free(train_labels);
    
    return 0;
}

int trainOnNumbers(Model model, float training_step) {
    printf("Start training on number suite.\n");
    printf("training_step : %f\n", training_step);
    
    log_trace("Loading training values...\n");
    int ret;
    int batch;
    int input_size;
    int expected_size;
    float **inputs;
    float **expecteds;
    ret = loadInputData(TRAIN_IMAGES_FILENAME, &batch, &input_size, &inputs);
    if(ret == -1) {
        return -1;
    }
    ret = loadTestData(TRAIN_LABEL_FILENAME, &batch, &expected_size, &expecteds);
    if(ret == -1) {
        return -1;
    }
    log_trace("Loading complete.\n");

    log_trace("Training...\n");
    ret = train(model, training_step, batch, inputs, input_size, expecteds, expected_size, false);
    if(ret != 0) {
        log_error("Error during training. Stopping.\n");
        return -1;
    }
    log_trace("Training complete.\n");

    for(int i = 0 ; i < batch ; i++) {
        free(inputs[i]);
        free(expecteds[i]);
    }
    free(inputs);
    free(expecteds);

    return 0;
}
