#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "image.h"
#include "functions.h"

void genericHandler(FILE* fIn1, FILE* fIn2, FILE* fOut, IMGDATA imgInFile1, IMGDATA imgInFile2, ARGINFO cmdargs){
    QTREE *imageOne = propertiesHandler(fIn1, &imgInFile1);
    QTREE *imageTwo = propertiesHandler(fIn2, &imgInFile2);

    // check if the two images are of same resolution
    if(imgInFile1.size != imgInFile2.size){
        printf("fatal: dimensions of '%s' and '%s' are incompatible\n", imgInFile1.fileName, imgInFile2.fileName);
        deleteTree(imageOne);
        deleteTree(imageTwo);
        remove(cmdargs.outfile_arg[0]);
        exit(1);
    }

    if(cmdargs.union_given){
        overlap(&imageOne, imageTwo);
    }
    else{
        intersect(&imageOne, imageTwo);
    }

    if(cmdargs.invert_given){
        invert(imageOne);
    }

    fwrite(imgInFile1.header, sizeof(unsigned char), 54, fOut);
    writeMatrix(imageOne, fIn1, fOut, imgInFile1.padding);
    deleteTree(imageOne);
    deleteTree(imageTwo);
}

void invertHandler(FILE* fIn, FILE* fOut, IMGDATA imgInFile){
    printf("Inverting...\n");
    QTREE* root = propertiesHandler(fIn, &imgInFile);
    invert(root);
    fwrite(imgInFile.header, sizeof(unsigned char), 54, fOut);
    writeMatrix(root, fIn, fOut, imgInFile.padding);
    printf("Done.\n");
    deleteTree(root);
}

void convertHandler(FILE* fIn, FILE* fOut, IMGDATA imgInFile, char* outFile){
    imgProperties(&imgInFile);
    printf("Converting...\n");
    convert(fIn, fOut, imgInFile);
    printf("Done.\n");
}

QTREE* propertiesHandler(FILE* fIn, IMGDATA* imgInFile){
    // check if the image meets documented requirements
    imgProperties(imgInFile);
    imageCheck(*imgInFile);

    // allocate memory for a root node if all checks pass
    QTREE *root = createNode(log2(imgInFile->width), 0);
    constructQuadTree(root, fIn, imgInFile);
    printProperties(*imgInFile, root);
    printf("\n");
    return root;
}
