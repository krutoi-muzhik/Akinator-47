#ifndef TREE_H

#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define POISON "BOOBA"

typedef char * data_t;

typedef enum TYPES {
	FEATURE,
	ELEMENT
} branch_type_t;

typedef struct branch {
	data_t data;
	struct branch *right;
	struct branch *left;
	struct branch *parent;
	branch_type_t type;
} branch_t;

typedef struct tree {
	branch_t *root;
	size_t size;
} tree_t;

typedef enum ERRORS {
	NICE_TREE,
	INVALID_SIZE
} tree_error_t;

branch_t *Branch (branch_t *parent, data_t data);
branch_t *Branch_ (branch_t *parent, data_t data, branch_type_t type);
void RecursiveDestruct (branch_t *branch);
tree_t *TreeConstruct (tree_t *tree);
void TreeDestruct (tree_t *tree);
void Graph (FILE *graph, branch_t *branch);
void GVDump (tree_t *tree);
void InsertBranch (branch_t *parent, size_t dir, data_t data);

#endif
