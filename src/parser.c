#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>
#include "../include/network.h"

#define COMMENT_CHAR #
#define MODEL_LAYER_N_STEP 0
#define LAYER_SIZE_STEP 1
#define LAYER_WEIGHTS_STEP 2
#define LAYER_BIAS_STEP 3


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
    assert(ret != -1);
    return n;
}

void parseLayerSize(char *line, int *layer_s, int *layer_w) {
    int ret;
    ret = sscanf(line, "%d,%d", layer_s, layer_w);
    assert(ret != -1);
}

void parseWeights(char *line, float **weights, int n, int w) {
    float f = 0;
    int ind = 0;
    char *token;
    weights[n] = malloc(sizeof(float) * w);
    token = strtok(line, ",");
    while(token != NULL) {
        sscanf(token, "%f", &f);
        weights[n][ind] = f;
        token = strtok(NULL, ",");
        ind++;
    }
}

void parseBiases(char *line, float *biases, int n) {
    float f = 0;
    int ind = 0;
    char *token;
    token = strtok(line, ",");
    while(token != NULL) {
        sscanf(token, "%f", &f);
        biases[ind] = f;
        token = strtok(NULL, ",");
        ind++;
    }
}


Model fromFile(const char *filepath) {
         
    Model model;
    FILE *fp;
    char *line = NULL;
    char *trimmed = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int step = 0;
    
    int n = 0;
    Layer prev;
    Layer curr;
    int curr_weight_line = 0;

    fp = fopen(filepath, "r");
    if(fp == NULL) {
        return NULL;
    }

    model = malloc(sizeof(struct model));
    model->input = NULL;
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
                model->layer_n = n;
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
                if(model->input == NULL) {
                    model->input = curr;
                }
                curr_weight_line = 0;
                parseLayerSize(line, &curr->n, &curr->w);
                curr->neurons = malloc(sizeof(float) * curr->n);
                curr->weight = malloc(sizeof(float*) * curr->n);
                curr->bias = malloc(sizeof(float) * curr->n);
                step=LAYER_WEIGHTS_STEP;
                break;
            case LAYER_WEIGHTS_STEP:
                parseWeights(line, curr->weight, curr_weight_line, curr->w);
                curr_weight_line++;
                if(curr_weight_line == curr->n) {
                    step=LAYER_BIAS_STEP;
                }
                break;
            case LAYER_BIAS_STEP:
                parseBiases(line, curr->bias, curr->n);
                step=LAYER_SIZE_STEP;
                break;
        }
        free(trimmed);
    }

    Layer last = malloc(sizeof(struct layer));
    last->n = curr->w;
    last->w = 0;
    last->neurons = malloc(sizeof(float) * last->n);
    last->weight = NULL;
    last->bias = NULL;
    last->previous = curr;
    last->next = NULL;
    curr->next = last;

    fclose(fp);
    if(line) {
        free(line);
    }
    return model;
}


int saveHeaderToFile(FILE *fp) {
    char *line = "# NNF File\n\n";
    int ret = fwrite(line, sizeof(char), strlen(line), fp);
    return ret;
}
int saveLayerNToFile(int n, FILE *fp) {
    char *res;
    char *fmt = "# Number of layers\n%d\n\n";
    int len = snprintf(NULL, 0, fmt, n);
    if(len < 0) {
        return len;
    }
    res = malloc(sizeof(char) * (len+1));
    len = sprintf(res, fmt, n);
    if(len < 0) {
        return len;
    }
    len = fwrite(res, sizeof(char), len, fp); 
    free(res);
    return len;
}
int saveLayerHeaderToFile(int layer_s, int layer_w, FILE *fp) {
    char *res;
    char *fmt = "# layer_s number of neurons in the layer.\n# layer_w width of the layer's weight matrix.\n%d, %d\n\n";
    int len = snprintf(NULL, 0, fmt, layer_s, layer_w);
    if(len < 0) {
        return len;
    }
    res = malloc(sizeof(char) * (len+1));
    len = sprintf(res, fmt, layer_s, layer_w);
    if(len < 0) {
        return len;
    }
    len = fwrite(res, sizeof(char), len, fp); 
    free(res);
    return len;
}
int saveWeightsToFile(float *weights, int len, FILE *fp) {
    char *fmt = "%s%f, ";
    char *res = malloc(sizeof(char));
    res[0] = '\0';
    int reslen;
    
    for(int i = 0 ; i < len ; i++) {
        int newlen = snprintf(NULL, 0, fmt, res, weights[i]);

        char *newres = malloc(sizeof(char) * (newlen+1));
        int len = sprintf(newres, fmt, res, weights[i]);
        assert(len != -1);
        free(res);
        res = newres;
        reslen = newlen;
    }

    len = fwrite(res, sizeof(char), reslen-2, fp);
    assert(len != -1);
    len = fwrite("\n", sizeof(char), 1, fp);
    free(res);
    return len;
}
int saveBiasesToFile(float *biases, int len, FILE *fp) {
    char *fmt = "%s%f, ";
    char *res = malloc(sizeof(char));
    res[0] = '\0';
    int reslen;

    for(int i = 0 ; i < len ; i++) {
        int newlen = snprintf(NULL, 0, fmt, res, biases[i]);
        char *newres = malloc(sizeof(char) * (newlen+1));
        int len = sprintf(newres, fmt, res, biases[i]);
        assert(len != -1);
        free(res);
        res = newres;
        reslen = newlen;
    }

    len = fwrite(res, sizeof(char), reslen-2, fp);
    assert(len != -1);
    len = fwrite("\n\n", sizeof(char), 2, fp);
    free(res);
    return len;
}
int saveLayerToFile(Layer layer, FILE *fp) {
    int ret;
    float *weights;
    float *biases;

    int layer_s = layer->n;
    int layer_w = layer->w;
    ret = saveLayerHeaderToFile(layer_s, layer_w, fp);
    assert(ret != -1);
    
    ret = fwrite("# Weights\n", sizeof(char), 10, fp);
    assert(ret != -1);
    for(int i = 0 ; i < layer_s ; i++) {
        weights = layer->weight[i];     
        ret = saveWeightsToFile(weights, layer_w, fp);
        assert(ret != -1);
    }
    
    ret = fwrite("\n", sizeof(char), 1, fp);
    assert(ret != -1);
    
    ret = fwrite("# Biases\n", sizeof(char), 9, fp);
    assert(ret != -1);
    biases = layer->bias;
    ret = saveBiasesToFile(biases, layer_s, fp); 
    assert(ret != -1);

    return 0;
}
int saveToFile(Model model, const char *filepath) {
    FILE *fp;

    fp = fopen(filepath, "w");
    if(fp == NULL) {
        return -1; 
    }

    int ret;
    int layer_n;

    ret = saveHeaderToFile(fp);
    assert(ret != -1);
    
    layer_n = countLayers(model);
    ret = saveLayerNToFile(layer_n, fp); 
    assert(ret != -1);

    Layer layer = model->input;
    while(layer != NULL) {
        if(layer->next == NULL) {
            break; 
        }
        ret = saveLayerToFile(layer, fp);
        assert(ret != -1);
        layer = layer->next;
    }

    fclose(fp);
    return 0;
}
