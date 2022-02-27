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

void properties(IMGDATA inFile){
	FILE *fIn = fopen(inFile.fileName, "rb");

	filechk(fIn, inFile.fileName);

	// read the 54 byte header from the input file
	fread(inFile.header, sizeof(unsigned char), 54, fIn);

	// check if the file is a valid bitmap
	frmtchk(inFile.fileName, inFile.header);

	// extract the image height, width and bit depth from image header
	inFile.width = *(int*)&inFile.header[18];
	inFile.height = *(int*)&inFile.header[22];
	inFile.bitDepth = *(int*)&inFile.header[28];

	printf("width: %d\n", inFile.width);
	printf("height: %d\n", inFile.height);
	printf("bit depth: %d\n", inFile.bitDepth);

	fclose(fIn);
}

void filechk(FILE* fp, char* fileName){
	if(fp==NULL){
		printf("fatal: '%s' not found\n", fileName);
		exit(1);
	}
}

void frmtchk(char* fileName, unsigned char* fileHeader){
	// use the file header to determine the file format
	if(fileHeader[0]+fileHeader[1]!=0x8f){
		printf("fatal: '%s' is not a bitmap\n", fileName);
		exit(1);
	}
}

void writechk(FILE* fp, char* fileName){
	if(fp==NULL){
		printf("fatal: cannot open '%s'\n", fileName);
		exit(1);
	}
}
