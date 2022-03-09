#include "tree.h"

#define DINAMIC_DATA

const char *GV = "graph.gv";

branch_t *Branch (branch_t *parent, data_t data) {
	branch_t *branch = calloc (1, sizeof (branch_t));
	branch->data = data;
	branch->parent = parent;
	branch->left = NULL;
	branch->right = NULL;
	return branch;
}

branch_t *Branch_ (branch_t *parent, data_t data, branch_type_t type) {
	branch_t *branch = Branch (parent, data);
	branch->type = type;
	return branch;
}

void RecursiveDestruct (branch_t *branch) {
	if (branch->left != NULL) {
		RecursiveDestruct (branch->left);
		branch->left = NULL;
		// if (branch->left == NULL)
		// 	printf ("\n%d left -> null\n\n", branch->data);
	}
	if (branch->right != NULL) {
		RecursiveDestruct (branch->right);
		branch->right = NULL;
		// if (branch->right == NULL)
		// 	printf ("\n%d right -> null\n\n", branch->data);
	}
	#ifdef DINAMIC_DATA
	free (branch->data);
	#endif

	free (branch);
	return;
}

tree_t *TreeConstruct (tree_t *tree) {
	tree->root = Branch (NULL, NULL);
	tree->size = 0;
	return tree;
}

void TreeDestruct (tree_t *tree) {
	RecursiveDestruct (tree->root);
	tree->root = NULL;
	tree->size = 0;
}

void Graph (FILE *graph, branch_t *branch) {
	if (branch->left != NULL) {
		fprintf (graph, "	\"%s\" -> \"%s\" [label = \"NO\"]\n", branch->data, branch->left->data);
		Graph (graph, branch->left);
	}
	if (branch->right != NULL) {
		fprintf (graph, "	\"%s\" -> \"%s\" [label = \"YES\"]\n", branch->data, branch->right->data);
		Graph (graph, branch->right);
	}
	return;
}

void GVDump (tree_t *tree) {
	FILE *graph = fopen (GV, "w");
	branch_t *branch = tree->root;
	fprintf (graph, "digraph TREE {\n");
	fprintf (graph, "	node [shape = box]\n");
	Graph (graph, branch);
	fprintf (graph, "}\n");
	fclose (graph);
	return;
}

void InsertBranch (branch_t *parent, size_t dir, data_t data) {
	branch_t *tmp;
	if (dir) {
		tmp = parent->right;
		parent->right = Branch (parent, data);
		parent->right->left = tmp;
	}
	else {
		tmp = parent->left;
		parent->left = Branch (parent, data);
		parent->left->left = tmp;
	}
	return;
}
