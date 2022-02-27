#ifndef IMAGE_H
#define IMAGE_H

#define WHITE 255
#define BLACK 0
#define THRESHOLD 128

#include "cmdline.h"

// structure to store command line arguments
typedef struct gengetopt_args_info ARGINFO;

extern ARGINFO cmdargs;

extern unsigned int pixel, bitDepth;

extern unsigned long height, width;

extern unsigned long long size;

// 54 byte image header array
extern unsigned char header[54];

#endif
