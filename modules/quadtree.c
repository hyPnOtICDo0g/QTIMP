#include <stdio.h>
#include <stdlib.h>

#include "quadtree.h"
#include "utilities.h"

// stores the first 20 powers of 2
long long twoPows[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576};

QTREE* createNode(int level, int val){
    QTREE *node = (QTREE*) malloc(sizeof(QTREE));
    if(node == NULL){
        printf("warning: insufficient memory\n");
        exit(1);
    }
    node->value = val;
    node->isLeaf = 1;
    node->level = level;
    node->tl = NULL;
    node->tr = NULL;
    node->bl = NULL;
    node->br = NULL;
    return node;
}

void setPixel(QTREE* node, int x1, int y1, int x2, int y2, int b){

    // sanity check
    if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0 || x2 < x1 || y2 < y1 || x2 >= twoPows[node->level] || y2 >= twoPows[node->level]){
        return;
    }
    // fleck of optimization when setting an entire node
    if (x1 == 0 && y1 == 0 && x2 == (twoPows[node->level]-1) && y2 == x2){
        // no need for post-processing since it is a leaf
        deleteTree(node);
        node->isLeaf = 1;
        node->value = b;
        return;
    }
    else{
        if (node->isLeaf){
            if (node->level==0){
                // change the value if the node is a leaf
                node->value = b;
                return;
            }
            else{
                // create temporary redundant nodes filled with the previous value
                node->tl = createNode(node->level-1, node->value);
                node->tr = createNode(node->level-1, node->value);
                node->bl = createNode(node->level-1, node->value);
                node->br = createNode(node->level-1, node->value);
                // remove leaf status, level remains same
                node->isLeaf = 0;
                node->value = -1;
            }
        }

        int mid = twoPows[node->level-1];

        if (x1 < mid && x2 >= mid && y1 < mid && y2 >= mid){
            // in all four nodes
            setPixel(node->tl, x1, y1, mid-1, mid-1, b);
            setPixel(node->tr, x1, 0, mid-1, y2-mid, b);
            setPixel(node->bl, 0, y1, x2-mid, mid-1, b);
            setPixel(node->br, 0, 0, x2-mid, y2-mid, b);
        }
        else if (x1 < mid && x2 >= mid && y2 < mid){
            // in tl and bl
            setPixel(node->tl, x1, y1, mid-1, y2, b);
            setPixel(node->bl, 0, y1, x2-mid, y2, b);
        }
        else if (x1 < mid && x2 >= mid && y1 >= mid){
            // in tr and br
            setPixel(node->tr, x1, y1-mid, mid-1, y2-mid, b);
            setPixel(node->br, 0, y1-mid, x2-mid, y2-mid, b);
        }
        else if (x2 < mid && y1 < mid && y2 >= mid){
            // in tl and tr
            setPixel(node->tl, x1, y1, x2, mid-1, b);
            setPixel(node->tr, x1, 0, x2, y2-mid, b);
        }
        else if (x1 >= mid && y1 < mid && y2 >= mid){
            // in bl and br
            setPixel(node->bl, x1-mid, y1, x2-mid, mid-1, b);
            setPixel(node->br, x1-mid, 0, x2-mid, y2-mid, b);
        }
        else if (x2 < mid && y2 < mid){
            // in tl
            setPixel(node->tl, x1, y1, x2, y2, b);
        }
        else if (x2 < mid && y1 >= mid){
            // in tr
            setPixel(node->tr, x1, y1-mid, x2, y2-mid, b);
        }
        else if (x1 >= mid && y2 < mid){
            // in bl
            setPixel(node->bl, x1-mid, y1, x2-mid, y2, b);
        }
        else if (x1 >= mid && y1 >= mid){
            // in br
            setPixel(node->br, x1-mid, y1-mid, x2-mid, y2-mid, b);
        }
    }
    postProcess(node);
}

unsigned int getPixel(const QTREE* node, int x1, int y1){
    if (node->isLeaf){
        return node->value;
    }
    else{
        int mid = twoPows[node->level-1];
        if (x1 >= mid){
            if (y1 >= mid){
                return getPixel(node->br, x1-mid, y1-mid);
            }
            else{
                return getPixel(node->bl, x1-mid, y1);
            }
        }
        else{
            if (y1 >= mid){
                return getPixel(node->tr, x1, y1-mid);
            }
            else{
                return getPixel(node->tl, x1, y1);
            }
        }
    }
}

void deleteTree(QTREE* root){
    // check if the root node is not a leaf
    if (!root->isLeaf){
        // recursively traverse the children & free all nodes
        deleteTree(root->tl);
        free(root->tl);
        deleteTree(root->tr);
        free(root->tr);
        deleteTree(root->bl);
        free(root->bl);
        deleteTree(root->br);
        free(root->br);
    }
}

void treeCopy(QTREE** destTree, const QTREE* sourceTree){
    (*destTree) = createNode(sourceTree->level, sourceTree->value);
    // set children as NULL if the source node is a leaf
    if (sourceTree->isLeaf){
        (*destTree)->tr = NULL;
        (*destTree)->tl = NULL;
        (*destTree)->br = NULL;
        (*destTree)->bl = NULL;
    }
    // recursively traverse the children and clone their contents
    else{
        (*destTree)->isLeaf = sourceTree->isLeaf;
        treeCopy(&(*destTree)->tr, sourceTree->tr);
        treeCopy(&(*destTree)->tl, sourceTree->tl);
        treeCopy(&(*destTree)->br, sourceTree->br);
        treeCopy(&(*destTree)->bl, sourceTree->bl);
    }
}

