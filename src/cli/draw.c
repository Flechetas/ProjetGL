#include "draw/draw.h"
#include <stdio.h>
#include <string.h>

int draw(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Please specify which figure to draw.\nAccepted figures :\n- Spiral");
        return 1;
    }
    
    if(strcmp(argv[2], "Spiral") == 0) {
        return displaySpiral();
    }
    
    // If no figure matches
    printf("Figure %s doesn't match any current figure.\nAccepted figures :\n- Spiral", argv[2]);
    return 1;
}
