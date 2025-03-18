#include <SDL2/SDL.h>
#include "cli/cli.h"

int main(int argc, char *argv[]) {

    return exec(argc, argv);

<<<<<<< HEAD
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderClear(renderer);

    drawSpiral(renderer);

    SDL_RenderPresent(renderer);
    SDL_Delay(3000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
=======
>>>>>>> dev
}
