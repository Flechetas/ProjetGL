#include <stdlib.h>
#include <stdio.h>
#include "cli/cli.h"
#include "codec/nnf.h"

int generate(int argc, char *argv[]) {
    char *output_file = argv[argc-1];
    if(endsWith(output_file, ".nnf") != 0) {
        printf("Invalid output file %s. Output file must have extension .nnf\n", argv[argc-1]);
        return 1;
    }

    int layer_n = argc-3;
    int *sizes = malloc((layer_n) * sizeof(int));
    for(int i = 0 ; i < layer_n ; i++) {
        int offset = 2; 
        char *size_str = argv[i+offset];
        int size = atoi(size_str);
        if(size == 0) {
            printf("Invalid layer size %s.\n", size_str);
        }
        sizes[i] = size;
    }

    printf("Generating...\n");
    Model model = createModelRandomFromArray(layer_n, sizes);
    saveToFile(model, output_file);
    printf("Saved to %s.\n", output_file);

    return 0;
}
