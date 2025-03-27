#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cli/cli.h"
#include "codec/nnf.h"
#include "log.h"

int displayGenerateHelp() {
    printf("\nDescription: Generates a new random model with given layer sizes\n");
    printf("Usage: generate n1 n2 ... nk <filename.nnf>\n\n");
    printf("Example :\n");
    printf("  generate 2 10 10 2 model.nnf\n");
    printf("  generate 5 100 200 2 output.nnf\n\n");
    return 0;
}

int generate(int argc, char *argv[]) {
    if(argc == 3 && strcmp(argv[2], "--help") == 0) {
        return displayGenerateHelp(); 
    }
    char *output_file = argv[argc-1];
    if(endsWith(output_file, ".nnf") != 0) {
        log_error("Invalid output file %s. Output file must have extension .nnf\n", argv[argc-1]);
        return 1;
    }

    int layer_n = argc-3;
    int *sizes = malloc((layer_n) * sizeof(int));
    for(int i = 0 ; i < layer_n ; i++) {
        int offset = 2; 
        char *size_str = argv[i+offset];
        int size = atoi(size_str);
        if(size == 0) {
            log_error("Invalid layer size %s.\n", size_str);
            return displayGenerateHelp();
        }
        sizes[i] = size;
    }

    log_info("Generating...\n");
    Model model = createModelRandomFromArray(layer_n, sizes);
    saveToFile(model, output_file);
    log_info("Saved to %s.\n", output_file);

    free(sizes);
    freeModel(model);

    return 0;
}
