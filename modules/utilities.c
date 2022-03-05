#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

void fileCheck(FILE* fp, char* fileName){
	if(fp == NULL){
		printf("fatal: cannot open '%s'\n", fileName);
		exit(1);
	}
}

void formatCheck(FILE* fp, char* fileName, unsigned char* fileHeader){
	// use the file header to determine the file format
	if(fileHeader[0]+fileHeader[1] != 0x8f){
		printf("warning: '%s' is not a bitmap\n", fileName);
		fclose(fp);
		exit(1);
	}
}

void imageCheck(IMGDATA img){
	if(
		// check if it is a 24-bit image
		(img.bitDepth != 24)
		// check if the image width and height are equal
		|| (img.width != img.height)
		// check if the image width is a power of 2
		|| (!(img.width && (!(img.width & (img.width-1)))))
		// check if the image width within the 2^20 powers
		|| (log2(img.width) > 20)
	){
		printf("fatal: '%s' does not meet documented requirements\n", img.fileName);
		exit(1);
	}
}

void extractColorTable(FILE* fIn, FILE* fOut){
	// only 24-bit bitmaps are supported
	// this function was added only for the sake of completeness
	unsigned char colorTable[1024];
	fread(colorTable, sizeof(unsigned char), 1024, fIn);
	fwrite(colorTable, sizeof(unsigned char), 1024, fOut);
}

void writeByte(FILE* fOut, int val){
	unsigned char buffer[3];
	// copy the pixel value to the buffer, thrice (RGB)
	memset(buffer, val, sizeof(buffer));
	// write the buffer to the output image
	fwrite(&buffer, 3, 1, fOut);
}

void getMatrix(const QTREE* root){
	int i, j;
	for (i=0; i<pow(2, root->level); i++){
		for (j=0; j<pow(2, root->level); j++){
			printf("%u ", getPixel(root, i, j));
		}
		printf("\n");
	}
	printf("\n");
}

void initImage(IMGDATA* img, char* fileName){
	img->fileName = fileName;
	img->blacks = 0;
	img->whites = 0;
}

void printProperties(const IMGDATA img, const QTREE* root){
	unsigned long total = totalCount(root), whites = countNodes(root, 1), blacks = countNodes(root, 0);
	float rawImgSize = (img.size*img.bitDepth)/(float)(8*1024*1024), qtSize = (total*sizeof(QTREE))/(float)(1024*1024);
	printf("\nProperties (%s):\n", img.fileName);
	printf("Image resolution: %ux%u | bit depth: %u\n", img.width, img.height, img.bitDepth);
	// total pixels = size of the image
	// number of pixels are multiplied by 3 since we have to count the pixels in all three planes (RGB)
	printf("Total pixels: %lu | whites: %u | blacks: %u\n", img.size*3, img.whites*3, img.blacks*3);
	printf("Tree level: %d | Total nodes: %lu | greys: %lu | whites: %lu | blacks: %lu\n", root->level, total, total-(whites+blacks), whites, blacks);
	// below values are converted to megabytes in the final output
	// raw image size = image size * bit depth
	// quadtree size = total nodes * sizeof(QTREE)
	// size reduction = (raw image size - quadtree size) / raw image size * 100
	printf("Raw image size: %.3f MB | Quadtree size: %.3f MB | Size reduction: %.f%%\n", rawImgSize, qtSize, ((rawImgSize-qtSize)/rawImgSize)*100);
}
