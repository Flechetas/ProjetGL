#include <math.h>
#include <SDL2/SDL.h>
#include "../include/config.h"
#include "../include/mylib.h"

void drawSpiral(SDL_Renderer *renderer) {

    // Spirale bleue
    for (int t = 0; t < WINDOW_WIDTH/sqrt(2); t+=2) {
        int x = WINDOW_WIDTH/2 + t*cos(t*M_PI/180);
        int y = WINDOW_HEIGHT/2 + t*sin(t*M_PI/180);
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); // Bleu
        SDL_RenderDrawPoint(renderer, x, y);
    }

    //Spirale rouge
    for (int t = 1; t < WINDOW_WIDTH/sqrt(2); t+=2) {
        int x = WINDOW_WIDTH/2 - t*cos(t*M_PI/180);
        int y = WINDOW_HEIGHT/2 - t*sin(t*M_PI/180);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Rouge
        SDL_RenderDrawPoint(renderer, x, y);
    }

    SDL_RenderPresent(renderer);
}
