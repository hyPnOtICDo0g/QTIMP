#ifndef STRUCT_QUADTREE_H
#define STRUCT_QUADTREE_H

/*
    C Implementation of Operations on Region Quadtrees for handling binary images
    Based on C++ Implementation by Harshit Varma: https://github.com/hrshtv/Region-Quadtrees-for-Images
*/

// struct definition for a node in a quadtree
typedef struct QT{
    int value; // set to -1 if a node is a root node else 0 or 1; 0 is black & 1 is white
    int isLeaf; // to determine if a node is leaf; operations can be carried out using `value` but this makes the code more readable
    int level; // 2^level * 2^level is the size of the submatrix stored by a node; not the standard tree level
    struct QT* tr; // top-right
    struct QT* tl; // top-left
    struct QT* bl; // bottom-left
    struct QT* br; // bottom-right
} QTREE;

// create a node with a level and pixel value
QTREE* __create_node(int level, int val);

// set all pixels in the sub-matrix with rows x1 to x2 and columns y1 to y2 to the value b
void __set_pixel(QTREE* node, int x1, int y1, int x2, int y2, int b);

// return the value of the pixel stored in a specific node
unsigned int __get_pixel(const QTREE* node, int x1, int y1);

// traverse the quadtree and get the matrix equivalent
void __get_matrix(const QTREE* root);

// delete a tree by recursively freeing nodes at each level
void __delete_tree(QTREE* root);

// deep copy a source tree and return the destination tree (clone)
void __tree_copy(QTREE** dest_t, const QTREE* source_t);

// assigns a new tree to `root` by deleting it and cloning `source_t`
void __assign_tree(QTREE** root, const QTREE* source_t);

// trim down redundant nodes, if any
void __post_process(QTREE* node);

// count the number of nodes in a quadtree
unsigned long long __count_nodes(const QTREE* root);

// pixelwise boolean OR (union)
void overlap(QTREE** T1, const QTREE* T2);

// pixelwise boolean AND (intersection)
void intersect(QTREE** T1, const QTREE* T2);

// toggle pixel values of each node in a quadtree
void complement(QTREE* root);

#endif
