#ifndef UTILITIES_H
#define UTILITIES_H

#include "image.h"

// check if arguments follow the documented syntax
void argschk(int argc, char **argv);

// extract bitmap properties and display
void properties(IMGDATA inFile);

// check if a file exists on the disk
void readchk(FILE* fp, char* fileName);

// check if a file is a bitmap
void frmtchk(char* fileName, unsigned char* fileHeader);

// check if the program has permission to write to disk
void writechk(FILE* fp, char* file);

// handle input and output files
void filehandler(char* inFileOne, char* inFileTwo, char* outFile);

#endif
