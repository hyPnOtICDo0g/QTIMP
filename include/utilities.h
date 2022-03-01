#ifndef UTILITIES_H
#define UTILITIES_H

#include "image.h"
#include "cmdline.h"

// structure to store command line arguments
extern struct gengetopt_args_info cmdargs;

// check if arguments follow the documented syntax
void argsCheck(int argc, char **argv);

// extract bitmap properties and display
void properties(IMGDATA* inFile);

// check if a file exists on the disk or the program has read/write permissions
void fileCheck(FILE* fp, char* fileName);

// check if a file is a bitmap
void formatCheck(FILE* fp, char* fileName, unsigned char* fileHeader);

// extract the color table, if present
void extractColorTable(FILE* fIn, FILE* fOut);

// convert a color image to B&W
void convert(IMGDATA inFile, char* outFile);

#endif
