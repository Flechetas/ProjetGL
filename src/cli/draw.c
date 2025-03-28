#include <stdio.h>
#include <string.h>

#include "log.h"
#include "draw/draw.h"

int displayDrawHelp() {
    printf("\nDescription: displays the given figure\n");
    printf("Usage: draw <figure>\n\n");
    printf("Accepted figures:\n");
    printf("  Spiral\n");
    printf("  Circle\n");
    printf("  Model <filename.nnf>\n\n");
    return 0;
}

int draw(int argc, char *argv[]) {
    if(argc < 3) {
        log_error("Please specify which figure to draw.\n");
        return displayDrawHelp();
    }

    if(strcmp(argv[2], "--help") == 0) {
        return displayDrawHelp(); 
    }
    if(strcmp(argv[2], "Spiral") == 0) {
        return displaySpiral();
    }
    if(strcmp(argv[2], "Circle") == 0) {
        return displayCircle();
    }
    if (strcmp(argv[2], "Model") == 0) {
        if (argc < 4) {
            log_error("Please specify input file for the model\nUse 'draw --help' to display help");
            return 1;
        }

        return displayModel(argv[3]);
    }
    
    // If no figure matches
    log_error("Figure %s doesn't match any current figure.\n", argv[2]);
    return displayDrawHelp();
}
