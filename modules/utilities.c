#include <stdio.h>
#include <stdlib.h>

#include "cmdline.h"
#include "image.h"
#include "utilities.h"

void argschk(int argc, char **argv){

	if (
        (cmdline_parser(argc, argv, &cmdargs) != 0 || argc == 1 || !(cmdargs.union_given || cmdargs.outfile_given || cmdargs.properties_given || cmdargs.intersect_given))
		    // --outfile requires either --union or --intersect
		|| (!(cmdargs.intersect_given || cmdargs.union_given) && cmdargs.outfile_given)
		    // --properties requires only 1 argument and 0 flags
        || ((cmdargs.outfile_given || cmdargs.union_given || cmdargs.intersect_given) && cmdargs.properties_given)
            // either pass --union or --intersect but not both
        || (cmdargs.union_given && cmdargs.intersect_given)
        ){
            printf("Usage: %s [OPTION]...\nTry '%s --help' for more information.\n", argv[0], argv[0]);
            exit(1);
    }
}

void properties(char* inFile){
	FILE *fIn = fopen(inFile, "rb");

	filechk(fIn, inFile);

	// read the 54 byte header from the input file
	fread(header, sizeof(unsigned char), 54, fIn);

	frmtchk(inFile);

	// extract the image height, width and bit depth from image header
	width = *(int*)&header[18];
	height = *(int*)&header[22];
	bitDepth = *(int*)&header[28];

	printf("width: %ld\n", width);
	printf("height: %ld\n", height);
	printf("bit depth: %d\n", bitDepth);

	fclose(fIn);
}

void filechk(FILE* fp, char* file){
	if(fp==NULL){
		printf("fatal: \"%s\" does not exist\n", file);
		exit(1);
	}
}

void frmtchk(char* file){
	// use the file header to determine it's format
	if(header[0]+header[1]!=0x8f){
		printf("fatal: \"%s\" is not a bitmap\n", file);
		exit(1);
	}
}

void writechk(FILE* fp, char* file){
	if(fp==NULL){
		printf("fatal: cannot open \"%s\"\n", file);
		exit(1);
	}
}
