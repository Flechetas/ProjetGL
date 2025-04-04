#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "config/config.h"
#include "draw/draw.h"
#include "log.h"

Point *red_points;
Point *blue_points;
int rlen=0, blen=0;
bool is_init;

// frees the 2 color arrays (to be called at the end of main)
void freePoints() {
    if (!is_init) {
        log_error("Tableaux de points non-initialisees");
        exit(EXIT_FAILURE);
    }

    if (rlen > 0) {
        free(red_points);
    }
    if (blen > 0) {
        free(blue_points);
    }
    
    is_init = false;
    rlen=0, blen=0;
}

bool draw_isInit() {
    return is_init;
} 

Point *getBluePoints() {
    if (!is_init) {
        log_error("Tableaux de points non-initialisees");
        exit(EXIT_FAILURE);
    }

    return blue_points;
}

Point *getRedPoints() {
    if (!is_init) {
        log_error("Tableaux de points non-initialisees");
        exit(EXIT_FAILURE);
    }

    return red_points;
}

int getBlen() {
    if (!is_init) {
        log_error("Tableaux de points non-initialisees");
        exit(EXIT_FAILURE);
    }

    return blen;
}

int getRlen() {
    if (!is_init) {
        log_error("Tableaux de points non-initialisees");
        exit(EXIT_FAILURE);
    }

    return rlen;
}

void initSpiralPoints() {
    if (is_init) {
        log_error("Tableaux de points deja initialisees");
        exit(EXIT_FAILURE);
    }
    
    log_info("Initialisation des tableaux de points des spirales...");
    
    log_info("Allocation des tableaux...");
    red_points = malloc(sizeof(Point));
    blue_points = malloc(sizeof(Point));
    int blue_capacity = 0, red_capacity = 0;
    
    if (red_points == NULL || blue_points == NULL) {
        log_error("Echec d'allocation de tableau");
        exit(EXIT_FAILURE);
    }
    log_info("Allocation effectuee avec succes!");

    // Spirale bleue
    log_info("Remplissage du tableau de points bleus...");
    for (int t = 0; t < WINDOW_WIDTH/sqrt(2); t+=2) {
        int x = WINDOW_WIDTH/(float)2 + t*cos(t*M_PI/180);
        int y = WINDOW_HEIGHT/(float)2 + t*sin(t*M_PI/180);

        if(x < WINDOW_WIDTH && y < WINDOW_HEIGHT) {
            if (blen == blue_capacity){
                log_trace("Reallocation du tableau...");
                blue_capacity = (blue_capacity == 0) ? 1 : blue_capacity*2;

                Point *hld = realloc(blue_points, sizeof(Point)*blue_capacity);
                if (hld == NULL) {
                    log_error("Erreur de reallocation du tableau");
                    freePoints();
                    exit(EXIT_FAILURE);
                }
                blue_points = hld;
            }            

            log_trace("Insertion de la valeur dans le tableau");
            blue_points[blen] = (Point){ .x = x, .y = y };
            blen++;
        }
    }
    log_info("Remplissage du tableau effectue avec succes!");

    //Spirale rouge
    log_info("Remplissage du tableau de points rouges...");    
    for (int t = 1; t < WINDOW_WIDTH/sqrt(2); t+=2) {
        int x = WINDOW_WIDTH/(float)2 - t*cos(t*M_PI/180);
        int y = WINDOW_HEIGHT/(float)2 - t*sin(t*M_PI/180);

        if(x < WINDOW_WIDTH && y < WINDOW_HEIGHT) {
            if (rlen == red_capacity){
                log_trace("Reallocation du tableau...");
                red_capacity = (red_capacity == 0) ? 1 : red_capacity*2;

                Point *hld = realloc(red_points, sizeof(Point)*red_capacity);
                if (hld == NULL) {
                    log_error("Erreur de reallocation du tableau");
                    freePoints();
                    exit(EXIT_FAILURE);
                }
                red_points = hld;
            }            

            log_trace("Insertion de la valeur dans le tableau");
            red_points[rlen] = (Point){ .x = x, .y = y };
            rlen++;
        }
    }
    log_trace("Shrinking the arrays to size");
    blue_points = realloc(blue_points, sizeof(Point)*blen);
    red_points = realloc(red_points, sizeof(Point)*rlen);
    log_info("Remplissage du tableau effectue avec succes!");

    log_info("Initialisation terminee!");
    is_init = true;
}

double distance(Point p1, Point p2) {
    return sqrt(pow(p2.x-p1.x, 2) + pow(p2.y-p1.y, 2));
}

int find_nearest(Point myPoint, Point *points, int len) {
    int closest = 0;

    for (int i = 1; i < len; i++) {
        if (distance(myPoint, points[closest]) == 0) {
            break;
        }

        if (distance(myPoint, points[closest]) > distance(myPoint, points[i])) {
            closest = i;
        }
    }

    return closest;
}

void determineColor(int px, int py, int *r_out, int *b_out) {
    if (!is_init) {
        log_error("Tableaux de points non-initialisees");
        exit(EXIT_FAILURE);
    }

    Point myPoint = { .x = px, .y = py };

    log_trace("Recherche des points bleu et rouges les plus proches");
    int nearest_blue = find_nearest(myPoint, blue_points, blen);
    int nearest_red = find_nearest(myPoint, red_points, rlen);


    log_trace("Calcul de la distance entre les deux points");
    double dist_blue = distance(myPoint, blue_points[nearest_blue]);
    double dist_red = distance(myPoint, red_points[nearest_red]);

    log_trace("Calcul des valeurs rgb actuels des couleurs");
    if (dist_blue == 0 && dist_red == 0) {
        log_error("Impossible d'avoir un points a la fois rouge et bleu");
        exit(EXIT_FAILURE);
    } 

    double total_distance = dist_blue + dist_red;
    *b_out = (total_distance-dist_blue)/total_distance * 255;
    *r_out = (total_distance-dist_red)/total_distance * 255;
}
