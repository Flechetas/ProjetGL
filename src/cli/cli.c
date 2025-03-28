#include <stdio.h>
#include <string.h>

#include "cli/cli.h"
#include "log.h"

int exec(int argc, char *argv[]) {
    // log level to read logs (set for info & above by default)
    log_set_level(2);

    if(argc < 2) {
        log_error("Not enough arguments.\n");
        return displayHelp(argc, argv); 
    } 

    char *arg = argv[1];
    if(strcmp(arg, "help") == 0) {
        return displayHelp(argc, argv); 
    }
    if(strcmp(arg, "draw") == 0) {
        return draw(argc, argv);
    }
    if(strcmp(arg, "train") == 0) {
        return execTrain(argc, argv);
    }
    if(strcmp(arg, "generate") == 0) {
        return generate(argc, argv);
    }
    if(strcmp(arg, "benchmark") == 0) {
        return execBenchmark(argc, argv);
    }

    return 0;
}

