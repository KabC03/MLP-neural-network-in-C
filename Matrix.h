#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>



typedef struct Matrix {

    size_t dimensionality;    //Number of dimensions in the matrix (basically the length of dimensions)
    size_t *dimensions;       //Array of dimensions (e.g [3,2,1] -> 3x2x1 3D matrix)

    size_t dataSize;          //Size of the data in the matrix
    uint8_t *data;            //Array of the data (uint8_t so can hold any data)

} Matrix;







#endif // MATRIX_H



