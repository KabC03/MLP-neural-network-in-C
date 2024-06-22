// 2D matricies in C

#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>



typedef struct Matrix {

    size_t rows;
    size_t cols;

    uint8_t *data;
    size_t dataSize;

} Matrix;

bool matrix_2D_print(Matrix *const matrix);
bool matrix_2D_initialise(Matrix *const matrix, size_t rows, size_t cols, void *data, size_t dataSize);
bool matrix_2D_add(Matrix *const result, Matrix *const arg1, Matrix *const arg2);
bool matrix_2D_subtract(Matrix *const result, Matrix *const arg1, Matrix *const arg2);



#endif // MATRIX2D_H

