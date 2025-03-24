#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>

#include "codec/nnf.h"
#include "neuralnet/model.h"

#define COMMENT_CHAR #
#define MODEL_LAYER_N_STEP 0
#define LAYER_SIZE_STEP 1
#define LAYER_WEIGHTS_STEP 2

int countNonSpaceCharacters(char *src, int size) {
    int n = 0;
    int ind = 0;
    while(ind < size) {
        if(src[ind] != ' ') {
            n++;
        }
        ind++;
    }
    return n;
}
void trim(char *src, char **dest, int size) {
    int charcount = 0;
    int step = 0;
    int ind = 0;

    charcount = countNonSpaceCharacters(src, size);
    *dest = malloc(sizeof(char) * (charcount+1));

    while(ind < size) {
        if(src[ind] != ' ') {
            (*dest)[step] = src[ind];
            step++;
        }
        ind++;
    }
    (*dest)[charcount] = '\0';
}

bool isLineEmpty(const char *line) {
    while(*line != '\0') {
        if(*line != '\n' && *line != '\r') {
            return false;
        }
        line++;         
    }
    return true;
}


int parseLayerN(char *line) {
    int n;
    int ret;
    ret = sscanf(line, "%d", &n);
    return n;
}

int parseLayerSize(char *line, int *layer_s, int *layer_w) {
    int ret;
    ret = sscanf(line, "%d,%d", layer_s, layer_w);
    return ret;
}

int parseWeights(char *line, float **weights, int n, int w) {
    if(w == 0) {
        return -1;
    }
    float f = 0;
    int ind = 0;
    int ret;
    char *token;
    weights[n] = malloc(sizeof(float) * w);
    token = strtok(line, ",");
    while(token != NULL) {
        ret = sscanf(token, "%f", &f);
        if(ret < 0) {
            return -1;
        }
        weights[n][ind] = f;
        token = strtok(NULL, ",");
        ind++;
    }
    return 0;
}


int fromFile(const char *filepath, Model *model) {
    FILE *fp;
    char *line = NULL;
    char *trimmed = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int step = 0;
    int ret = 0;
    
    int n = 0;
    Layer prev;
    Layer curr;
    int curr_weight_line = 0;

    fp = fopen(filepath, "r");
    if(fp == NULL) {
        return -1;
    }

    Model md = malloc(sizeof(struct model));
    *model = md;

    md->input = NULL;
    prev = NULL;
    curr = NULL;

    while((read = getline(&line, &len, fp)) != -1) {
        trim(line, &trimmed, read);
        strcpy(line, trimmed);
        if(isLineEmpty(line)) {
            free(trimmed);
            continue;
        }
        if(line[0] == '#') {
            free(trimmed);
            continue;
        }

        switch (step) {
            case MODEL_LAYER_N_STEP:
                n = parseLayerN(line);
                if(n < 0) {
                    ret = -1;
                }
                md->layer_n = n;
                step=LAYER_SIZE_STEP;
                break;
            case LAYER_SIZE_STEP:
                prev = curr;
                curr = malloc(sizeof(struct layer));
                if(prev != NULL) {
                    prev->next = curr;
                }
                curr->previous = prev;
                curr->next = NULL;
                if(md->input == NULL) {
                    md->input = curr;
                }
                curr_weight_line = 0;
                ret = parseLayerSize(line, &curr->n, &curr->w);
                if(ret < 0) {
                    break;
                }
                curr->neurons = malloc(sizeof(float) * curr->n);
                curr->weight = malloc(sizeof(float*) * curr->n);
                step=LAYER_WEIGHTS_STEP;
                break;
            case LAYER_WEIGHTS_STEP:
                ret = parseWeights(line, curr->weight, curr_weight_line, curr->w);
                if(ret < 0) {
                    break;
                }
                curr_weight_line++;
                if(curr_weight_line == curr->n) {
                    step=LAYER_SIZE_STEP;
                }
                break;
        }
        free(trimmed);

        if(ret < 0) {
            freeModel(md);
            *model = NULL;
            fclose(fp);
            if(line) {
                free(line);
            }
            return -1; 
        }
    }


    Layer last = malloc(sizeof(struct layer));
    last->n = curr->w;
    last->w = 0;
    last->neurons = malloc(sizeof(float) * last->n);
    last->weight = NULL;
    last->previous = curr;
    last->next = NULL;
    curr->next = last;

    fclose(fp);
    if(line) {
        free(line);
    }
    return 0;
}
