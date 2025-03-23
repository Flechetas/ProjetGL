#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cli/cli.h"
#include "codec/nnf.h"
#include "neuralnet/model.h"
#include "training/spiralSuite.h"

#define BATCH_SIZE 10000
#define TRAINING_STEP 0.001
#define INPUT_FILE ""
#define OUTPUT_FILE "output.nnf"

int displayTrainHelp() {
    printf("\nDescription: Trains the given model using the spiral data. The input and output layer have to be of size 2\n");
    printf("Usage: train --input <filename.nnf> [options] <output.nnf>\n\n");
    printf("Options :\n");
    printf(" --input <filename.nnf> : the input model file name\n");
    printf(" --batch <int> : the training dataset size\n");
    printf(" --step <float> : the amount of change of each training step\n");
    printf(" <output.nnf> : the output file name\n\n");
    return 0;
}

/*
 * train
 * --input <filepath>
 * --batch <int>    | 10000
 * --step <float>   | 0.001
 *  <output_path>
 */
int execTrain(int argc, char *argv[]) {
    if(argc == 3 && strcmp(argv[2], "--help") == 0) {
        return displayTrainHelp(); 
    }
    int batch_size = BATCH_SIZE;
    float training_step = TRAINING_STEP;
    char *input_file = INPUT_FILE;
    char *output_file = OUTPUT_FILE;
    Model model;
    int ret;

    for(int i = 2 ; i < argc ; i++) {
        if(strcmp(argv[i], "--input") == 0) {
            if(i >= argc-1) {
                printf("Invalid argument cound.\n");
                return 1;
            } 
            input_file = argv[i+1];
            i++;
            continue;
        }
        if(strcmp(argv[i], "--batch") == 0) {
            if(i >= argc-1) {
                printf("Invalid argument cound.\n");
                return 1;
            } 
            char *batch_size_str = argv[i+1];
            i++;
            batch_size = atoi(batch_size_str);
            if(batch_size == 0) {
                printf("Invalid argument --batch.\n");    
            }
            free(batch_size_str);
            continue;
        }
        if(strcmp(argv[i], "--step") == 0) {
            if(i >= argc-1) {
                printf("Invalid argument cound.\n");
                return 1;
            } 
            char *step_str = argv[i+1];
            i++;
            training_step = (float)atof(step_str);
            if(training_step == 0.0) {
                printf("Invalid argument --step.\n");    
            }
            free(step_str);
            continue;
        }
        if(i == argc-1) {
            if(endsWith(argv[i], ".nnf") != 0) {
                printf("Invalid output file %s. Output file must have extension .nnf", argv[i]);
                return 1;
            }
            output_file = argv[i];
            continue;
        }

        // error
        printf("Unknown argument : %s.\n", argv[i]);
        return 1;

    }

    if(access(input_file, F_OK) != 0) {
        printf("Input file %s does not exist.\n", input_file);
    }
    ret = fromFile(input_file, &model);
    if(ret != 0) {
        return ret;
    }

    ret = trainOnSpiral(model, training_step, batch_size);
    if(ret != 0) {
        return ret;
    }

    saveToFile(model, output_file);

    free(input_file);
    free(output_file);
    freeModel(model);

    return 0;    
}
