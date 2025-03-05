#include <math.h>
#include <SDL2/SDL.h>
#include "../../include/config/config.h"
#include "../../include/draw/draw.h"

void drawSpiral(SDL_Renderer *renderer, const char *filename) {
    FILE *file = fopen (filename, "w");
    if(file == NULL) {
        perror("erreur d'ouverture du fichier.");
        return;
    }

    // Spirale bleue
    fprintf(file,"bleu\n");

    for (int t = 0; t < WINDOW_WIDTH/sqrt(2); t+=2) {
        int x = WINDOW_WIDTH/2 + t*cos(t*M_PI/180);
        int y = WINDOW_HEIGHT/2 + t*sin(t*M_PI/180);
        if(x < WINDOW_WIDTH && y < WINDOW_HEIGHT) {
            fprintf(file, "%d\n", x);
            fprintf(file, "%d\n", y);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); // Bleu
        SDL_RenderDrawPoint(renderer, x, y);
    }

    //Spirale rouge
    fprintf(file,"rouge\n");

    for (int t = 1; t < WINDOW_WIDTH/sqrt(2); t+=2) {
        int x = WINDOW_WIDTH/2 - t*cos(t*M_PI/180);
        int y = WINDOW_HEIGHT/2 - t*sin(t*M_PI/180);
        if(x < WINDOW_WIDTH && y < WINDOW_HEIGHT) {
            fprintf(file, "%d\n", x);
            fprintf(file, "%d\n", y);
        }
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Rouge
        SDL_RenderDrawPoint(renderer, x, y);
    }

    fclose(file);
    SDL_RenderPresent(renderer);
}

void determineColor(const char *filename, int px, int py, int *r_out, int *b_out) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier.");
        return;
    }

    int x, y;
    char color[6];
    double totalWeight = 0;
    double weightedR = 0, weightedB = 0;

    // Lire les points et calculer la couleur pondérée
    while (fscanf(file, "%5s", color) == 1) {
        while (fscanf(file, "%d %d", &x, &y) == 2) {
            double dist = sqrt(pow(x - px, 2) + pow(y - py, 2));
            if (dist == 0) continue; // Éviter la division par zéro

            double weight = 1.0 / dist; // Plus un point est proche, plus il pèse
            if (strcmp(color, "rouge") == 0) {
                weightedR += 255 * weight;
            } else {
                weightedB += 255 * weight;
            }
            totalWeight += weight;
        }
    }
    fclose(file);

    // Normalisation des couleurs
    if (totalWeight > 0) {
        *r_out = (int)(weightedR / totalWeight);
        *b_out = (int)(weightedB / totalWeight);
    } else {
        *r_out = *b_out = 128; // Couleur neutre si aucun point trouvé
    }
}

void generateColorFile(const char *inputFile, const char *outputFile) {
    FILE *file = fopen(outputFile, "w");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier de sortie.");
        return;
    }

    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            int r, b;
            determineColor(inputFile, x, y, &r, &b);
            fprintf(file, "%d %d %d %d %d\n", x, y, r, 0, b); // RGB avec G = 0
        }
    }

    fclose(file);
    printf("Fichier %s généré avec succès !\n", outputFile);
}


void drawColoredPoints(SDL_Renderer *renderer, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier.");
        return;
    }

    int x, y, r, g, b;
    while (fscanf(file, "%d %d %d %d %d", &x, &y, &r, &g, &b) == 5) {
        SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawPoint(renderer, x, y);
    }

    fclose(file);
    SDL_RenderPresent(renderer);
}