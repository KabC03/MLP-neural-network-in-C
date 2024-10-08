#include "../libraries/MLP.h"
#include "../libraries/bitmap.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define FILE_BUFFER_SIZE 100
#define NUM_LAYERS 2
#define BYTES_PER_PIXEL 3
#define NEURONS_PER_LAYER {((testImage.bitmapMetadata.imageHeight * testImage.bitmapMetadata.imageWidth)), 3, 3}
//#define NEURONS_PER_LAYER {20, 100, 2, 2} /*NOTE: last 2 numbers MUST be the same to properly initilise the network*/

#define TRAIN_FLAG "-t"
#define RUN_FLAG "-r"



int main(void) {


    srand(time(NULL)); //Use default seed of 1

    //Generate a blank image

    BitmapImage testImage;
    if(bitmap_generate_image_24(&testImage, 100, 100, 255, 5, 5) != _SUCCESS_) {
        printf("Failed to generate\n");
        return -1;
    }

    

    
    if(bitmap_greyscale(&testImage) != _SUCCESS_) {
        printf("Failed to greyscale image\n");
        return -1;
    }
    

    if(bitmap_reconstruct_image(&testImage, "./data/test.bmp") != _SUCCESS_) {
        printf("Failed to reconstruct image\n");
        return -2;
    }

    

    Network network;
    size_t neuronsPerHiddenLayer[] = NEURONS_PER_LAYER;
    
    if(MLP_initialise_network(&network, NUM_LAYERS, neuronsPerHiddenLayer) != _SUCCESS_) {
        printf("Failed to initialise network\n");
        return -1;
    }


    if(MLP_evaluate_input(&network, &(testImage.bitmapData)) != _SUCCESS_) {
        printf("Failed to run network\n");
        return -1;
    }


    if(MLP_print_layers(&network) != _SUCCESS_) {
        printf("Failed to print layers\n");
        return -1;
    }

    printf("Printing network output:\n");
    if(MLP_print_output(&network) != _SUCCESS_) {
        printf("Failed to print output layer\n");
        return -1;
    }

    return 0;
}
























