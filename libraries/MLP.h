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

    Matrix inputLayer;   //Matrix of output layer OUTPUT
    Vector hiddenLayers; //Hidden layer data (metadata)
    Matrix outputLayer;  //Vector of output layer OUTPUT

} Network;





bool MLP_randomise(Matrix *const matrix, float range, float min);
bool MLP_mean_square_error(Matrix *const matrix, float expectedValue ,float *output);

bool MLP_ReLu(Matrix *const arg1, Matrix *const result);
bool MLP_ReLu_gradient(Matrix *const arg1, Matrix *const result);



RETURN_CODE MLP_initialise_network(Network *network, size_t numberOfInputNeurons, size_t numberOfHiddenLayers, size_t *hiddenNeuronsPerLayer, size_t numberOfOutputNeurons);

#endif // MLP_H



