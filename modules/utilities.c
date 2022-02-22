#include <stdio.h>
#include <stdlib.h>

#include "quadtree.h"
#include "cmdline.h"
#include "utilities.h"

void argschk(int argc, char **argv){

	if (
        (cmdline_parser(argc, argv, &cmdargs) != 0 || argc == 1 || !(cmdargs.union_given || cmdargs.outfile_given || cmdargs.properties_given || cmdargs.intersect_given))
		    // --outfile requires --union or --intersect
		|| (!(cmdargs.intersect_given || cmdargs.union_given) && cmdargs.outfile_given)
		    // --properties requires only 1 argument and 0 flags
        || ((cmdargs.outfile_given || cmdargs.union_given || cmdargs.intersect_given) && cmdargs.properties_given)
        ){
            printf("Usage: %s [OPTION]...\nTry '%s --help' for more information.\n", argv[0], argv[0]);
            exit(1);
    }
}

void filechk(FILE* fp){

	if(fp==NULL){

		printf("fatal: file does not exist\n");
		exit(1);
	}
}

void frmtchk(){

	// check if the given file is a bitmap
	if(header[0]+header[1]!=0x8f){

		printf("fatal: not a bitmap\n");
		exit(1);
	}
}

void writechk(FILE* fp){

	if(fp==NULL){
		printf("fatal: cannot open file\n");
		exit(1);
	}
}
