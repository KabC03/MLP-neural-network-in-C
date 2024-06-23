#include "MLP.h"
#define square(value) (value * value)

/**
 * MLP_randomise
 * ===============================================
 * Brief: Generates a random matrix
 * 
 * Param: *matrix - matrix of interest
 *        range - range from minimum
 *        min - min value in matrix
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool MLP_randomise(Matrix *const matrix, float range, float min) {

    if(matrix == NULL) {
        return false;
    } else if(matrix->data == NULL) {
        return false;
    } else {

        srand(time(NULL));
        for(size_t i = 0; i < (matrix->cols * matrix->rows); i++) {
            matrix->data[(matrix->dataSize) * i] = (min + (range * (float)rand())/RAND_MAX);
        }

    }
    return true;
}




/**
 * MLP_mean_square_error
 * ===============================================
 * Brief: Calculate the MSE of a matrix
 * 
 * Param: *matrix - matrix of interest
 *        expectedValue - expected value
 *        *output - output data pointer
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool MLP_mean_square_error(Matrix *const matrix, float expectedValue ,float *output) {

    if(matrix == NULL || output == NULL) {
        return false;
    } else if(matrix->data == NULL) {
        return false;
    } else {

        (*output) = 0;
        for(size_t i = 0; i < (matrix->rows * matrix->cols); i++) {

            (*output) += square(((matrix->data)[i * matrix->dataSize]) - expectedValue);
        }
        (*output) /= (matrix->rows * matrix->cols);

    }
    return true;
}

























