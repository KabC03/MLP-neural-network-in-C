// Basic generic matrix algorithms for the network

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
bool matrix_2D_initialise(Matrix *const matrix, size_t rows, size_t cols, size_t dataSize);
bool matrix_2D_set(Matrix *const matrix, size_t rows, size_t cols, void *data, size_t dataSize);
void matrix_2D_add_float_component(float *result, float *arg1, float *arg2);
bool matrix_2D_add(Matrix *const result, Matrix *const arg1, Matrix *const arg2, void (*componentArithmatic)(float*, float*, float*));
void matrix_2D_subtract_float_component(float *result, float *arg1, float *arg2);
bool matrix_2D_subtract(Matrix *const result, Matrix *const arg1, Matrix *const arg2, void (*componentArithmatic)(float*, float*, float*));
void matrix_2D_multiply_float_component(float *result, float *arg1, float *arg2);
bool matrix_2D_multiply(Matrix *const result, Matrix *const arg1, Matrix *const arg2, void (*componentArithmatic)(float*, float*, float*));
bool matrix_2D_transpose(Matrix *const result, Matrix *const arg1);
bool matrix_2D_free(Matrix *matrix);

#endif // MATRIX2D_H
