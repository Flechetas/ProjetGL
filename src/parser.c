#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>
#include "../include/network.h"


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

        //res = realloc(res, sizeof(char) * (newlen+1));
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
