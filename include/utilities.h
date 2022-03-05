#ifndef UTILITIES_H
#define UTILITIES_H

#include "image.h"
#include "cmdline.h"

// structure to store command line arguments
extern struct gengetopt_args_info cmdargs;

// check if arguments follow the documented syntax
void argsCheck(int argc, char **argv);

// check if a file exists on the disk or the program has read/write permissions
void fileCheck(FILE* fp, char* fileName);

// check if a file is a bitmap
void formatCheck(FILE* fp, char* fileName, unsigned char* fileHeader);

// extract the color table, if present
void extractColorTable(FILE* fIn, FILE* fOut);

// write a pixel (RGB) to the output image
void writeByte(FILE* fOut, int val);

// initialize image structure to default values
void initImage(IMGDATA* img, char* fileName);

// check if the input image meets documented requirements
void imageCheck(IMGDATA img);

// print image and quadtree properties
void printProperties(const IMGDATA img, const QTREE* root);

// print the image matrix by traversing a quadtree (DEBUG)
void getMatrix(const QTREE* root);

#endif
