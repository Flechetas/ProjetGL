#include <math.h>
#include <SDL2/SDL.h>
#include "../include/config.h"
#include "../include/mylib.h"

void drawSpiral(SDL_Renderer *renderer, int centerX, int centerY) {
    const double angleStep = M_PI / 60; // 30° en radians
    const int totalSteps = 240;        // 2 tours (720° / 30°)

    // Spiral 1 : Direction horaire
    for (int i = 0; i < totalSteps; i++) {
        double angle = i * angleStep;
        int x = centerX + (int)(20 * angle * cos(angle));
        int y = centerY + (int)(20 * angle * sin(angle));
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Rouge
        SDL_RenderDrawPoint(renderer, x, y);
    }

    // Spiral 2 : Direction anti-horaire
    for (int i = 0; i < totalSteps; i++) {
        double angle = i * angleStep;
        int x = centerX - (int)(20 * angle * cos(-angle));
        int y = centerY + (int)(20 * angle * sin(-angle));
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); // Bleu
        SDL_RenderDrawPoint(renderer, x, y);
    }

    SDL_RenderPresent(renderer);
}
