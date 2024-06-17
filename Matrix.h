#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>



typedef struct Matrix {

    size_t dimensionality;    //Number of dimensions in the matrix (basically the length of dimensions)
    size_t *dimensions;       //Array of dimensions (e.g [3,2,1] -> 3x2x1 3D matrix) (rows x cols x depth x ...)

    size_t dataSize;          //Size of the data in the matrix
    uint8_t *data;            //Array of the data (uint8_t so can hold any data)

} Matrix;


bool matrix_initialise(Matrix *const matrix, size_t dimensionality, size_t *dimensions, size_t dataSize, void *data);
void matrix_print(Matrix *const matrix);



#endif // MATRIX_H



