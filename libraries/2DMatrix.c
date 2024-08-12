#include "2DMatrix.h"




/**
 * matrix_2D_print
 * ===============================================
 * Brief: Print a 2D matrix of floats (used for debugging)
 * 
 * Param: *matrix - matrix of interest
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool matrix_2D_print(Matrix *const matrix) {

    if(matrix == NULL) {
        return false;
    } else {

        for(size_t i = 0; i < matrix->rows; i++) {
            for(size_t j = 0; j < matrix->cols; j++) {

                printf("%f ", (float)((matrix->data)[(matrix->dataSize) * ((i * matrix->cols) + j)]));
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
 *        dataSize - sizeof(element) in bytes
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool matrix_2D_initialise(Matrix *const matrix, size_t rows, size_t cols, size_t dataSize) {

    if(matrix == NULL || rows == 0 || cols == 0 || dataSize == 0) {
        return false;
    } else {

        matrix->cols = cols;
        matrix->rows = rows;
        matrix->dataSize = dataSize;

        matrix->data = malloc(dataSize * rows * cols);
        if(matrix->data == NULL) {
            return false;
        }
    }

    return true;
}













/**
 * matrix_2D_set
 * ===============================================
 * Brief: Set or resize a 2D matrix
 * 
 * Param: *matrix - matrix of interest
 *        rows - rows of the matrix
 *        cols - columns of the matrix
 *        *data - data to put into the matrix
 *        dataSize - sizeof(element) in bytes
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool matrix_2D_set(Matrix *const matrix, size_t rows, size_t cols, void *data, size_t dataSize) {

    if(matrix == NULL || rows == 0 || cols == 0 || data == NULL || dataSize == 0) {
        return false;
    } else {

        matrix->cols = cols;
        matrix->rows = rows;
        matrix->dataSize = dataSize;


        matrix->data = realloc(matrix->data, dataSize * rows * cols);
        if(matrix->data == NULL) {
            return false;
        }
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
    || result->rows != arg1->rows
    || result->dataSize != arg1->dataSize
    || arg1->dataSize != arg2->dataSize
    ) { //Incompatable dimensions
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
    || result->rows != arg1->rows
    || result->dataSize != arg1->dataSize
    || arg1->dataSize != arg2->dataSize
    ) { //Incompatable dimensions
        return false;
    } else {

        for(size_t i = 0; i < (result->rows) * (result->cols); i++) {

            (result->data)[i * result->dataSize] = (arg1->data)[i * arg1->dataSize] - (arg2->data)[i * arg2->dataSize];
        }

    }

    return true;
}






/**
 * matrix_2D_multiply
 * ===============================================
 * Brief: Multiply two matricies
 * 
 * Param: *result - Result matrix
 *        *arg1 - arg1 matrix
 *        *arg2 - arg2 matrix
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool matrix_2D_multiply(Matrix *const result, Matrix *const arg1, Matrix *const arg2) {

    if(result == NULL || arg1 == NULL || arg2 == NULL) {
        return false;


    } else if(arg1->cols != arg2->rows 
    || result->rows != arg1->rows 
    || result->cols != arg2->cols
    || arg1->dataSize != arg2->dataSize
    || arg1->dataSize != result->dataSize) { //Incompatable dimensions

        //printf("arg1: %zu, arg2: %zu, result: %zu\n", arg1->dataSize, arg2->dataSize, result->dataSize);
        //printf("arg1: rows: %zu, cols: %zu, arg2: rows: %zu, cols: %zu\n",arg1->rows, arg1->cols, arg2->rows, arg2->cols);
        //printf("output: rows: %zu, cols: %zu\n",result->rows, result->cols);
        return false;

    } else {


        
        for(size_t i = 0; i < arg1->rows; i++) {
            for(size_t j = 0; j < arg2->cols; j++) {

                (result->data)[(result->dataSize) * (i * result->cols + j)] = 0; 
                //Zero before doing the sum - prevents needed additional sum temp variable
                for(size_t k = 0; k < arg1->cols; k++) {

                    (result->data)[(result->dataSize) * ((i * result->cols + j))] += 
                    (arg1->data)[(arg1->dataSize) * (k + (arg1->cols * i))] * 
                    (arg2->data)[(arg2->dataSize) * (j + (arg2->cols * k))];

                }
            }
        }
    }

    return true;
}




/**
 * matrix_2D_transpose
 * ===============================================
 * Brief: Transpose a matrix
 * 
 * Param: *result - Result matrix
 *        *arg1 - arg1 matrix
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool matrix_2D_transpose(Matrix *const result, Matrix *const arg1) {

    if(result == NULL || arg1 == NULL) {
        return false;
    } else if(result->cols != arg1->rows || result->rows != arg1->cols) {
        return false;
    } else {

        for(size_t i = 0; i < arg1->rows; i++) {
            for(size_t j = 0; j < arg1->cols; j++) {

                (result->data)[(result->dataSize) * ((result->cols * j) + i)] = 
                (arg1->data)[(arg1->dataSize) * ((arg1->cols * i) + j)];
            }
        }
    }
    return true;
}



/**
 * matrix_2D_free
 * ===============================================
 * Brief: Free a matrix
 * 
 * Param: *matrix - Matrix of interest
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool matrix_2D_free(Matrix *matrix) {

    if(matrix == NULL) {
        return false; 
    } else if(matrix->data == NULL) {
        return false;
    } else {
        matrix->cols = 0;
        matrix->rows = 0;
        matrix->dataSize = 0;
        free(matrix->data);
    }
    return true;
}









//Dot product, ReLU + Derivative, Sigmoid + Derivative, MSE












