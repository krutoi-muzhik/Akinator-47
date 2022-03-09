#include "tree.h"

int main () {
	tree_t tree;
	TreeConstruct (&tree);

	tree.root->data = "Живой?";
	tree.root->left = Branch (tree.root, "Стол");
	tree.root->right = Branch (tree.root, "Человек?");
	tree.root->right->left = Branch (tree.root->right, "Собака");
	//printf ("%d\n", tree.root->right->left->data);
	tree.root->right->right = Branch (tree.root->right, "Блондин?");
	//printf ("%d\n", tree.root->right->right->data);
	tree.root->right->right->left = Branch (tree.root->right->right, "Макс");
	tree.root->right->right->right = Branch (tree.root->right->right, "Димас");


	GVDump (&tree);

	TreeDestruct (&tree);

	exit (EXIT_SUCCESS);
}