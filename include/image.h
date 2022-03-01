#ifndef IMAGE_H
#define IMAGE_H

#define WHITE 255
#define BLACK 0
#define THRESHOLD 128

// structure to store image data
typedef struct {
    char *fileName;
    unsigned int bitDepth;
    unsigned int height;
    unsigned int width;
    unsigned int padding;
    unsigned long long size; // height * width
    unsigned char header[54]; // 54 byte image header array
} IMGDATA;

#endif
