#define WHITE 255
#define BLACK 0
#define THRESHOLD 128

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

	clock_t start, stop;
	start = clock();

	unsigned int i, j, pixel, bitDepth;
	unsigned long long size, height, width;
	unsigned char header[54];

	// check for correct number of arguments
	if(argc!=3){

		printf("fatal: requires 2 arguments but %d were provided\n", argc-1);
		return 0;
	}

	FILE *fIn = fopen(argv[1], "rb");

	// check whether the file is present
	if(fIn==NULL){

		printf("fatal: file does not exist\n");
		return 0;
	}

	// read the 54 byte header from the input file
	fread(header, sizeof(unsigned char), 54, fIn);

	// check if the given file is a bitmap
	if(header[0]+header[1]!=0x8f){

		printf("fatal: not a bitmap\n");
		return 0;
	}

	FILE *fOut = fopen(argv[2], "wb");

	// write header to the output file
	fwrite(header, sizeof(unsigned char), 54, fOut);

	// extract the image height, width and bit depth from image header
	width = *(int*)&header[18];
	height = *(int*)&header[22];
	bitDepth = *(int*)&header[28];
	size = height*width;

	// extract the color table the image is of <=8-bit depth
	if(bitDepth<=8){

		unsigned char colorTable[1024];
		fread(colorTable, sizeof(unsigned char), 1024, fIn);
		fwrite(colorTable, sizeof(unsigned char), 1024, fOut);
	}

	printf("width: %lld\n", width);
	printf("height: %lld\n", height);
	printf("bit depth: %d\n", bitDepth);

	// allocate buffer to store the image
	unsigned char (*buffer)[size][3] = malloc(sizeof *buffer);

	// check if malloc succeded in allocating required buffer size
	if(buffer==NULL){

		printf("warning: insufficient memory");
		return 0;
	}

	// traverse all the pixels in the image
	for(i=0; i<size; i++){

		// get RGB values from buffer
		(*buffer)[i][2]=getc(fIn);
		(*buffer)[i][1]=getc(fIn);
		(*buffer)[i][0]=getc(fIn);

		// convert RGB -> grayscale -> b/w
		pixel = (((*buffer)[i][0]*0.3) + ((*buffer)[i][1]*0.59) + ((*buffer)[i][2]*0.11)) > THRESHOLD ? WHITE : BLACK;

		// write the pixel to output file
		for(j=0; j<3; j++)
			putc(pixel, fOut);
	}

	fclose(fOut);
	fclose(fIn);
	free(buffer);

	stop = clock();

	printf("time taken: %.3lfs\n", ((double)((stop-start)*1000.0)/CLOCKS_PER_SEC)/1000);
	return 0;
}
