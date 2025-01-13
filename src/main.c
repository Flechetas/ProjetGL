#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL_Init : %s\n", SDL_GetError());
        return 1;
    }

    // Créer une fenêtre
    SDL_Window *window = SDL_CreateWindow(
        "Fenêtre SDL2",                // Titre de la fenêtre
        SDL_WINDOWPOS_CENTERED,       // Position X
        SDL_WINDOWPOS_CENTERED,       // Position Y
        500,                          // Largeur
        500,                          // Hauteur
        SDL_WINDOW_SHOWN              // Flags
    );
    if (!window) {
        printf("Erreur SDL_CreateWindow : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Garder la fenêtre ouverte pendant 3 secondes
    SDL_Delay(3000);

    // Nettoyage
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}