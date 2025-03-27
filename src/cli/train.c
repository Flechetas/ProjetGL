#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cli/cli.h"
#include "codec/nnf.h"
#include "log.h"
#include "neuralnet/model.h"
#include "training/numberSuite.h"
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
    printf(" --suite <suite> : the training suite used to train the model\n");
    printf(" --batch <int> : the training dataset size\n");
    printf(" --step <float> : the amount of change of each training step\n");
    printf(" --visualise : specifies if the model should be visualized during the training process");
    printf(" <output.nnf> : the output file name\n\n");
    return 0;
}

int execTrain(int argc, char *argv[]) {
    if(argc == 3 && strcmp(argv[2], "--help") == 0) {
        return displayTrainHelp(); 
    }
    int batch_size = BATCH_SIZE;
    float training_step = TRAINING_STEP;
    char *input_file = INPUT_FILE;
    char *output_file = OUTPUT_FILE;
    char *suite = "";
    int visualized = 0;
    Model model;
    int ret;

    for(int i = 2 ; i < argc ; i++) {
        if(strcmp(argv[i], "--visualize") == 0) {
            visualized = 1;
            continue;
        }
        if(strcmp(argv[i], "--input") == 0) {
            if(i >= argc-1) {
                log_error("Invalid argument count.\n");
                return 1;
            } 
            input_file = argv[i+1];
            i++;
            continue;
        }
        if(strcmp(argv[i], "--suite") == 0) {
            if(i >= argc-1) {
                log_error("Invalid argument count.\n");
                return 1;
            } 
            suite = argv[i+1];
            i++;
            continue;
        }
        if(strcmp(argv[i], "--batch") == 0) {
            if(i >= argc-1) {
                log_error("Invalid argument count.\n");
                return 1;
            } 
            char *batch_size_str = argv[i+1];
            i++;
            batch_size = atoi(batch_size_str);
            if(batch_size == 0) {
                log_error("Invalid argument --batch.\n");    
            }
            continue;
        }
        if(strcmp(argv[i], "--step") == 0) {
            if(i >= argc-1) {
                log_error("Invalid argument cound.\n");
                return 1;
            } 
            char *step_str = argv[i+1];
            i++;
            training_step = (float)atof(step_str);
            if(training_step == 0.0) {
                log_error("Invalid argument --step.\n");    
            }
            continue;
        }
        if(i == argc-1) {
            if(endsWith(argv[i], ".nnf") != 0) {
                log_error("Invalid output file %s. Output file must have extension .nnf", argv[i]);
                return 1;
            }
            output_file = argv[i];
            continue;
        }

        // error
        log_error("Unknown argument : %s.\n", argv[i]);
        return 1;

    }

    if(strcmp(suite, "") == 0) {
        log_error("No training suite given\n");
        return -1;
    }
    if(access(input_file, F_OK) != 0) {
        log_error("Input file %s does not exist.\n", input_file);
        return -1;
    }
    ret = fromFile(input_file, &model);
    if(ret != 0) {
        return ret;
    }
    
    // Train on given suite
    if(strcmp(suite, "spiral") == 0) {
        ret = trainOnSpiral(model, training_step, batch_size, visualized);
        if(ret != 0) {
            return ret;
        }
    }
    if(strcmp(suite, "numbers") == 0) {
        ret = trainOnNumbers(model, training_step);
    }

    saveToFile(model, output_file);

    freeModel(model);

    return 0;    
}
