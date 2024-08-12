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
#define BYTES_PER_PIXEL 3
#define NEURONS_PER_LAYER {((testImage.bitmapMetadata.imageHeight * testImage.bitmapMetadata.imageWidth)), 2, 3, 3}
//#define NEURONS_PER_LAYER {20, 100, 2, 2} /*NOTE: last 2 numbers MUST be the same to properly initilise the network*/

#define TRAIN_FLAG "-t"
#define RUN_FLAG "-r"



int main(void) {


    //srand(time(NULL)); //Use default seed of 1


    //Generate a blank image

    BitmapImage testImage;
    if(bitmap_generate_image_24(&testImage, 0, 100, 255, 10, 10) != _SUCCESS_) {
        printf("Failed to generate\n");
        return -1;
    }
    

    
    //Smiley face
    if(bitmap_colour_pixel(&testImage, 3, 7, 255, 255, 0) != _SUCCESS_) {
        printf("Failed to colour pixel\n");
        return -4;
    }
    if(bitmap_colour_pixel(&testImage, 7, 7, 255, 255, 0) != _SUCCESS_) {
    printf("Failed to colour pixel\n");
    return -4;
    }

    if(bitmap_draw_line(&testImage, 1, 3, 7, 2, 255, 255, 255, 1) != _SUCCESS_) {
        printf("Failed to draw line\n");
        return -3;
    }
    if(bitmap_draw_line(&testImage, 5, 2, 7, 3, 255, 255, 255, 1) != _SUCCESS_) {
        printf("Failed to draw line\n");
        return -3;
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


    printf("Printing network output:\n");
    if(MLP_print_output(&network) != _SUCCESS_) {
        printf("Failed to print output layer\n");
        return -1;
    }

    return 0;
}
























