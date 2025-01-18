#ifndef PARSER_H
#define PARSER_H

#include "../neuralnet/layer.h"
#include "../neuralnet/model.h"

/*
 * NNF File description
 * 
 *  # number of layers in the model
 *      layer_n             
 * 
 *  # the next section describes how each layer is stored.
 *  # It is to be duplicated layer_n times.
 *
 *  # layer_s number of neurons in the layer.
 *  # layer_w width of the layer's weight matrix.
 *      layer_s, layer_w
 *   
 *  # weights
 *  # layer_s lines, of size layer_w.
 *  # comma separated float64 values. Spaces allowed and ignored.
 *      w[0][0]       ... w[0][layer_w]
 *      .        .                  .
 *      .              .            .
 *      w[layer_s][0] ... w[layer_s][layer_w]
 *
 *  # biases
 *  # one line of size layer_s.
 *  # comma separated float64 values. Spaces allowed and ignored .
 *      b[0] ... b[layer_s]
 *
 *  # Lines starting with # will be ignored.
 *
 */

int fromFile(const char *filepath, Model *model);
void saveToFile(Model model, const char *filepath);

#endif
