#include "../libraries/MLP.h"
#include "../libraries/bitmap.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define FILE_BUFFER_SIZE 100
#define NUM_LAYERS 3
#define NEURONS_PER_LAYER {inputImage.bitmapMetadata.imageHeight * inputImage.bitmapMetadata.imageWidth, 100, 2}

#define TRAIN_FLAG "-t"
#define RUN_FLAG "-r"



int main(void) {


    //srand(time(NULL)); //Use default seed of 1


    BitmapImage inputImage;
    if(bitmap_enstantiate("../data/test_image", &inputImage) == false) {
        printf("Failed to open bitmap\n");
        return -1;
    }


    Network network;
    size_t neuronsPerHiddenLayer[] = NEURONS_PER_LAYER;
    
    if(MLP_initialise_network(&network, NUM_LAYERS, neuronsPerHiddenLayer) != _SUCCESS_) {
        printf("Failed to initialise network\n");
        return -1;
    }

    if(MLP_evaluate_input(&network, &(inputImage.bitmapData)) != _SUCCESS_) {
        printf("Failed to run network\n");
        return -1;
    }

    return 0;
}
























