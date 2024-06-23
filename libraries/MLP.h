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
#include "2Dmatrix.h"

bool MLP_randomise(Matrix *const matrix, float range, float min);
bool MLP_mean_square_error(Matrix *const matrix, float expectedValue ,float *output);

bool MLP_ReLu(Matrix *const arg1, Matrix *const result);
bool MLP_ReLu_gradient(Matrix *const arg1, Matrix *const result);

#endif // MLP_H



