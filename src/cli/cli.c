#include <stdio.h>
#include <string.h>
#include "cli/cli.h"

int exec(int argc, char *argv[]) {
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

    return 0;
}

