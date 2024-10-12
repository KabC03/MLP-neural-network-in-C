#include "mlp.h"
#define NUM_TYPE float


/**
 * @brief :: Initialise a MLP network 
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
    

    size_t i = 0;
    int weightFlag = 0;
    int biasFlag = 0;
    int inputFlag = 0;

    for(i = 0; i < mlp->layers.top; i++) {
        Layer *current = vector_access_index(&(mlp->layers), i);
        size_t *currentLayerSize = vector_access_index(&(mlp->layers), i);
        size_t *nextLayerSize = vector_access_index(&(mlp->layers), i + 1);
        weightFlag = 0; 
        biasFlag = 0;
        inputFlag = 0;
        if(matrix_init(&(current->weight), sizeof(NUM_TYPE), *nextLayerSize, *currentLayerSize) == false) {
            goto cleanup;
        }
        weightFlag = 1;
        if(matrix_init(&(current->bias), sizeof(NUM_TYPE), *nextLayerSize, 1) == false) {
            goto cleanup;
        }
        biasFlag = 1;
        if(matrix_init(&(current->input), sizeof(NUM_TYPE), *nextLayerSize, *currentLayerSize) == false) {
            goto cleanup;
        }
        inputFlag = 1;
    } 

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























