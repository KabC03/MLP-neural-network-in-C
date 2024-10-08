// MLP library - NOTE assumes floats

#ifndef MLP_H
#define MLP_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <limits.h>
#include "2DMatrix.h"
#include "vector.h"
#include "return codes.h"

typedef struct Network {

    Vector networkLayers; //Layer data (metadata) - note network output is stored in the last layers output matrix
    float networkError;   //Error of network

} Network;





bool MLP_randomise(Matrix *const matrix, float range, float min);
bool MLP_normalise(Matrix *const matrix, float value);
bool MLP_mean_square_error(Matrix *const matrix, Matrix *const expectedValues ,float *output);

bool MLP_ReLu(Matrix *const arg1, Matrix *const result);
bool MLP_ReLu_gradient(Matrix *const arg1, Matrix *const result);



RETURN_CODE MLP_initialise_network(Network *network, size_t numberOfLayers, size_t *neuronsPerLayer);
RETURN_CODE MLP_evaluate_input(Network *network, Vector *input);
RETURN_CODE MLP_print_output(Network *network);
RETURN_CODE MLP_print_layers(Network *network);
RETURN_CODE MLP_backpropagate(Network *network, Matrix *expectedOutput);

#endif // MLP_H



