#include "cli/cli.h"
#include <stdio.h>

int displayHelp(int argc, char *argv[]) {
    printf("Projet Génie Logiciel - Réseau de neurones\n\n");
    printf("help\n- display help\n");
    printf("draw <figure>\n- display figure\n Currently accepted figures : \n- Spiral\n");
    printf("train --input <filepath> --batch <int> --step <float>\n- train model on using spiral's data.\n--input corresponds to the input file for the model. It is necessarily a .nff files. If absent, creates a new random model.\n--batch corresponds to the number of iteration used to train the model, defaults to 10000.\n--step corresponds to the amount of change to the model each step provides, defaults to 0.001.\n");
    return 0;
}
