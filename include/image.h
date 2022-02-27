#ifndef IMAGE_H
#define IMAGE_H

#define WHITE 255
#define BLACK 0
#define THRESHOLD 128

#include "cmdline.h"

// structure to store command line arguments
typedef struct gengetopt_args_info ARGINFO;

// structure to store image data
typedef struct {
    char* fileName;
    unsigned int pixel; // pixel value, can be white or black
    unsigned int bitDepth;
    unsigned int height;
    unsigned int width;
    unsigned long long size; // height * width
    unsigned char header[54]; // 54 byte image header array
} IMGDATA;

extern ARGINFO cmdargs;

#endif
