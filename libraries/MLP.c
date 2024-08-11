#include "MLP.h"
#define MLP_RAND_RANGE 0.1
#define MLP_RAND_MIN 0.001
#define square(value) (value * value)
#define HERE printf("HERE\n");





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



//Data for the hidden layer
typedef struct HiddenLayer {

    Matrix weight;              //Weight for each neuron
    Matrix bias;                //Bias
    Matrix preActivationOutput; //Store preactivation output for back propagation
    Matrix output;              //Output of the layer (after activation, bias, etc)

} HiddenLayer;


/**
 * MLP_instantiate_network
 * ===============================================
 * Brief: Create a MLP network
 * 
 * Param: *network - Network to be instantiated
 *        numberOfHiddenNeurons - Number of input neurons
 *        numHidden - Number of hidden layers
 *        *hiddenLayerSizeArray - Array of numbers specifying size of each hidden layer
 *        numOutputNeurons - Number of output neurons
 *        
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
RETURN_CODE MLP_initialise_network(Network *network, size_t numberOfInputNeurons, size_t numberOfHiddenLayers, size_t *hiddenNeuronsPerLayer, size_t numberOfOutputNeurons) {

    if(network == NULL || numberOfInputNeurons == 0 || numberOfHiddenLayers == 0 || hiddenNeuronsPerLayer == NULL || numberOfOutputNeurons == 0) {
        return _INVALID_ARG_PASS_;

    } else {

        //Initialise hidden layer
        if(matrix_2D_initialise(&(network->inputLayer), numberOfInputNeurons, 1, sizeof(float)) == false) {

            return _INTERNAL_ERROR_;
        }

        
        //Initialise hidden layer
        if(vector_initialise(&(network->hiddenLayers), sizeof(HiddenLayer)) == false) { //Vector of matricies
            return _INTERNAL_ERROR_;
        }
        if(vector_resize(&(network->hiddenLayers), numberOfHiddenLayers) == false) {
            return _INTERNAL_ERROR_;
        }
        for(size_t i = 0; i < numberOfHiddenLayers; i++) { //Initialise each matrix layer
            HiddenLayer currentHiddenLayer;

            //Initialise pre-activation values - Rows: 1, Cols: Number of neurons in next layer
            if(i == numberOfHiddenLayers - 1) { //Last hidden layer connects to output neurons
                if(matrix_2D_initialise(&(currentHiddenLayer.preActivationOutput), numberOfOutputNeurons, 1, sizeof(float)) == false) {
                    return _INTERNAL_ERROR_;
                }
            } else { //This is really inefficient but makes the code cleaner - consider optimising later
                if(matrix_2D_initialise(&(currentHiddenLayer.preActivationOutput), hiddenNeuronsPerLayer[i + 1], 1, sizeof(float)) == false) {
                    return _INTERNAL_ERROR_;
                }
            }
            //Initialise output values - Rows: 1, Cols: Number of neurons in next layer
            if(i == numberOfHiddenLayers - 1) { //Last hidden layer connects to output neurons
                if(matrix_2D_initialise(&(currentHiddenLayer.output), numberOfOutputNeurons, 1, sizeof(float)) == false) {
                    return _INTERNAL_ERROR_;
                }
            } else { //This is really inefficient but makes the code cleaner - consider optimising later
                if(matrix_2D_initialise(&(currentHiddenLayer.output), hiddenNeuronsPerLayer[i + 1], 1, sizeof(float)) == false) {
                    return _INTERNAL_ERROR_;
                }
            }



            //Initialise biases - Rows: Number of neurons in next layer, Cols: 1
            if(i == numberOfHiddenLayers - 1) { //Last hidden layer connects to output neurons
                if(matrix_2D_initialise(&(currentHiddenLayer.bias), numberOfOutputNeurons, 1, sizeof(float)) == false) {
                    return _INTERNAL_ERROR_;
                }
            } else { //This is really inefficient but makes the code cleaner - consider optimising later
                if(matrix_2D_initialise(&(currentHiddenLayer.bias), hiddenNeuronsPerLayer[i + 1], 1, sizeof(float)) == false) {
                    return _INTERNAL_ERROR_;
                }
            }
            if(MLP_randomise(&(currentHiddenLayer.bias), MLP_RAND_RANGE, MLP_RAND_MIN) == false) { //Randomise biases
                return _INTERNAL_ERROR_;
            }


            //Initialise weights - Rows: Number of neurons in next layer, Cols: Number of neurons in current layer
            if(i == numberOfHiddenLayers - 1) { //Last hidden layer connects to output neurons
                if(matrix_2D_initialise(&(currentHiddenLayer.weight), numberOfOutputNeurons, hiddenNeuronsPerLayer[i], sizeof(float)) == false) {
                    return _INTERNAL_ERROR_;
                }
            } else { //This is really inefficient but makes the code cleaner - consider optimising later
                if(matrix_2D_initialise(&(currentHiddenLayer.weight), hiddenNeuronsPerLayer[i + 1], hiddenNeuronsPerLayer[i], sizeof(float)) == false) {
                    return _INTERNAL_ERROR_;
                }
            }


            if(MLP_randomise(&(currentHiddenLayer.weight), MLP_RAND_RANGE, MLP_RAND_MIN) == false) { //Randomise weights
                return _INTERNAL_ERROR_;
            }

            //Insert layer to network
            if(vector_insert_index(&(network->hiddenLayers), i, &currentHiddenLayer) == false) {
                return _INTERNAL_ERROR_;
            }
        }


        //Initialise output layer
        if(matrix_2D_initialise(&(network->outputLayer), numberOfOutputNeurons, 1, sizeof(float)) == false) {
            return _INTERNAL_ERROR_;
        }
    }

    return _SUCCESS_;
}









/**
 * MLP_input_to_network
 * ===============================================
 * Brief: Input a vector to a network but do not evaluate it
 * 
 * Param: *network - Network of interest
 *        *inputVector - Input vector to input layer
 *        
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
RETURN_CODE MLP_input_to_network(Network *network, Vector *inputToNetwork) {

    if(network == NULL || inputToNetwork == NULL) {
        return _INVALID_ARG_PASS_;
    } else {

        if(matrix_2D_set(&(network->inputLayer), network->inputLayer.rows, network->inputLayer.cols, (void*)(inputToNetwork->data), sizeof(float)) == false) {
            return _INTERNAL_ERROR_;
        }
    }

    return _SUCCESS_;
}
















