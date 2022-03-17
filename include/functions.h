#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "utilities.h"

/* Handlers for Image Operations */

// `--union` OR `--intersect`
void genericHandler(FILE* fIn1, FILE* fIn2, FILE* fOut, IMGDATA imgInFile1, IMGDATA imgInFile2, ARGINFO cmdargs);

// `--invert`
void invertHandler(FILE* fIn, FILE* fOut, IMGDATA imgInFile);

// `--properties`
QTREE* propertiesHandler(FILE* fIn, IMGDATA* inFile);

// `--convert`
void convertHandler(FILE* fIn, FILE* fOut, IMGDATA imgInFile, char* outFile);

#endif
