#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "image.h"
#include "quadtree.h"
#include "utilities.h"

#ifdef DEBUG
#define DEBUG
int main(int argc, char** argv){

	clock_t time = clock();

	argsCheck(argc, argv);

	IMGDATA imgInFile1;
	initImage(&imgInFile1, cmdargs.infile_arg[0]);

	if(cmdargs.properties_given){
		imgProperties(&imgInFile1);
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
	// github docs image comparision and add sample images to a folder
	// check time calc once
	// check if gengetopt is installed
	// may not work on 24bit images with colortable
	// remove all globals and use function restrcited file pointers if required
	// check deletetree
	// check size reduction for 2x2 image

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
#endif
