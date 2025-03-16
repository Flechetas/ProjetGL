#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "config/config.h"
#include "draw/draw.h"
#include "log.h"

Point *red_points;
Point *blue_points;
bool is_init;

// frees the 2 color arrays (to be called at the end of main)
void freeSpirals() {
    free(red_points);
    free(blue_points);
    is_init = false;
}

bool isInit() {
    return is_init;
} 

void drawSpiral(SDL_Renderer *renderer) {

    for (int t = 0; t < WINDOW_WIDTH/sqrt(2); t+=2) {
        int x = WINDOW_WIDTH/2 + t*cos(t*M_PI/180);
        int y = WINDOW_HEIGHT/2 + t*sin(t*M_PI/180);
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); // Bleu
        SDL_RenderDrawPoint(renderer, x, y);
    }

    for (int t = 1; t < WINDOW_WIDTH/sqrt(2); t+=2) {
        int x = WINDOW_WIDTH/2 - t*cos(t*M_PI/180);
        int y = WINDOW_HEIGHT/2 - t*sin(t*M_PI/180);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Rouge
        SDL_RenderDrawPoint(renderer, x, y);
    }

    SDL_RenderPresent(renderer);
}

// an auxiliary function for qsort, which has to be written with this format
int compare_points(const void *a, const void *b) {
    const Point *p1 = (const Point*) a;
    const Point *p2 = (const Point*) b;

    if (p1->x != p2->x) {
        return p1->x - p2->x;
    }
    return p1->y - p2->y;
}

void initSpiralValues() {
    log_info("Initialisation des tableaux de points des spirales...");
    
    log_info("Allocation des tableaux...");
    red_points = malloc(sizeof(Point));
    blue_points = malloc(sizeof(Point));
    int curr_index_b = 0;
    int curr_index_r = 0;

    if (red_points == NULL || blue_points == NULL) {
        log_error("Echec d'allocation de tableau");
        exit(EXIT_FAILURE);
    }
    log_info("Allocation effectuee avec succes!");

    // Spirale bleue
    log_info("Remplissage du tableau de points bleus...");
    for (int t = 0; t < WINDOW_WIDTH/sqrt(2); t+=2) {
        int x = WINDOW_WIDTH/2 + t*cos(t*M_PI/180);
        int y = WINDOW_HEIGHT/2 + t*sin(t*M_PI/180);

        if(x < WINDOW_WIDTH && y < WINDOW_HEIGHT) {
            log_trace("Reallocation du tableau...");
            blue_points = realloc(blue_points, sizeof(Point)*curr_index_b+1);

            log_trace("Insertion de la valeur dans le tableau");
            Point tmp = { .x = x, .y = y };
            blue_points[curr_index_b] = tmp;
            curr_index_b++;
        }
    }
    log_info("Remplissage du tableau effectue avec succes!");

    //Spirale rouge
    log_info("Remplissage du tableau de points bleus...");    
    for (int t = 1; t < WINDOW_WIDTH/sqrt(2); t+=2) {
        int x = WINDOW_WIDTH/2 - t*cos(t*M_PI/180);
        int y = WINDOW_HEIGHT/2 - t*sin(t*M_PI/180);

        if(x < WINDOW_WIDTH && y < WINDOW_HEIGHT) {
            log_trace("Reallocation du tableau...");
            red_points = realloc(red_points, sizeof(Point)*curr_index_r+1);

            log_trace("Insertion de la valeur dans le tableau");
            Point tmp = { .x = x, .y = y };
            red_points[curr_index_r] = tmp;
            curr_index_r++;
        }
    }
    log_info("Remplissage du tableau effectue avec succes!");

    log_info("Triage des tableaux");
    qsort(blue_points, curr_index_b+1, sizeof(Point), compare_points);
    qsort(red_points, curr_index_r+1, sizeof(Point), compare_points);

    log_info("Initialisation terminee!");
    is_init = true;
}

int find_nearest(Point myPoint, Point *points) {
    int len = sizeof(points) / sizeof(Point);
    int start_index = 0;
    int end_index = len-1;
    
    int curr;
    int closest = start_index; // just some point in the array
    bool thend = false;
    
    while (!thend) {
        // checking whether we're at the end
        if (start_index == end_index) {
            thend = true;
        }

        // comparing with curr
        curr = (start_index+end_index)/2;
        if (compare_points(&myPoint, &points[curr]) == 0) {
            closest = curr;
            break;
        }
        else if (compare_points(&myPoint, &points[curr]) < 0) {
            end_index = curr-1;
        }
        else{
            start_index = curr+1;
        }

        // checking which is closest
        if (abs(compare_points(&myPoint, &points[closest])) > abs(compare_points(&myPoint, &points[curr])))
            closest = curr;
    }

    return closest;
}

double distance(Point p1, Point p2) {
    return sqrt(pow(p2.x-p1.x, 2) + pow(p2.y-p1.y, 2));
}

void determineColor(int px, int py, int *r_out, int *b_out) {
    Point myPoint = { .x = px, .y = py };

    log_trace("Recherche des points bleu et rouges les plus proches");
    int nearest_blue = find_nearest(myPoint, blue_points);
    int nearest_red = find_nearest(myPoint, red_points);

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

void generateColorFile(const char *outputFile) {
    FILE *file = fopen(outputFile, "w");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier de sortie.");
        return;
    }

    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            int r, b;
            determineColor(x, y, &r, &b);
            fprintf(file, "%d %d %d %d %d\n", x, y, r, 0, b); // RGB avec G = 0
        }
    }

    fclose(file);
    printf("Fichier %s généré avec succès !\n", outputFile);
}


void drawColoredPoints(SDL_Renderer *renderer, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier.");
        return;
    }

    int x, y, r, g, b;
    while (fscanf(file, "%d %d %d %d %d", &x, &y, &r, &g, &b) == 5) {
        SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawPoint(renderer, x, y);
    }

    fclose(file);
    SDL_RenderPresent(renderer);
}
