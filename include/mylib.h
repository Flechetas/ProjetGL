#ifndef MYLIB_H
#define MYLIB_H
#define M_PI 3.14159265358979323846

#include <SDL2/SDL.h>

/**
 * @brief Function which creates a spiral scene with the sizes given in config.HAVE_ATOF
 * @param renderer Presents the spiral scene
 */
void drawSpiral(SDL_Renderer *renderer);

#endif // MYLIB_H