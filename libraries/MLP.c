#include "MLP.h"
#define MLP_RAND_RANGE 0.1
#define MLP_RAND_MIN 0.001
#define square(value) (value * value)
#define HERE printf("HERE\n");
#define BYTE_SIZE 255
#define BYTES_PER_PIXEL 3
#define MLP_activate(arg1, result) MLP_ReLu(arg1, result)



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
            *((float*)(&(matrix->data[(matrix->dataSize) * i]))) = (min + (range * (float)rand())/RAND_MAX);
        }

    }
    return true;
}

/**
 * MLP_normalise
 * ===============================================
 * Brief: Normalise a matrix by a value
 * 
 * Param: *matrix - matrix of interest
 *        value - value to normalise to
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool MLP_normalise(Matrix *const matrix, float value) {

    if(matrix == NULL) {
        return false;
    } else if(matrix->data == NULL) {
        return false;
    } else {


        for(size_t i = 0; i < (matrix->cols * matrix->rows); i++) {
            *(float*)(&((matrix->data[(matrix->dataSize) * i]))) /= value;
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
bool MLP_mean_square_error(Matrix *const matrix, Matrix *const expectedValues ,float *output) {

    if(matrix == NULL || output == NULL || expectedValues == NULL) {
        return false;
    } else if(matrix->data == NULL) {
        return false;
    } else {

        if(expectedValues->cols != matrix->cols || expectedValues->rows != matrix->rows) {
            return false; //Invalid dimensions
        }


        (*output) = 0;
        for(size_t i = 0; i < (matrix->rows * matrix->cols); i++) {

            (*output) += square((float)((matrix->data)[i * matrix->dataSize]) - (float)((expectedValues->data)[i * expectedValues->dataSize]));
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
                *((float*)(&((result->data)[(result->dataSize) * i]))) = 0;
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
 *        numberOfLayers - Number of layers to network (When = 2 this means there is a direct connection from input -> output layer)
 *        *neuronsPerLayer - Array of neurons per layer, MUST be 1 longer than the number of layers, where last number is DUPLICATED
 *                      E.g if numberOfLayers = 2, then len(neuronsPerLayer) MUST = 3, where arr[1] == arr[2], this is NOT checked by the function for performance
 *        
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
RETURN_CODE MLP_initialise_network(Network *network, size_t numberOfLayers, size_t *neuronsPerLayer) {

    if(network == NULL || numberOfLayers < 2 || neuronsPerLayer == NULL) { //2 layers means inputs are directly connected to output
        return _INVALID_ARG_PASS_;

    } else {

        
        if(vector_initialise(&(network->networkLayers), sizeof(NetworkLayer)) == false) { //Vector of matricies
            return _INTERNAL_ERROR_;
        }
        if(vector_resize(&(network->networkLayers), numberOfLayers) == false) {
            return _INTERNAL_ERROR_;
        }
        for(size_t i = 0; i < numberOfLayers; i++) { //NOTE: since going to i < layers, MUST make sure that last layer is DUPLICATED, e.g if number layers = 2, per layer = {x,y,z}

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
            if(vector_insert_index(&(network->networkLayers), i, &currentNetworkLayer) == false) {
                return _INTERNAL_ERROR_;
            }
        }

    }

    return _SUCCESS_;
}





/**
 * MLP_evaluate_input
 * ===============================================
 * Brief: Evaluate a network output (requires inputs to be set) - ASSUMES R-G-B in GREYSCALE format
 * 
 * Param: *network - Network of interest
 *        
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
RETURN_CODE MLP_evaluate_input(Network *network, Vector *input) {

    if(network == NULL || input == NULL) {
        return _INVALID_ARG_PASS_;

    } else {

        if(vector_get_length(input) == -1 || vector_get_length(input) == 0) {
            return _INVALID_ARG_PASS_;
        }


        //Input data to network
        /*
        TODO:
        - Convert input vector data to floats
        - Normalise matrix
        */


        //Run model
        /*
        TODO:
        for layer in layers:
        
        preActivatedOutput = [weights]*[input] + [bias]; //STORE THIS
        output = act(preActivatedOutput); //STORE THIS
        input = output;

        */

       //This is VERY inefficient - should optimise it later
        Matrix inputToInputLayer;
        Vector inputAsFloat;
        if(vector_initialise(&inputAsFloat, sizeof(float)) == false) {
            return _INTERNAL_ERROR_;
        }
        //Convert uint8 to float
        for(size_t i = 0; i < vector_get_length(input) + 1; i++) {
            const uint8_t *currentInt = vector_get_index(input, i); //Get the bottom 8 bits



            if(currentInt == NULL) {
                return _INTERNAL_ERROR_;
            }

            float current = (float)(*currentInt); //Have to do it in one line otherwise a buffer overflow occurs
            //printf("Int: %f\n", current);
            if(vector_quick_append(&inputAsFloat, &(current), 1) == false) {
                return _INTERNAL_ERROR_;
            }
        }

        //Assign to new matrix
        if(matrix_2D_initialise(&inputToInputLayer, vector_get_length(input) + 1, 1, sizeof(float)) == false) {
            return _INTERNAL_ERROR_;
        }
        if(matrix_2D_set(&inputToInputLayer, vector_get_length(&inputAsFloat) + 1, 1, inputAsFloat.data, sizeof(float)) == false) {
            return _INTERNAL_ERROR_;
        }
        
        /*
        printf("Rows: %zu, Cols: %zu\n",inputToInputLayer.rows, inputToInputLayer.cols);
        if(matrix_2D_print(&inputToInputLayer) == false) {
            return _INTERNAL_ERROR_;
        }
        printf("\n");
        */
        
        if(MLP_normalise(&inputToInputLayer, BYTE_SIZE) == false) {
            return _INTERNAL_ERROR_;
        }

        /*
        printf("NORM || Rows: %zu, Cols: %zu\n",inputToInputLayer.rows, inputToInputLayer.cols);
        if(matrix_2D_print(&inputToInputLayer) == false) {
            return _INTERNAL_ERROR_;
        }
        printf("\n");
        */


        Matrix *inputToLayer = &inputToInputLayer;
        size_t numberOfLayers = vector_get_length(&(network->networkLayers)) + 1;
        for(size_t i = 0; i < numberOfLayers; i++) {

            NetworkLayer *currentLayer = (NetworkLayer*)vector_get_index(&(network->networkLayers), i);
            if(currentLayer == NULL) {
                return _INTERNAL_ERROR_;
            }

            //preActivatedOutput = [weights]*[input] + [bias]; //STORE THIS
            if(matrix_2D_multiply(&(currentLayer->preActivationOutput), &(currentLayer->weight), inputToLayer, matrix_2D_multiply_float_component) == false) {
                return _INTERNAL_ERROR_;
            }
            
            /*
            printf("Preactivation: %zu\n",i);
            if(matrix_2D_print(&(currentLayer->preActivationOutput)) == false) {
                return _INTERNAL_ERROR_;
            }
            printf("\n");
            */


            if(matrix_2D_add(&(currentLayer->preActivationOutput), &(currentLayer->preActivationOutput), &(currentLayer->bias), matrix_2D_add_float_component) == false) {
                return _INTERNAL_ERROR_;
            }

            //output = act(preActivatedOutput); //STORE THIS
            if(MLP_activate(&(currentLayer->preActivationOutput), &(currentLayer->output)) == false) {
                return _INTERNAL_ERROR_;
            }

            //input = output;
            inputToLayer = &(currentLayer->output);



            /*
            printf("Layer: %zu\n",i);
            if(matrix_2D_print(&(currentLayer->output)) == false) {
                return _INTERNAL_ERROR_;
            }
            printf("\n");
            */
        }



    }

    return _SUCCESS_;
}






