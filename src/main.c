#include <SDL2/SDL.h>
#include <stdio.h>
#include "config/config.h"
#include "draw/draw.h"

int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Coloration par Distance",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_RESIZABLE);
    if (!window) {
        printf("Erreur SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    drawSpiral(renderer, "spirales.txt");

    //generateColorFile("spirales.txt", "output.txt");

    drawColoredPoints(renderer, "output.txt");

    SDL_RenderPresent(renderer);
    SDL_Delay(5000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
