#include <stdio.h>
#include <time.h>

#include "image.h"
#include "functions.h"

int main(int argc, char** argv){
	clock_t time = clock();

	ARGINFO cmdargs;
	argsCheck(&cmdargs, argc, argv);

	IMGDATA imgInFile1;
	FILE *fOut = NULL, *fIn1 = fopen(cmdargs.infile_arg[0], "rb");
	initImage(fIn1, &imgInFile1, cmdargs.infile_arg[0]);

	if(cmdargs.invert_given || cmdargs.union_given || cmdargs.intersect_given || cmdargs.convert_given){
		fOut = fopen(cmdargs.outfile_arg[0], "wb");
	}

	switch(argsParse(cmdargs)){
		// union and intersect options use a generic handler
		// therefore to circumvent compiler warnings we add a `;` to the case statement
		case 'u': ;
		case 'n': ;
			IMGDATA imgInFile2;
			FILE *fIn2 = fopen(cmdargs.infile_arg[1], "rb");
			initImage(fIn2, &imgInFile2, cmdargs.infile_arg[1]);
			extensionCheck(cmdargs.outfile_arg[0]);
			genericHandler(fIn1, fIn2, fOut, imgInFile1, imgInFile2, cmdargs);
			fclose(fIn2);
			fclose(fOut);
			break;

		case 'r':
			extensionCheck(cmdargs.outfile_arg[0]);
			invertHandler(fIn1, fOut, imgInFile1);
			fclose(fOut);
			break;

		case 'c':
			extensionCheck(cmdargs.outfile_arg[0]);
			convertHandler(fIn1, fOut, imgInFile1);
			fclose(fOut);
			break;

		case 'p':
			deleteTree(propertiesHandler(fIn1, &imgInFile1));
			break;
	}

	fclose(fIn1);
	time = clock()-time;

	printf("time taken: %.3fs\n", (double)(time)/CLOCKS_PER_SEC);
	return 0;
}
