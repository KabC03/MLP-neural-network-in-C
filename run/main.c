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
//#define NEURONS_PER_LAYER {inputImage.bitmapMetadata.imageHeight * inputImage.bitmapMetadata.imageWidth, 100, 2}
#define NEURONS_PER_LAYER {20, 100, 2, 2} /*NOTE: last 2 numbers MUST be the same to properly initilise the network*/

#define TRAIN_FLAG "-t"
#define RUN_FLAG "-r"



int main(void) {


    //srand(time(NULL)); //Use default seed of 1


    BitmapImage testImage;
    if(bitmap_generate_image_24(&testImage, 255, 0, 0, 1000, 1000) != _SUCCESS_) {
        printf("Failed to generate\n");
        return -1;
    }
    printf("Image generated\n");
    /*
    if(bitmap_greyscale(&testImage) != _SUCCESS_) {
        printf("Failed to greyscale\n");
        return -3;
    }
    */
    if(bitmap_reconstruct_image(&testImage, "./data/test.bmp") != _SUCCESS_) {
        printf("Failed to reconstruct image\n");
        return -2;
    }

    return 0;



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
























