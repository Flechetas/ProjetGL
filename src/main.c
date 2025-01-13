#include <SDL2/SDL.h>
#include <stdio.h>
#include "config.h"  // Inclure les paramètres de configuration

// Fonction pour appliquer un dégradé
void drawGradient(SDL_Renderer *renderer, int width, int height) {
    // Dégradé entre deux couleurs (rouge et bleu)
    SDL_Color color1 = {255, 0, 0, 255};  // Rouge
    SDL_Color color2 = {0, 0, 255, 255};  // Bleu

    // Création d'un dégradé vertical de haut en bas
    for (int y = 0; y < height; ++y) {
        Uint8 r = color1.r + (color2.r - color1.r) * y / height;
        Uint8 g = color1.g + (color2.g - color1.g) * y / height;
        Uint8 b = color1.b + (color2.b - color1.b) * y / height;
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);

        // Dessiner une ligne horizontale
        SDL_RenderDrawLine(renderer, 0, y, width, y);
    }
}

int main(void)
{
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Erreur d'initialisation SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Créer la fenêtre SDL avec l'option SDL_WINDOW_RESIZABLE
    SDL_Window *window = SDL_CreateWindow(
        "Fenêtre SDL Redimensionnable", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    if (window == NULL) {
        fprintf(stderr, "Erreur lors de la création de la fenêtre SDL : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Créer un renderer pour afficher du contenu
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int running = 1;
    SDL_Event e;

    // Boucle principale du programme
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
            else if (e.type == SDL_WINDOWEVENT) {
                // Si la fenêtre est redimensionnée
                if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    // Récupérer la nouvelle taille de la fenêtre
                    int newWidth, newHeight;
                    SDL_GetWindowSize(window, &newWidth, &newHeight);
                    // Appliquer un dégradé avec la nouvelle taille de la fenêtre
                    drawGradient(renderer, newWidth, newHeight);
                    SDL_RenderPresent(renderer);
                }
            }
        }

        // Effacer la fenêtre avec un fond noir
        SDL_RenderClear(renderer);
        // Appliquer le dégradé avec la taille actuelle de la fenêtre
        drawGradient(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
        // Afficher le rendu
        SDL_RenderPresent(renderer);
    }

    // Libération des ressources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
