#ifndef DRAW_H
#define DRAW_H

#define M_PI 3.14159265358979323846
#define SPIRAL_VALUE_FILE "spiralFile.txt" // do we really need this ?
#define COLOR_VALUE_FILE "colorValue.txt"

#include <SDL2/SDL.h>

/**
 * @brief Type that represents a point.
 */
typedef struct {
    int x, y; ///> x and y for the points
} Point;

/**
 * @brief Function that creates a spiral scene with the sizes given in config.HAVE_ATOF
 */
int displaySpiral();

/**
 * @brief Function that creates a spiral scene with the sizes given in config.HAVE_ATOF
 * @param renderer Presents the spiral scene
 */
void drawSpiral(SDL_Renderer *renderer);

/**
 * @brief Precomputes the values of the spiral in the screen and save it to given file
 * @param filename the given file's name
 */
void initSpiralValues();

/**
 * @brief Determines all colors at each pixel based on red and blue pixels
 * @param renderer Presents the spiral scene
 */
void determineColor(int px, int py, int *r_out, int *b_out);

/**
 * @brief Creates output.txt
 * @param renderer Presents the spiral scene
 */
void generateColorFile(const char *outputFile);

/**
 * @brief Creates the example image from output.txt
 * @param renderer Presents the spiral scene
 */
void drawColoredPoints(SDL_Renderer *renderer, const char *filename);

#endif // DRAW_H
