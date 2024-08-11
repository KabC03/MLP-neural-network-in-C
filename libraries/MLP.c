#include "MLP.h"
#define MLP_RAND_RANGE 0.1
#define MLP_RAND_MIN 0.001
#define square(value) (value * value)
#define HERE printf("HERE\n");


//Data for the hidden layer
typedef struct NetworkLayer {

    Matrix weight;              //Weight for each neuron
    Matrix bias;                //Bias
    Matrix preActivationOutput; //Store preactivation output for back propagation
    Matrix output;              //Output of the layer (after activation, bias, etc)

} NetworkLayer;


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




//Activation functions



/**
 * MLP_ReLu
 * ===============================================
 * Brief: Calculates ReLu on a matrix
 * 
 * Param: *result - Output matrix with ReLu values
 *        *arg1 - matrix to calculate ReLu on
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool MLP_ReLu(Matrix *const arg1, Matrix *const result) {

    if(result == NULL || arg1 == NULL) {
        return false;
    } else if(result->data == NULL 
    || arg1->data == NULL 
    || arg1->cols != result->cols 
    || arg1->rows != result->rows 
    || arg1->dataSize != result->dataSize) {
        return false;
    } else {

        for(size_t i = 0; i < (arg1->cols * arg1->rows); i++) {

            if(*(float*)(&((arg1->data)[(result->dataSize) * i])) < 0) {
                *(float*)(&((result->data)[(result->dataSize) * i])) = 0;
            } else {
                *(float*)(&((result->data)[(result->dataSize) * i])) = *(float*)(&((arg1->data)[(arg1->dataSize) * i]));
            }
        }

    }
    return true;
}






/**
 * MLP_ReLu_gradient
 * ===============================================
 * Brief: Calculates ReLu grqadient on a matrix
 * 
 * Param: *result - Output matrix with ReLu values
 *        *arg1 - matrix to calculate ReLu gradient on
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool MLP_ReLu_gradient(Matrix *const arg1, Matrix *const result) {

    if(result == NULL || arg1 == NULL) {
        return false;
    } else if(result->data == NULL 
    || arg1->data == NULL 
    || arg1->cols != result->cols 
    || arg1->rows != result->rows 
    || arg1->dataSize != result->dataSize) {
        return false;
    } else {

        for(size_t i = 0; i < (arg1->cols * arg1->rows); i++) {

            if(*(float*)(&((arg1->data)[(arg1->dataSize) * i])) < 0) {
                *(float*)(&((result->data)[(result->dataSize) * i])) = 0;
            } else {
                *(float*)(&((result->data)[(result->dataSize) * i])) = 1;
            }
        }

    }
    return true;
}






/**
 * MLP_instantiate_network
 * ===============================================
 * Brief: Create a MLP network
 * 
 * Param: *network - Network to be instantiated
 *        numberOfLayers - Number of layers to network (must be at least 3 to account for input and output layers)
 *        *neuronsPerLayer - Array of neurons per layer
 *        
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
RETURN_CODE MLP_initialise_network(Network *network, size_t numberOfLayers, size_t *neuronsPerLayer) {

    if(network == NULL || numberOfLayers < 3 || neuronsPerLayer == NULL) {
        return _INVALID_ARG_PASS_;

    } else {

        
        if(vector_initialise(&(network->hiddenLayers), sizeof(NetworkLayer)) == false) { //Vector of matricies
            return _INTERNAL_ERROR_;
        }
        if(vector_resize(&(network->hiddenLayers), numberOfLayers) == false) {
            return _INTERNAL_ERROR_;
        }
        for(size_t i = 0; i < numberOfLayers - 1; i++) { //Initialise each matrix layer, going to layers - 1 since output does not have weights/biases

            NetworkLayer currentNetworkLayer;


            //Preactivation output: Rows - Number of output neurons, Cols - 1
            if(matrix_2D_initialise(&(currentNetworkLayer.preActivationOutput), neuronsPerLayer[i + 1], 1, sizeof(float)) == false) {
                return _INTERNAL_ERROR_;
            }
            //Activation output: Rows - Number of output neurons, Cols - 1
            if(matrix_2D_initialise(&(currentNetworkLayer.output), neuronsPerLayer[i + 1], 1, sizeof(float)) == false) {
                return _INTERNAL_ERROR_;
            }


            //Weights: Rows - Number of output neurons, Cols - Number of current neurons
            if(matrix_2D_initialise(&(currentNetworkLayer.weight), neuronsPerLayer[i + 1], neuronsPerLayer[i], sizeof(float)) == false) {
                return _INTERNAL_ERROR_;
            }
            if(MLP_randomise(&(currentNetworkLayer.weight), MLP_RAND_RANGE, MLP_RAND_MIN) == false) { //Randomise weights
                return _INTERNAL_ERROR_;
            }


            //Biases: Rows - Number of output neurons, Cols - 1
            if(matrix_2D_initialise(&(currentNetworkLayer.bias), neuronsPerLayer[i + 1], 1, sizeof(float)) == false) {
                return _INTERNAL_ERROR_;
            }
            if(MLP_randomise(&(currentNetworkLayer.bias), MLP_RAND_RANGE, MLP_RAND_MIN) == false) { //Randomise weights
                return _INTERNAL_ERROR_;
            }




            //Insert layer to network
            if(vector_insert_index(&(network->hiddenLayers), i, &currentNetworkLayer) == false) {
                return _INTERNAL_ERROR_;
            }
        }
    }

    return _SUCCESS_;
}





/**
 * MLP_evaluate_input
 * ===============================================
 * Brief: Evaluate a network output (requires inputs to be set)
 * 
 * Param: *network - Network of interest
 *        
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
RETURN_CODE MLP_evaluate_input(Network *network, Vector *input) {

    if(network == NULL) {
        return _INVALID_ARG_PASS_;

    } else {

        //Evaluate hidden layers
        //Matrix *prevLayerOutput = vector_get_index(&(network->hiddenLayers), 0); //Set to input layer



        size_t numberOfHiddenLayers = vector_get_length(&(network->hiddenLayers));
        for(size_t i = 0; i < numberOfHiddenLayers; i++) {



        }

        //Evaluate output layer




    }

    return _SUCCESS_;
}