/**
 * MLP_backpropagate
 * ===============================================
 * Brief: Perform backpropagation on the network
 * 
 * Param: *network - Network of interest
 *        *expectedOutput - Expected output of output neurons
 *        
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
RETURN_CODE MLP_backpropagate(Network *network, Matrix *expectedOutput) {

    if(network == NULL || expectedOutput == NULL) {
        return _INVALID_ARG_PASS_;

    } else {

        Matrix *outputLayer = vector_get_index(&(network->networkLayers), vector_get_length(&network->networkLayers));
        if(outputLayer == NULL) {
            return _INTERNAL_ERROR_;
        }

        if(outputLayer->cols != expectedOutput->cols || outputLayer->rows != expectedOutput->rows) {

            return _INVALID_ARG_PASS_; //Invalid dimensions
        }


        //Calculate error
        if(MLP_mean_square_error(outputLayer, expectedOutput, &(network->networkError)) == false) {
            return _INTERNAL_ERROR_;
        }












    }

    return _SUCCESS_;

}










/**
 * MLP_print_output
 * ===============================================
 * Brief: Print the output matrix at the output layer
 * 
 * Param: *network - Network of interest
 *        
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
RETURN_CODE MLP_print_output(Network *network) {

    if(network == NULL) {
        return _INVALID_ARG_PASS_;

    } else {

        NetworkLayer *outputLayer = (NetworkLayer*)vector_get_index(&(network->networkLayers), vector_get_length(&(network->networkLayers)));

        if(matrix_2D_print(&(outputLayer->output)) == false) {
            return _INTERNAL_ERROR_;
        }
    }

    return _SUCCESS_;
}



/**
 * MLP_print_layers
 * ===============================================
 * Brief: Print all layers of a network
 * 
 * Param: *network - Network of interest
 *        
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
RETURN_CODE MLP_print_layers(Network *network) {

    if(network == NULL) {
        return _INVALID_ARG_PASS_;

    } else {


        for(size_t i = 0; i < vector_get_length(&(network->networkLayers)) + 1; i++) {
            NetworkLayer *currentLayer = (NetworkLayer*)vector_get_index(&(network->networkLayers), i);


            printf("Layer: %zu ||| Neurons: %zu\n", i, vector_get_size(&(network->networkLayers)) + 1);


            printf("    bias:\n");
            if(matrix_2D_print(&(currentLayer->bias)) == false) {
                return _INTERNAL_ERROR_;
            }

            printf("    weight:\n");
            if(matrix_2D_print(&(currentLayer->weight)) == false) {
                return _INTERNAL_ERROR_;
            }

            printf("    pre-ac:\n");
            if(matrix_2D_print(&(currentLayer->preActivationOutput)) == false) {
                return _INTERNAL_ERROR_;
            }

            printf("    output:\n");
            if(matrix_2D_print(&(currentLayer->output)) == false) {
                return _INTERNAL_ERROR_;
            }
            printf("\n\n\n");
        }

    }

    return _SUCCESS_;
}








