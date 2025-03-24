#ifndef DRAW_H
#define DRAW_H

#define M_PI 3.14159265358979323846
#define SPIRAL_VALUE_FILE "spiralFile.txt" // do we really need this ?
#define COLOR_VALUE_FILE "colorValue.txt"

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "neuralnet/model.h"

/*-------------------------------------------------------------------------------
 * ## IMPLEMENTATION NOTES ##                                                    
 *------------------------------------------------------------------------------- 
 *                                                                                  
 * Dans le fichier il y a deux tableaux de couleurs : 1 qui represente           
 * les points bleus, et l'autre qui represente les points rouges.                
 *                                                                               
 * Pour initialiser les tableaux, il faut le faire au debut de l'utilisation par
 *  initSpiralValues()
 * 
 * Pour verifier si les tableaux sont initialises, on a la fonction isInit()
 * 
 * Pour liberer toutes les ressources a la fin de l'utilisation, il faut appeler
 * la fonction freeSpirals
 *                                                                                  
 *-------------------------------------------------------------------------------
 */

/**
 * @brief Type that represents a point.
 */
typedef struct {
    int x, y; ///> x and y for the points
} Point;

/**
 * @brief Function that tells you if the spiral arrays have been initialised
 */
bool isInit();

/**
 * @brief Function used for testing purposes to pull the blue_points array
 */
Point *getBluePoints();

/**
 * @brief Function used for testing purposes to pull the red_points array
 */
Point *getRedPoints();

/**
 * @brief Pulls the length of the blue_points array
 */
int getBlen();

/**
 * @brief Pulls the length of the red_points array
 */
int getRlen();

/**
 * @brief an auxiliary function for qsort, to be used EXCLUSIVELY for comparing point positions in a point array.
 * @param a Pointer to the test point
 * @param b Pointer to the comparison point
 * @return 0 if equal, a negative number if a < b, and a positive number if a > b
 */
int comparePoints(const void* a, const void *b);

/**
 * @brief Function that frees the spiral arrays
 */
void freeSpirals();

/*-------------------------------------------------------*
 *  DISPLAY FUNCTIONS                                    *
 *-------------------------------------------------------*/

/**
 * @brief Function that creates a spiral scene with the sizes given in config.HAVE_ATOF
 */
int displaySpiral();

/**
 * @brief Function that displays a screen based on values calculated by the model passed in the save file
 */
int displayModel(const char *filename);

/**
 * @brief Creates the window and renderer ready for display
 */
int displaySetup();

/**
 * @brief Destroys the window and the renderer
 */
int displayClear();

/**
 * @brief Function that creates a spiral scene with the sizes given in config.HAVE_ATOF
 * @param renderer Presents the spiral scene
 */
void drawSpiral(SDL_Renderer *renderer);

/**
 * @brief Precomputes the values of the spiral and stores them to an allocated local array
 */
void initSpiralValues();

/**
 * @brief Determines all colors at each pixel based on red and blue pixels
 * @param r_out a pointer to where the red value should be stored
 * @param b_out a pointer to where the blue value should be stored
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

/**
 * @brief Presents the result of the points applied to the model
 * @param render Presents the scene
 */
void drawModelResults(Model model);

#endif // DRAW_H
