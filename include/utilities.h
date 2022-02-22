#ifndef UTILITIES_H
#define UTILITIES_H

// check if arguments follow the documented syntax
void argschk(int argc, char **argv);

// check if a file exists on the disk
void filechk(FILE* fp);

// check if a file is a bitmap
void frmtchk();

// check if the program has permission to write to disk
void writechk(FILE* fp);

#endif
