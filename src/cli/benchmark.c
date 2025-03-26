#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "benchmark/numberBenchmark.h"
#include "cli/cli.h"
#include "codec/nnf.h"
#include "log.h"
#include "neuralnet/model.h"


int execBenchmark(int argc, char **argv) {
    int ret;
    char *input_file = "";
    char *suite = "";
    Model model;

    for(int i = 2 ; i < argc ; i++) {
        if(strcmp(argv[i], "--input") == 0) {
            if(i >= argc-1) {
                printf("Invalid argument found.\n");
                return 1;
            } 
            input_file = argv[i+1];
            i++;
            continue;
        }
        if(strcmp(argv[i], "--suite") == 0) {
            if(i >= argc-1) {
                printf("Invalid argument found.\n");
                return 1;
            } 
            suite = argv[i+1];
            i++;
            continue;
        }
    }
    
    if(access(input_file, F_OK) != 0) {
        log_error("Wrong file name %s", input_file);
        return -1;
    }
    ret = fromFile(input_file, &model);
    if(ret == -1) {
        log_error("Error loading model");
        return -1; 
    }

    if(strcmp(suite, "spiral") == 0) {
        // spiral benchmark
    }
    if(strcmp(suite, "numbers") == 0) {
        ret = benchmarkNumbers(model);
        if(ret != 0) {
            log_error("Error during benchmarking");
            return -1;
        }
        return 0;
    }
    
    printf("No matching suite found.");
    return -1;
}
