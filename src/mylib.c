#include <math.h>
#include <SDL2/SDL.h>
#include "../include/config.h"
#include "../include/mylib.h"

void drawSpiral(SDL_Renderer *renderer, int n) {

    // Spiral 1 : Direction horaire
    for (int i = 1; i < 1.5*n; i++) {
        double angle = i * 2*M_PI/n;
        int x = WINDOW_WIDTH/2 + (int)(WINDOW_WIDTH/2*i/n * cos(angle));
        int y = WINDOW_HEIGHT/2 + (int)(WINDOW_HEIGHT/2*i/n * sin(angle));
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Rouge
        SDL_RenderDrawPoint(renderer, x, y);
    }

    // Spiral 2 : Direction anti-horaire
    for (int i = 1; i < 1.5*n; i++) {
        double angle = i * 2*M_PI/n;
        int x = WINDOW_WIDTH/2 - (int)(WINDOW_WIDTH/2*i/n * cos(-angle));
        int y = WINDOW_HEIGHT/2 + (int)(WINDOW_HEIGHT/2*i/n * sin(-angle));
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); // Bleu
        SDL_RenderDrawPoint(renderer, x, y);
    }

    SDL_RenderPresent(renderer);
}