void assignTree(QTREE** root, const QTREE* sourceTree){
    deleteTree(*root);
    treeCopy(root, sourceTree);
}

void postProcess(QTREE* node){
    if(
        !(node->isLeaf) && node->tl->isLeaf && node->tl->value == node->tr->value
        && node->tr->value == node->bl->value && node->bl->value == node->br->value
        && (node->br->value == 0 || node->br->value == 1)
        ){
        // redundant node found
        node->value = node->tl->value;
        deleteTree(node);
        node->isLeaf = 1;
        node->tl = NULL;
        node->tr = NULL;
        node->bl = NULL;
        node->br = NULL;
    }
}

unsigned long totalCount(const QTREE* root){
    if (root == NULL){
       return 0;
    }
    else{
        return 1 + (totalCount(root->tl) + totalCount(root->tr) + totalCount(root->bl) + totalCount(root->br));
    }
}

unsigned long countNodes(const QTREE* root, int val){
    if (root->isLeaf){
        if (root->value == val){
            return 1;
        }
        else{
           return 0;
        }
    }
    else{
        return (countNodes(root->tl, val) + countNodes(root->tr, val) + countNodes(root->bl, val) + countNodes(root->br, val));
    }
}

void overlap(QTREE** T1, const QTREE* T2){
    if ((*T1)->isLeaf){
        if ((*T1)->value == 0){
            // boolean OR with a black pixel is the other pixel
            assignTree(T1, T2);
            return;
        }
        else{
            // it is a white pixel; result will be a white pixel too
            return;
        }
    }
    else if (T2->isLeaf){
        // no change since it is boolean OR with a black pixel
        if (T2->value == 0)
            return;
        else{
            // boolean OR with a white pixel is the other pixel
            assignTree(T1, T2);
            return;
        }
    }
    else{
        // when both are not leaves, recurse on their children
        overlap(&(*T1)->tl, T2->tl);
        overlap(&(*T1)->tr, T2->tr);
        overlap(&(*T1)->bl, T2->bl);
        overlap(&(*T1)->br, T2->br);
    }
    postProcess(*T1);
}

void intersect(QTREE** T1, const QTREE* T2){
    if ((*T1)->isLeaf){
        if ((*T1)->value == 1){
            // boolean AND with a white pixel is the other pixel
            assignTree(T1, T2);
            return;
        }
        else{
            // it is a black pixel; result will be a black pixel too
            return;
        }
    }
    else if (T2->isLeaf){
        // no change since it is boolean AND with a white pixel
        if (T2->value == 1){
            return;
        }
        else{
            // boolean OR with a black pixel is the other pixel
            assignTree(T1, T2);
            return;
        }
    }
    else{
        // when both are not leaves, recurse on their children
        intersect(&(*T1)->tl, T2->tl);
        intersect(&(*T1)->tr, T2->tr);
        intersect(&(*T1)->bl, T2->bl);
        intersect(&(*T1)->br, T2->br);
    }
    postProcess(*T1);
}

void invert(QTREE* root){
    if (root->isLeaf){
        // toggle (XOR)
        root->value ^= 1;
    }
    else{
        invert(root->tl);
        invert(root->tr);
        invert(root->bl);
        invert(root->br);
    }
}

#ifdef DEBUG
#define DEBUG
int main(){
    // create a root node for tree `T1` where level = 3 and value = 0
    QTREE *T1 = createNode(3, 0);

    setPixel(T1,0,1,0,5,1);
    setPixel(T1,1,1,1,1,1);
    setPixel(T1,1,5,1,5,1);
    setPixel(T1,2,1,2,1,1);
    setPixel(T1,2,5,2,5,1);
    setPixel(T1,3,1,3,1,1);
    setPixel(T1,3,5,3,5,1);
    setPixel(T1,4,1,4,5,1);

    getMatrix(T1);
    printf("total: %lu\n", totalCount(T1));
    printf("whites: %lu\n", countNodes(T1, 1));
    printf("blacks: %lu\n\n", countNodes(T1, 0));

    // create a root node for tree `T2` where level = 3 and value = 0
    QTREE *T2 = createNode(3, 0);

    setPixel(T2,2,3,2,3,1);
    setPixel(T2,2,5,3,5,1);
    setPixel(T2,4,1,4,1,1);
    setPixel(T2,4,5,4,5,1);
    setPixel(T2,5,2,5,4,1);

    getMatrix(T2);
    printf("total: %lu\n", totalCount(T2));
    printf("whites: %lu\n", countNodes(T2, 1));
    printf("blacks: %lu\n\n", countNodes(T2, 0));

    // `copy` is a clone of the quadtree `T1` created from the first image
    // a deep copy has been performed to retain the contents of `T1` as-is
    // we use this tree to avoid deep copying of similar nodes from `T2`

    QTREE *copy = NULL;
    treeCopy(&copy, T1);

    // union of T1 (copy) & T2
    overlap(&copy, T2);

    getMatrix(copy);
    printf("total: %lu\n", totalCount(copy));
    printf("whites: %lu\n", countNodes(copy, 1));
    printf("blacks: %lu\n\n", countNodes(copy, 0));

    // complement the union
    invert(copy);

    getMatrix(copy);
    printf("total: %lu\n", totalCount(copy));
    printf("whites: %lu\n", countNodes(copy, 1));
    printf("blacks: %lu\n\n", countNodes(copy, 0));
    return 0;
}
#endif
