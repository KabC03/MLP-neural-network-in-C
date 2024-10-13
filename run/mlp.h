//10 October 2024
#ifndef MLP_H 
#define MLP_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../libraries/vector.h"
#include "../libraries/matrix.h"
typedef struct Layer {

    Matrix weight; //Weight matrix
    Matrix bias;   //Bias matrix
    Matrix input;  //Layer input 

} Layer;
typedef struct MLP {

    Vector layers; //Vector of layers

} MLP;


void MLP_disp(MLP *mlp);
bool MLP_init(MLP *mlp, Vector *layerNumbers);
void MLP_run(MLP *mlp, Vector *input, Vector *output, void activate(void *element));
/*
TODO:
- Compute the output of a network from an input
- Distroy a network
*/


#endif 



      
      
      
      