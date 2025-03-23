#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cli/cli.h"


char *commands[] = {
    "help",
    "draw",
    "train",
    "generate",
    NULL,
};

char *descriptions[] = {
    "Display help",
    "Draw specified model",
    "Train the given model with the spiral data",
    "Generate a new random model from parameters",
    NULL,
};

void commandParams(int *count, int *longest) {
    *count = 0;
    *longest = 0;
    char **command = commands;
    while(*command != NULL) {
        *count += 1;
        int length = strlen(*command);
        if(length > *longest) {
            *longest = length;
        }
        command++;
    }
}

int displayHelp(int argc, char *argv[]) {
    printf("Projet Génie Logiciel - Réseau de neurones\n");
    
    int count;
    int maxlen;
    commandParams(&count, &maxlen);
    for(int i = 0 ; i < count ; i++) {
        char *cmd = commands[i];
        int step = 0;
        int currlen = strlen(cmd);
        printf("\n  ");
        while(step < maxlen && step < currlen) {
            printf("%c", cmd[step]);
            step++;
        }
        while(step < maxlen) {
            printf(" ");
            step++;
        }
        printf("  ");
        printf("%s", descriptions[i]);
        free(cmd);
    }
    printf("\n\nRun 'COMMAND --help' for more information on a command.\n\n");

    return 0;
}
