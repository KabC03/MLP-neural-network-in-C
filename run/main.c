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




int main(void) {



    return 0;
}
























