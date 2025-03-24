#include <stdio.h>
#include <string.h>

#include "cli/cli.h"
#include "log.h"

int exec(int argc, char *argv[]) {
    // log level to read logs (set for info & above by default)
    log_set_level(2);

    if(argc < 2) {
        printf("Not enough argument. Use help to display help.\n");
        return 1;
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
        return benchmark_execTrain(argc, argv);
    }

    return 0;
}

