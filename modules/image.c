#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "image.h"
#include "quadtree.h"
#include "utilities.h"

int main(int argc, char **argv){

	clock_t time = clock();

	argsCheck(argc, argv);

	IMGDATA imgInFile1, imgInFile2;
	imgInFile1.fileName = cmdargs.infile_arg[0];
	imgInFile2.fileName = cmdargs.infile_arg[1];

	if(cmdargs.properties_given){
		properties(&imgInFile1);
	}
	else if(cmdargs.convert_given){
		convert(imgInFile1, cmdargs.outfile_arg[0]);
	}
/*
	else if(cmdargs.union_given){
		filehandler(cmdargs.union_arg, cmdargs.outfile_arg);
	}
	else if(cmdargs.intersect_given){
		filehandler(cmdargs.intersect_arg, cmdargs.outfile_arg);
	}

	// tasklist (ignore)
	// display tree depth, number of nodes, count white & black pixels etc
	// count number of nodes and actual pixels and display size reduction between them
	// check if an image is b/w & 24bit
	// check if image resolution is of power of 2
	// check if image level is greater than 2^20 after log2()
	// github docs image comparision and add sample images to a folder
	// warning: image doesn't meet requirements (optional message args)
	// string pattern match from the end .bmp
	// check time calc once
	// merge all check operations
	// check if gengetopt is installed
	// display ratio of white to black pixels

	// allocate buffer to store the image
	unsigned char (*buffer)[size][3] = malloc(sizeof *buffer);

	// check if malloc succeded in allocating required buffer size
	if(buffer==NULL){

		printf("warning: insufficient memory");
		return 0;
	}

	free(buffer);
*/

	time = clock()-time;

	printf("time taken: %.3fs\n", (double)(time)/CLOCKS_PER_SEC);
	return 0;
}
