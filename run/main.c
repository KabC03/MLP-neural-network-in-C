#include "../libraries/MLP.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define FILE_BUFFER_SIZE 100


#define TRAIN_FLAG "-t"
#define RUN_FLAG "-r"



int main(void) {


    //srand(time(NULL)); //Use default seed of 1
    Network network;
    size_t neuronsPerHiddenLayer[] = {5};
    
    if(MLP_initialise_network(&network, 10, 1, neuronsPerHiddenLayer, 2) != _SUCCESS_) {
        printf("Failed to initialise network\n");
        return -1;
    }



    return 0;
}
























