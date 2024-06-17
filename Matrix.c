#include "matrix.h"

//Helper functions

//Check if a matrix is set up properly
bool valid_matrix(Matrix *const matrix) {
    if(matrix == NULL) {
        return false;
    } else if(matrix->data == NULL || matrix->dataSize == 0 || matrix->dimensionality == 0 || matrix->dimensions == NULL) {
        return false;
    } else {

    }
    return true;
}






//User functions


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
 * Return: T/F depending on if initialisation was succesful
 */
bool matrix_initialise(Matrix *const matrix, size_t dimensionality, size_t *dimensions, size_t dataSize, void *data) {

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










/**
 * matrix_print
 * ========================================
 * Brief: Print a matrix (used for debugging)
 * 
 * Param: matrix - Matrix of interest
 * Return: void
 */
void matrix_print(Matrix *const matrix) {

    if(valid_matrix(matrix) == false) {
        printf("Matrix not initialised\n");
        return;
    } else {
        //Use recursion
        


    }

    return;
}










































