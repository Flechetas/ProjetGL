#include <stdio.h>
#include <string.h>
#include "log.h"
#include "draw/draw.h"

int draw(int argc, char *argv[]) {
    if(argc < 3) {
        log_error("Please specify which figure to draw.\nAccepted figures :\n- Spiral\n- Model <filename>");
        return 1;
    }
    
    if(strcmp(argv[2], "Spiral") == 0) {
        return displaySpiral();
    }

    if (strcmp(argv[2], "Model") == 0) {
        if (argc < 4) {
            log_error("Please specify input file for the model");
            return 1;
        }

        return displayModel(argv[3]);
    }
    
    // If no figure matches
    log_error("Figure %s doesn't match any current figure.\nAccepted figures :\n- Spiral", argv[2]);
    return 1;
}
