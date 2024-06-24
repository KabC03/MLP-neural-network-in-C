#include "MLP.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>








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
    uint16_t bits;
    uint32_t compression;
    uint32_t imagesize;
    int32_t xresolution;
    int32_t yresolution;
    uint32_t ncolours;
    uint32_t importantcolours;

} BMPInfo;
#pragma pack(pop)








int main(void) {

    
    BMPHeader BMPheader;
    BMPInfo BMPinfo;

    FILE *image = fopen("./logo.bmp", "rb");
    if(image == NULL) {
        printf("Failed to open image\n");
        return 1;
    } 

    fread(&BMPheader, sizeof(BMPHeader), 1, image);
    fread(&BMPinfo, sizeof(BMPinfo), 1, image);

    if(BMPheader.type != 0x4D42) {
        printf("Folder should only contain BMP files\n");
        fclose(image);
        return 1;
    }


    printf("Width: %d\n", BMPinfo.width);
    printf("Height: %d\n", BMPinfo.height);
    printf("Bit Depth: %d\n", BMPinfo.bits);




    fclose(image);
    return 0;
}



























 
