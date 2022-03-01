#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

struct gengetopt_args_info cmdargs;

void argsCheck(int argc, char **argv){
	if(
		// check if the command-line options provided are valid
		(cmdline_parser(argc, argv, &cmdargs) != 0 || argc == 1)
		// check if --infile and --outfile are given but there are no operational flags provided
		|| ((cmdargs.infile_given || cmdargs.outfile_given)
		&& !(cmdargs.union_given || cmdargs.intersect_given || cmdargs.convert_given || cmdargs.invert_given || cmdargs.properties_given))
	){
		printf("Usage: %s [OPTION]...\nTry '%s --help' for more information.\n", argv[0], argv[0]);
		exit(1);
    }
}

void properties(IMGDATA* inFile){
	FILE *fIn = fopen(inFile->fileName, "rb");

	// check if the input file exists on the disk
	fileCheck(fIn, inFile->fileName);

	// read the 54 byte header from the input file
	fread(inFile->header, sizeof(unsigned char), 54, fIn);

	// check if the file is a valid bitmap
	formatCheck(fIn, inFile->fileName, inFile->header);

	// extract the image properties from the header
	inFile->width = *(unsigned int*)&inFile->header[18];
	inFile->height = *(unsigned int*)&inFile->header[22];
	inFile->bitDepth = *(unsigned int*)&inFile->header[28];
	inFile->size = inFile->width*inFile->height;
	inFile->padding = ((inFile->width * 3 + 3) & ~3) - inFile->width * 3;

	printf("Name: %s\n", inFile->fileName);
	printf("Width: %d\n", inFile->width);
	printf("Height: %d\n", inFile->height);
	printf("Bit Depth: %d\n", inFile->bitDepth);
	fclose(fIn);
}

void fileCheck(FILE* fp, char* fileName){
	if(fp==NULL){
		printf("fatal: cannot open '%s'\n", fileName);
		exit(1);
	}
}

void formatCheck(FILE* fp, char* fileName, unsigned char* fileHeader){
	// use the file header to determine the file format
	if(fileHeader[0]+fileHeader[1]!=0x8f){
		printf("warning: '%s' is not a bitmap\n", fileName);
		fclose(fp);
		exit(1);
	}
}

void extractColorTable(FILE* fIn, FILE* fOut){
	unsigned char colorTable[1024];
	fread(colorTable, sizeof(unsigned char), 1024, fIn);
	fwrite(colorTable, sizeof(unsigned char), 1024, fOut);
}

void convert(IMGDATA inFile, char* outFile){
	FILE *fIn = fopen(inFile.fileName, "rb");

	properties(&inFile);

	FILE *fOut = fopen(outFile, "wb");

	// check if the program has write permission
	fileCheck(fOut, outFile);

	// write header to the output file
	fwrite(inFile.header, sizeof(unsigned char), 54, fOut);
	fseek(fIn, 54, SEEK_SET);

	// extract the color table the if a 8-bit image is provided
	if(inFile.bitDepth<=8){
		extractColorTable(fIn, fOut);
	}

	unsigned int i, j;
	unsigned char pixel, buffer[3];

    for (i=0; i<inFile.height; i++){
    	for (j=0; j<inFile.width; j++){
			// read pixel values from the input image
			fread(buffer, 3, 1, fIn);
			// convert RGB -> grayscale -> b/w
			pixel = (buffer[0] * 0.3 + buffer[1] * 0.59 + buffer[2] * 0.11) > THRESHOLD ? WHITE : BLACK;
			// copy the value stored in `pixel` to the buffer, thrice (RGB)
			memset(buffer, pixel, sizeof(buffer));
			// write the buffer to the output image
			fwrite(&buffer, 3, 1, fOut);
    	}
		// padding at every row to make it a multiple of 4 bytes
		fread(buffer, inFile.padding, 1, fIn);
		fwrite(buffer, inFile.padding, 1, fOut);
	}
	fclose(fOut);
	fclose(fIn);
}
