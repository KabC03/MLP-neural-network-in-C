#include "mlp.h"
#define NUM_TYPE float
#define FLOAT_RAND_MAX 0.1
#define FLOAT_RAND_MIN -0.1

/**
 * @brief :: Display a networks status 
 *
 * @param :: *mlp :: Network of interest 
 *  
 * @return :: void
 */
void MLP_disp(MLP *mlp) {

    printf("\n\n");
    for(size_t i = 0; i < mlp->layers.top; i++) {
        Layer *current = vector_access_index(&(mlp->layers), i);

        printf("Layer :: %zu\n", i);

        printf("\tWeight matrix:\n");
        matrix_disp(&(current->weight), matrix_print_float);


        printf("\tBias matrix:\n");
        matrix_disp(&(current->bias), matrix_print_float);


        printf("\tInput matrix:\n");
        matrix_disp(&(current->input), matrix_print_float);
        printf("\n\n");
    }
    printf("\n\n");
    return;
}




/**
 * @brief :: Initialise a MLP network with random weights and biases
 *
 * @param :: *mlp :: Network of interest 
 * @param :: *layerNumbers :: Array specifying number of neurones in the layer
 *           [10, 4, 3, 2] - specifies 10 input, 4 in hidden, 3 in hidden, 2 in output 
 *           NOTE: To avoid segfault array should have last element duplicated
 *  
 * @return :: bool :: Indication of if initialisation was successful
 */
bool MLP_init(MLP *mlp, Vector *layerNumbers) {

    if(vector_init(&(mlp->layers), sizeof(Layer), layerNumbers->top - 1) == false) {
        return false;
    }

    Layer temp;

    size_t i = 0;
    int weightFlag = 0;
    int biasFlag = 0;
    int inputFlag = 0;

    for(i = 0; i < mlp->layers.capacity; i++) {

        Layer *current = vector_set_index(&(mlp->layers), &temp, i);
        size_t *currentLayerSize = vector_access_index(layerNumbers, i);
        size_t *nextLayerSize = vector_access_index(layerNumbers, i + 1);

        float min = FLOAT_RAND_MIN;
        float max = FLOAT_RAND_MAX;

        weightFlag = 0; 
        biasFlag = 0;
        inputFlag = 0;
        if(matrix_init(&(current->weight), sizeof(NUM_TYPE), *nextLayerSize, *currentLayerSize) == false) {
            goto cleanup;
        }
        matrix_randomise(&(current->weight), &min, &max, matrix_randomise_float);

        weightFlag = 1;
        if(matrix_init(&(current->bias), sizeof(NUM_TYPE), *nextLayerSize, 1) == false) {
            goto cleanup;
        }
        matrix_randomise(&(current->bias), &min, &max, matrix_randomise_float);
        biasFlag = 1;
        if(matrix_init(&(current->input), sizeof(NUM_TYPE), *nextLayerSize, *currentLayerSize) == false) {
            goto cleanup;
        }
        matrix_randomise(&(current->input), &min, &max, matrix_randomise_float);
        inputFlag = 1;
    } 
    mlp->layers.top = mlp->layers.capacity;
    return true;



cleanup:
    for(size_t j = 0; j < i + inputFlag; j++) {
        Layer *current = vector_access_index(&(mlp->layers), j);
        matrix_destroy(&(current->input));
    }
    for(size_t j = 0; j < i + biasFlag; j++) {
        Layer *current = vector_access_index(&(mlp->layers), j);
        matrix_destroy(&(current->bias));
    }
    for(size_t j = 0; j < i + weightFlag; j++) {
        Layer *current = vector_access_index(&(mlp->layers), j);
        matrix_destroy(&(current->weight));
    }
    return false;
}









/**
 * @brief :: Run an input through a matrix 
 *
 * @param :: *mlp :: Network of interest 
 * @param :: *input :: Input vector of data 
 * @param :: activate :: Activation function 
 *  
 * @return :: void 
 */
void MLP_run(Matrix *mlp, Vector *input, void activate(void *element)) {

    

    return;
}












