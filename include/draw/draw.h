#ifndef DRAW_H
#define DRAW_H

#define M_PI 3.14159265358979323846
#define SPIRAL_VALUE_FILE "spiralFile.txt"
#define COLOR_VALUE_FILE "colorValue.txt"

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "neuralnet/model.h"

/*-------------------------------------------------------*
 *  POINT GENERATION FUNCTIONS                           *
 *-------------------------------------------------------*/

/*-------------------------------------------------------------------------------
 * ## NOTES D'IMPLEMENTATION ##                                                    
 *------------------------------------------------------------------------------- 
 *                                                                                  
 * Dans le fichier il y a deux tableaux de couleurs : 1 qui represente           
 * les points bleus, et l'autre qui represente les points rouges.                
 *                                                                               
 * Pour initialiser les tableaux, il faut le faire au debut de l'utilisation par
 *  initSpiralPoints()
 * 
 * Pour verifier si les tableaux sont initialises, on a la fonction isInit()
 * 
 * Pour liberer toutes les ressources a la fin de l'utilisation, il faut appeler
 * la fonction freePoints()
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
 * @brief Precomputes the values of the spirals and stores them into allocated local arrays
 */
void initSpiralPoints();

/**
 * @brief Precomputes the values of the circles and stores them into allocated local arrays
 */
void initCirclePoints();

/**
 * @brief Function that tells you if the spiral arrays have been initialised
 */
bool draw_isInit();

/**
 * @brief Function used to pull the blue_points array
 */
Point *getBluePoints();

/**
 * @brief Function used to pull the red_points array
 */
Point *getRedPoints();

/**
 * @brief Function used to pull the green_points array
 */
Point *getGreenPoints();

/**
 * @brief Pulls the length of the blue_points array
 */
int getBlen();

/**
 * @brief Pulls the length of the red_points array
 */
int getRlen();

/**
 * @brief Pulls the length of the green_points array
 */
int getGlen();

/**
 * @brief Determines all colors at each pixel based on distance from red and blue pixels
 * @param r_out a pointer to where the red value should be stored
 * @param b_out a pointer to where the blue value should be stored
 */
void determineColor(int px, int py, int *r_out, int *b_out);

/**
 * @brief Function that frees the spiral arrays
 */
void freePoints();

/*-------------------------------------------------------*
 *  DISPLAY FUNCTIONS                                    *
 *-------------------------------------------------------*/

/**
 * @brief Function that creates a spiral scene with the sizes given in config.HAVE_ATOF
 */
int displaySpiral();

/**
 * @brief Function that creates a circle scene
 */
int displayCircle();

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
void drawSpiral();

/**
 * @brief Presents the result of the points applied to the model
 * @param render Presents the scene
 */
void drawModelResults(Model model);

#endif // DRAW_H
