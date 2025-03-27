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

            log_trace("Drawing point (%d, %d)...", i, j);
            SDL_SetRenderDrawColor(renderer, (int)(res[0]*255), 0, (int)(res[1]*255), SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(renderer, i, j);
        }
    }

    SDL_RenderPresent(renderer);

    log_trace("Freeing resources");
    free(inputs);
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

void drawSpiral() {

    for (int t = 0; t < WINDOW_WIDTH/sqrt(2); t+=2) {
        int x = WINDOW_WIDTH/(float)2 + t*cos(t*M_PI/180);
        int y = WINDOW_HEIGHT/(float)2 + t*sin(t*M_PI/180);
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); // Bleu
        SDL_RenderDrawPoint(renderer, x, y);
    }

    for (int t = 1; t < WINDOW_WIDTH/sqrt(2); t+=2) {
        int x = WINDOW_WIDTH/(float)2 - t*cos(t*M_PI/180);
        int y = WINDOW_HEIGHT/(float)2 - t*sin(t*M_PI/180);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Rouge
        SDL_RenderDrawPoint(renderer, x, y);
    }

    SDL_RenderPresent(renderer);
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

int displayModel(const char *filename) {
    displaySetup();
    
    Model model;
    fromFile(filename, &model);
    drawModelResults(model);
    freeModel(model);
    
    displayClear();

    return 0;
}