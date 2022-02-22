#ifndef STRUCT_QUADTREE_H
#define STRUCT_QUADTREE_H

#include "cmdline.h"

typedef struct gengetopt_args_info ARGINFO;

extern ARGINFO cmdargs;

extern unsigned int pixel, bitDepth;

extern unsigned long height, width;

extern unsigned long long size;

extern unsigned char header[54];

#endif
