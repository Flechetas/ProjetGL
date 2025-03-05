#ifndef MYLIB_H
#define MYLIB_H
#define M_PI 3.14159265358979323846

#include <SDL2/SDL.h>

// Déclaration de la fonction drawSpiral
void drawSpiral(SDL_Renderer *renderer, const char *filename);    // Dessine les deux spirales
void determineColor(const char *filename, int px, int py, int *r_out, int *b_out); // Détermine toutes les couleurs à chaque pixel par rapport aux pixels rouges et bleus
void generateColorFile(const char *inputFile, const char *outputFile); // Créé output.txt
void drawColoredPoints(SDL_Renderer *renderer, const char *filename); // Créé à partir de output.txt l'image exemple

#endif // MYLIB_H