#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cmdline.h"
#include "image.h"
#include "quadtree.h"
#include "utilities.h"

ARGINFO cmdargs;

int main(int argc, char **argv){

	clock_t time = clock();

	argschk(argc, argv);

	if(cmdargs.properties_given){
		IMGDATA imgInfile;
		imgInfile.fileName = cmdargs.properties_arg;
		properties(imgInfile);
	}
/*
	else if(cmdargs.union_given){
		filehandler(cmdargs.union_arg, cmdargs.outfile_arg);
	}
	else if(cmdargs.intersect_given){
		filehandler(cmdargs.intersect_arg, cmdargs.outfile_arg);
	}

	//can add tree depth, number of nodes, count white & black pixels etc
	// count number of nodes and actual pixels and display size reduction between them
	FILE *fOut = fopen(cmdargs.outfile_arg, "wb");

	// write header to the output file
	fwrite(header, sizeof(unsigned char), 54, fOut);

	size = height*width;

	// extract the color table the image is of <=8-bit depth
	if(bitDepth<=8){

		unsigned char colorTable[1024];
		fread(colorTable, sizeof(unsigned char), 1024, fIn);
		fwrite(colorTable, sizeof(unsigned char), 1024, fOut);
	}

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
		// write entire buffer later instead?
		for(j=0; j<3; j++)
			putc(pixel, fOut);
	}

	fclose(fOut);
	fclose(fIn);
	free(buffer);
*/

	time = clock()-time;

	printf("time taken: %.3fs\n", (double)(time)/CLOCKS_PER_SEC);
	return 0;
}
