#include "matrix.h"




/**
 * matrix_2D_print
 * ===============================================
 * Brief: Print a 2D matrix of integers (used for debugging)
 * 
 * Param: *matrix - matrix of interest
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool matrix_2D_print(Matrix *const matrix) {

    if(matrix == NULL) {
        return false;
    } else {

        for(size_t i = 0; i < matrix->cols; i++) {
            for(size_t j = 0; j < matrix->cols; j++) {

                printf("%d ", (matrix->data)[(matrix->dataSize) * ((i * matrix->cols) + j)]);
            }
            printf("\n");
        }
    }

    return true;
}



/**
 * matrix_2D_initialise
 * ===============================================
 * Brief: Initialise a 2D matrix
 * 
 * Param: *matrix - matrix of interest
 *        rows - rows of the matrix
 *        cols - columns of the matrix
 *        *data - data to put into the matrix
 *        dataSize - sizeof(element) in bytes
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool matrix_2D_initialise(Matrix *const matrix, size_t rows, size_t cols, void *data, size_t dataSize) {

    if(matrix == NULL || rows == 0 || cols == 0 || data == NULL || dataSize == 0) {
        return false;
    } else {

        matrix->cols = cols;
        matrix->rows = rows;
        matrix->dataSize = dataSize;

        matrix->data = malloc(dataSize * rows * cols);
        memcpy(matrix->data, data, dataSize * rows * cols);
    }

    return true;
}



/**
 * matrix_2D_add
 * ===============================================
 * Brief: Add two matricies
 * 
 * Param: *result - Result matrix
 *        *arg1 - arg1 matrix
 *        *arg2 - arg2 matrix
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool matrix_2D_add(Matrix *const result, Matrix *const arg1, Matrix *const arg2) {

    if(result == NULL || arg1 == NULL || arg2 == NULL) {
        return false;


    } else if(arg1->cols != arg2->cols 
    || arg1->rows != arg2->rows 
    || result->cols != arg1->cols 
    || result->rows != arg1->rows) { //Incompatable dimensions
        return false;
    } else {

        for(size_t i = 0; i < (result->rows) * (result->cols); i++) {

            (result->data)[i * result->dataSize] = (arg1->data)[i * arg1->dataSize] + (arg2->data)[i * arg2->dataSize];
        }

    }

    return true;
}



/**
 * matrix_2D_subtract
 * ===============================================
 * Brief: Subtract two matricies
 * 
 * Param: *result - Result matrix
 *        *arg1 - arg1 matrix
 *        *arg2 - arg2 matrix
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool matrix_2D_subtract(Matrix *const result, Matrix *const arg1, Matrix *const arg2) {

    if(result == NULL || arg1 == NULL || arg2 == NULL) {
        return false;


    } else if(arg1->cols != arg2->cols 
    || arg1->rows != arg2->rows 
    || result->cols != arg1->cols 
    || result->rows != arg1->rows) { //Incompatable dimensions
        return false;
    } else {

        for(size_t i = 0; i < (result->rows) * (result->cols); i++) {

            (result->data)[i * result->dataSize] = (arg1->data)[i * arg1->dataSize] - (arg2->data)[i * arg2->dataSize];
        }

    }

    return true;
}


















