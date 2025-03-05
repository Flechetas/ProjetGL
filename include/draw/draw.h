#ifndef MYLIB_H
#define MYLIB_H
#define M_PI 3.14159265358979323846

#include <SDL2/SDL.h>

/**
 * @brief Function that creates a spiral scene with the sizes given in config.HAVE_ATOF
 * @param renderer Presents the spiral scene
 */
void drawSpiral(SDL_Renderer *renderer, const char *filename);

/**
 * @brief Determines all colors at each pixel based on red and blue pixels
 * @param renderer Presents the spiral scene
 */
void determineColor(const char *filename, int px, int py, int *r_out, int *b_out);

/**
 * @brief Creates output.txt
 * @param renderer Presents the spiral scene
 */
void generateColorFile(const char *inputFile, const char *outputFile);

/**
 * @brief Creates the example image from output.txt
 * @param renderer Presents the spiral scene
 */
void drawColoredPoints(SDL_Renderer *renderer, const char *filename);

#endif // MYLIB_H