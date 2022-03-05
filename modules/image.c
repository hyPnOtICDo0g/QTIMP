#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "image.h"
#include "utilities.h"

void constructQuadTree(QTREE* root, FILE* fIn, IMGDATA* img){
    unsigned int i, j, pixel, offset = 4-((img->width*3)%4);
    if (offset == 4){
        offset = 0;
    }
    for(i=0; i<img->height; i++){
        for(j=0; j<img->width; j++){
            // read the `blue` pixel value
            fread(&pixel, 1, 1, fIn);
            if(pixel==WHITE){
			    setPixel(root, i, j, i, j, 1);
				img->whites++;
            }
			else if(pixel==BLACK){
				img->blacks++;
			}
			else{
				printf("fatal: '%s' does not meet documented requirements\n", img->fileName);
				fclose(fIn);
				deleteTree(root);
				exit(1);
			}
            // ignore `green` and `red` pixel values since they are same as blue
            fseek(fIn, 2, SEEK_CUR);
        }
        fseek(fIn, offset, SEEK_CUR);
    }
}

void convert(IMGDATA inFile, char* outFile){
	FILE *fIn = fopen(inFile.fileName, "rb");

	imgProperties(&inFile);

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
			writeByte(fOut, pixel);
    	}
		// padding at every row to make it a multiple of 4 bytes
		fread(buffer, inFile.padding, 1, fIn);
		fwrite(buffer, inFile.padding, 1, fOut);
	}
	fclose(fOut);
	fclose(fIn);
}

void imgProperties(IMGDATA* inFile){
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

	fclose(fIn);
}

void writeMatrix(const QTREE* root, FILE* fIn, FILE* fOut, IMGDATA img){
	int i, j;
	unsigned char padding;
	for (i=0; i<pow(2, root->level); i++){
		for (j=0; j<pow(2, root->level); j++){
			// check if the pixel obtained is a white pixel
			if(getPixel(root, i, j)){
				writeByte(fOut, WHITE);
			}
			// else it is a black pixel
			else{
				writeByte(fOut, BLACK);
			}
		}
		fread(&padding, img.padding, 1, fIn);
		fwrite(&padding, img.padding, 1, fOut);
	}
}
