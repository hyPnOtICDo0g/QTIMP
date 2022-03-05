#ifndef IMAGE_H
#define IMAGE_H

#define WHITE 255
#define BLACK 0
#define THRESHOLD 128

#include "quadtree.h"

// structure to store image data
typedef struct {
    char *fileName;
    unsigned int width;
    unsigned int height;
    unsigned int bitDepth;
    unsigned int padding;
    unsigned int blacks; // number of black pixels
    unsigned int whites; // number of white pixels
    unsigned long size; // height * width
    unsigned char header[54]; // 54 byte image header array
} IMGDATA;

// creates a quadtree by reading pixel values from an image
void constructQuadTree(QTREE* root, FILE* fIn, IMGDATA* img);

// write the image matrix to an output image by traversing a quadtree
void writeMatrix(const QTREE* root,  FILE* fIn, FILE* fOut, IMGDATA img);

// convert a color image to a B&W image
void convert(IMGDATA inFile, char* outFile);

// extract image properties from the input image and display
void imgProperties(IMGDATA* inFile);

#endif
