#include "draw/draw.h"
#include "config/config.h"
#include "neuralnet/model.h"
#include "neuralnet/forwardpass.h"
#include "codec/nnf.h"
#include "log.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool display_init = false;

/*-------------------------------------------------------------*
 *        DRAW FUNCTIONS                                       *
 *-------------------------------------------------------------*/

void drawModelResults(Model model) {
    if (!display_init) {
        log_fatal("Window et renderer non initialisees");
        exit(EXIT_FAILURE);
    }

    log_trace("Initialising input array");
    float *inputs = malloc(sizeof(float)*2);

    if (inputs == NULL) {
        log_fatal("Erreur d'allocation");
        exit(EXIT_FAILURE);
    }
    
    float xMax = WINDOW_WIDTH;
    float yMax = WINDOW_HEIGHT;
    for (int i = 0; i < WINDOW_WIDTH; i++) {
        for (int j = 0; j < WINDOW_HEIGHT; j++) {
            inputs[0] = (float)i / xMax;
            inputs[1] = (float)j / yMax;

            log_trace("Starting forward pass");
            float *res = forwardPass(model, inputs);
            int r = (int)(res[0]*255);
            int b = (int)(res[1]*255);
            // Determining whether spiralSuite or circleSuite is used. NOTE: there are much better ways to do this
            int g = (lastLayer(model)->n == 3) ? (g = (int)(res[2]*255)) : (g = 0);
            
            log_trace("Drawing point (%d, %d)...", i, j);
            SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(renderer, i, j);
        }
    }

    SDL_RenderPresent(renderer);

    log_trace("Freeing resources");
    free(inputs);
}

// function for drawing larger isolated points
void drawBiggerPoint(Point pt) {
    SDL_RenderDrawPoint(renderer, pt.x, pt.y);
    SDL_RenderDrawPoint(renderer, pt.x, pt.y+1);
    SDL_RenderDrawPoint(renderer, pt.x+1, pt.y);
    SDL_RenderDrawPoint(renderer, pt.x+1, pt.y+1);
}

void drawSpiral() {

    for (int t = 0; t < WINDOW_WIDTH/sqrt(2); t+=2) {
        int x = WINDOW_WIDTH/(float)2 + t*cos(t*M_PI/180);
        int y = WINDOW_HEIGHT/(float)2 + t*sin(t*M_PI/180);
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); // Bleu
        drawBiggerPoint((Point){ .x = x, .y = y });
    }

    for (int t = 1; t < WINDOW_WIDTH/sqrt(2); t+=2) {
        int x = WINDOW_WIDTH/(float)2 - t*cos(t*M_PI/180);
        int y = WINDOW_HEIGHT/(float)2 - t*sin(t*M_PI/180);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Rouge
        drawBiggerPoint((Point){ .x = x, .y = y });
    }

    SDL_RenderPresent(renderer);
}

void drawSpiralFull() {
    if (!display_init) {
        log_fatal("Window et renderer non initialisees");
        exit(EXIT_FAILURE);
    }

    log_trace("Initialising spiral values");
    initSpiralPoints();

    log_trace("Calculating point values");
    int r = 0, b = 0;
    for (int i = 0; i < WINDOW_WIDTH; i++) {
        for (int j = 0; j < WINDOW_HEIGHT; j++) {
            determineColor(i, j, &r, &b);
            
            SDL_SetRenderDrawColor(renderer, r, 0, b, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(renderer, i, j);
        }
    }

    log_trace("Presenting and freeing");
    SDL_RenderPresent(renderer);
    freePoints();
}

void drawCircles() {
    if (!display_init) {
        log_fatal("Window et renderer non initialisees");
        exit(EXIT_FAILURE);
    }

    log_trace("Initialising circle arrays");
    initCirclePoints();
    Point *red_points = getRedPoints();
    Point *blue_points = getBluePoints();
    Point *green_points = getGreenPoints();

    log_trace("Displaying red points");
    for (int i = 0; i < getRlen(); i++) {
        Point curr = red_points[i];
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        drawBiggerPoint(curr);
        // Displaying 4 points for better visibility
    }

    log_trace("Displaying blue points");
    for (int i = 0; i < getRlen(); i++) {
        Point curr = blue_points[i];
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
        drawBiggerPoint(curr);
    }

    log_trace("Displaying green points");
    for (int i = 0; i < getGlen(); i++) {
        Point curr = green_points[i];
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        drawBiggerPoint(curr);
    }


    log_trace("Presenting and freeing");
    SDL_RenderPresent(renderer);
    freePoints();
}

/*------------------------------------------------------------------------*
 *          DISPLAY INITIALISATION AND CLEARING                           *
 *------------------------------------------------------------------------*/

int displaySetup() {
    if (display_init) {
        log_error("Display already initialised");
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        log_fatal("Erreur SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Coloration par Distance",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_RESIZABLE);
    if (!window) {
        log_fatal("Erreur SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        log_fatal("Erreur SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    display_init = true;

    return 0;
}

int displayClear() {
    // A brief delay
    SDL_Delay(5000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    display_init = false;

    return 0;
}

bool display_isInit() {
    return display_init;
}

/*--------------------------------------------------------------------------------*
 *          DISPLAY SHOWING OPTIONS                                               *
 *--------------------------------------------------------------------------------*/

int displaySpiral() {
    displaySetup();
    drawSpiral();
    displayClear();
    
    return 0;
}

int displayCircle() {
    displaySetup();
    drawCircles();
    displayClear();

    return 0;
}

int displayModel(const char *filename) {
    displaySetup();
    
    Model model;
    fromFile(filename, &model);
    drawModelResults(model);
    freeModel(model);
    
    displayClear();

    return 0;
}