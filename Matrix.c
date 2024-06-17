#include "matrix.h"


/**
 * matrix_initialise
 * ========================================
 * Brief: Initialises a matrix and sets it to an initial value
 * 
 * Param: matrix - Matrix of interest
 *      dimensionality - Number of dimensions
 *      dimensions - Array of dimensions (e.g [3,2,1] -> 3x2x1 matrix)
 *      dataSize - Size of the data in the matrix (e.g sizeof(int))
 *      *data - Flat array of data to be copied to matrix
 */
bool matrix_initialise(Matrix *const matrix, size_t dimensionality, size_t *dimensions, size_t dataSize, uint8_t *data) {

    if(dimensions == NULL || data == NULL || dimensionality == 0 || dataSize == 0) {
        return false;
    } else {
        matrix->dimensionality = dimensionality;
        matrix->dataSize = dataSize;


        matrix->dimensions = malloc(sizeof(size_t) * dimensionality);
        if(matrix->dimensions == NULL) {
            return false;
        }
        memcpy(matrix->dimensions, dimensions, dimensionality * sizeof(size_t));


        //Calculate numel - probably not optimal since it can be passed but eh
        size_t numel = 1;
        for(int i = 0; i < dimensionality; i++) {
            numel *= dimensions[i];
        }
        matrix->data = malloc(dataSize * numel);
        if(matrix->data == NULL) {
            free(matrix->dimensions);
            return false;
        }
        memcpy(matrix->data, data, numel * dataSize);
    }

    return true;
}























