#include <stdio.h>
#include <stdlib.h>

#include "quadtree.h"
#include "functions.h"
#include "utilities.h"

void properties(char *inFile){

	FILE *fIn = fopen(inFile, "rb");

	filechk(fIn);

	// read the 54 byte header from the input file
	fread(header, sizeof(unsigned char), 54, fIn);

	frmtchk();

	width = *(int*)&header[18];
	height = *(int*)&header[22];
	bitDepth = *(int*)&header[28];

	printf("width: %ld\n", width);
	printf("height: %ld\n", height);
	printf("bit depth: %d\n", bitDepth);

	fclose(fIn);
}
