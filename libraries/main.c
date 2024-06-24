#include "MLP.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define FILE_BUFFER_SIZE 100


#define TRAIN_FLAG "-t"
#define RUN_FLAG "-r"



#pragma pack(push,1) //Prevent packing
typedef struct BMPHeader {

    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;

} BMPHeader;
typedef struct BMPInfo {

    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imagesize;
    int32_t xresolution;
    int32_t yresolution;
    uint32_t ncolours;
    uint32_t importantcolours;

} BMPInfo;
#pragma pack(pop)








//Read into a column matrix (Greyscale and load)
bool read_image_into_matrix(Matrix *const matrix, BMPHeader *const BMPheader, BMPInfo *const BMPinfo) {

    


    return true;
}


//Train model on a folder of BMP - output weights and stuff to a text file for use again (csv)
bool train_MLP(char *dirName) {



    //Image training
    BMPHeader BMPheader;
    BMPInfo BMPinfo;
    FILE *image = NULL;
    Matrix inputLayer = {0,0,0,0};
    char fileNameBuffer[FILE_BUFFER_SIZE];

    while(1) { //For file in directory (Do in C++)



        //Assign file name here



        image = fopen(fileNameBuffer, "rb");
        if(image == NULL) {
            printf("Failed to open image '%s'\n",fileNameBuffer);
            return false;
        } 
        fread(&BMPheader, sizeof(BMPHeader), 1, image);
        fread(&BMPinfo, sizeof(BMPinfo), 1, image);
        if(BMPheader.type != 0x4D42) {
            printf("Folder should only contain BMP files - '%s'\n",fileNameBuffer);
            fclose(image);
            return false;
        }


        if(BMPinfo.height * inputLayer.cols != inputLayer.rows || BMPinfo.width != 1) { 
            //Either first time load or incorrect image size

            if(inputLayer.rows == 0 && inputLayer.cols == 0) { //First load therefore initialise matrix
                if(matrix_2D_initialise(&inputLayer, abs(BMPinfo.height * BMPinfo.width), 1, sizeof(float)) == false) {
                    printf("Failed to initialise input layer for '%s'\n",fileNameBuffer);
                    return false;
                }

            } else {
                printf("Image '%s' of incorrect dimensions\n",fileNameBuffer);
                return false;
            }
        }
    }

    fclose(image);
    return true;

}




//TODO - Filesystem libray in C++ -> call in this C file to get all files in dir
//Read image into input layer of neurons

int main(int argc, char *argv[]) {

    //Command line

    if(argc != 3) {
        printf("Format: ./main Path -flags\n\n");
        
        printf("        Path - directory of bmp images\n\n");
        printf("        Flags (max one):\n");
        printf("            -t : train Train on the dataset\n");
        printf("            -r : run  Run on the dataset\n");
        return 1;
    }



    //Check if argv[1] is a valid folder (Do in C++) with <filesystem>




    if(strcmp(argv[2], TRAIN_FLAG) == 0) {
        //Train model
        
        /* REMOVE COMMENT ONE FILESYSTEM IS STE UP IN C++
        if(train_MLP(directory) == false ){
        return 1;
        }
        */

    } else if(strcmp(argv[2], RUN_FLAG) == 0) {
        //Prediction






    } else {

        printf("Unrecognised flag'%s'\n",argv[2]);
        return 1;
    }



    return 0;
}



























