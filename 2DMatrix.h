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

} Matrix;






#endif // MATRIX2D_H


