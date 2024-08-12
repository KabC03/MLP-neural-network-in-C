//A basic bitmap library in C
//14, Jul, 2024

#ifndef BITMAP_H 
#define BITMAP_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "vector.h" 
#include "return codes.h"


#pragma pack(push, 1)

//Enstatntiate BMPImage not this
typedef struct BitmapHeader {

    uint16_t fileType;
    uint32_t fileSize;
    uint16_t res1;
    uint16_t res2;
    uint32_t dataOffset;

} BitmapHeader;
typedef struct BitmapMetadata {

    uint32_t headerSize;
    int32_t imageWidth;
    int32_t imageHeight;
    uint16_t numberOfPlanes;
    uint16_t bitsPerPixel;
    uint32_t compressionType;
    uint32_t imageFileSize;
    int32_t xRes;
    int32_t yRes;
    uint32_t numberOfColours;
    uint32_t importantColours;

} BitmapMetadata;
typedef struct BitmapImage {

    FILE *bitmapImagePtr;
    BitmapHeader bitmapHeader;
    BitmapMetadata bitmapMetadata;
    Vector bitmapData;

} BitmapImage;


#pragma pack(pop)


RETURN_CODE bitmap_enstantiate(char *bitmapPath, BitmapImage *bitmapImageOutput);
RETURN_CODE bitmap_generate_image_24(BitmapImage *outputImage, uint8_t red, uint8_t green, uint8_t blue, size_t xRes, size_t yRes);
RETURN_CODE bitmap_greyscale(BitmapImage *bitmapImage);
RETURN_CODE bitmap_reconstruct_image(BitmapImage *bitmapImage, char *imageName);
RETURN_CODE bitmap_destroy(BitmapImage *bitmapImage);
RETURN_CODE bitmap_return_metadata(BitmapImage *bitmapImage, BitmapMetadata *outputMetadata);


#endif // BITMAP_H





