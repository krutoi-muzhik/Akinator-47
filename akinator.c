#include "akinator.h"
#include "Tree/tree.h"

const char *base = "base.txt";

enum SIZES {
	BUF_SIZE = 1024,
	STR_LEN = 20
};

enum ANSWER {
	Q_TRUE = 1,
	Q_FALSE = 2,
	E_TRUE = 3,
	E_FALSE = 4,
	UNKNOWN_ANS = 5
};

enum GAMEOVER {
	ERROR = 2,
	WIN = 1,
	LOSE = 0
};

enum ANS {
	YES = 1,
	NO = 0,
	START = -1
};

void WriteBase (FILE *base, branch_t *branch, size_t depth) {
	for (size_t i = 0; i < depth; i++) {
		fprintf (base, "\t");
	}
	if (branch->type == FEATURE)
		fprintf (base, "?");
	fprintf (base, "%s", branch->data);

	if (branch->type == FEATURE) {
		fprintf (base, " (\n");
		if (branch->right != NULL) {
			WriteBase (base, branch->right, depth + 1);
		} else
			fprintf (base, "\nERROR %s->right == NULL\n\n", branch->data);

		for (size_t i = 0; i < depth + 1; i++) { fprintf (base, "\t"); }
		fprintf (base, ") {\n");

		if (branch->left != NULL) {
			WriteBase (base, branch->left, depth + 1);
		} else
			fprintf (base, "\nERROR %s->left == NULL\n\n", branch->data);

		for (size_t i = 0; i < depth + 1; i++) { fprintf (base, "\t"); }
		fprintf (base, "}\n");
		return;
	} else if (branch->type == ELEMENT) {
		fprintf (base, "\n");
		return;
	}
	fprintf (base, "%s unknown branch type\n", branch->data);
	return;
}

void SaveBase (const char *pathname, tree_t* tree) {
	FILE *base = fopen (pathname, "w");
	fprintf (base, "AKINATOR 47 by krutoi_muzhik crated this base\n");
	fprintf (base, "[\n");
	WriteBase (base, tree->root, 0);
	fprintf (base, "]");
	fclose (base);
	return;
}

size_t ReadBase (char *buf, branch_t *branch, size_t nread) {
	if (branch->data != NULL) {
		printf ("Tree is already filled\n");
		return 0;
	}
	size_t len = 0;
	char *str = (char *) calloc (sizeof (char), STR_LEN);
	if (buf[0] == '?') {
		branch->type = FEATURE;
		len++;
	} else {
		branch->type = ELEMENT;
	}
	sscanf (buf + len, "%s", str);
	branch->data = str;
	len += strlen (str);
	if (branch->type == FEATURE) {
		branch->right = Branch (branch, NULL);
		while (!isalpha(buf[len]) && (buf[len] != '?'))
			len++;
		len += ReadBase (buf + len, branch->right, nread - len);
		branch->left = Branch (branch, NULL);
		while (!isalpha(buf[len]) && (buf[len] != '?'))
			len++;
		len += ReadBase (buf + len, branch->left, nread - len);
	}
	return len;
}

void OpenBase (const char *pathname, tree_t *tree) {
	if ((tree == NULL) || (tree->root == NULL)) {
		printf ("Tree not created\n");
		return;
	}
	FILE *base = fopen (pathname, "r+");
	char buf[BUF_SIZE];
	size_t nread = fread (buf, sizeof (char), BUF_SIZE, base);
	// printf ("%s\n", buf);
	if (!nread) {
		printf ("The file %s is empty\n", pathname);
		return;
	}
	size_t i = 0;
	while ((buf[i] != '[') && (i < nread))						//skip introduction till the base
		i++;
	if (i == nread) {
		printf ("invalid file\n");
	}
	i++;														//now buf[i] = '['
	while (isspace (buf[i]))
		i++;													//now buf[i] -> first element
	printf ("%c %c\n", *(buf + i), buf[i]);
	size_t len = ReadBase (buf + i, tree->root, nread - i);
	printf ("nread = %ld, len = %ld\n", nread, len);
	fclose (base);
	return;
}

int Ask (branch_t *branch) {
	char *answer = (char *) calloc (STR_LEN, sizeof (char));
	if (branch->type == FEATURE) {
		printf ("Is that %s?\n", branch->data);
		scanf ("%s", answer);

		if (!strcmp (answer, "Yes") || !strcmp (answer, "yes"))
			return Q_TRUE;
		if (!strcmp (answer, "No") || !strcmp (answer, "no"))
			return Q_FALSE;

		return UNKNOWN_ANS;
	} else {
		printf ("That is %s am I right?\n", branch->data);
		scanf ("%s", answer);

		if (!strcmp (answer, "Yes") || !strcmp (answer, "yes"))
			return E_TRUE;
		if (!strcmp (answer, "No") || !strcmp (answer, "no"))
			return E_FALSE;

		return UNKNOWN_ANS;
	}
}

int Guess (branch_t *branch) {

	int ans = Ask (branch);
	if (ans == Q_TRUE)
		return Guess (branch->right);

	if (ans == Q_FALSE)
		return Guess (branch->left);

	if (ans == E_TRUE) {
		printf ("Oh I won Yahooo I didn't expect that\n");
		return WIN;
	}

	if (ans == E_FALSE) {
		char *answer = (char *) calloc (STR_LEN, sizeof (char));
		char *feature = (char *) calloc (STR_LEN, sizeof (char));

		printf ("\nIt seems like you know much more than I do\n");
		printf ("Tell me, who did you guess?\n");
		scanf ("%s", answer);
		// char *answer = GetStr ();
		printf ("\nWhats the differense between [%s] and [%s]?\n", branch->data, answer);
		scanf ("%s", feature);
		// char *feature = GetStr ();
		printf ("\nOK I'll remember it\n");

		branch_t *tmp = Branch_ (branch->parent, feature, FEATURE);
		if (branch->parent->right == branch) {
			branch->parent->right = tmp;
			branch->parent = tmp;
			tmp->right = Branch_ (tmp, answer, ELEMENT);
			tmp->left = branch;

			return LOSE;
		}
		if (branch->parent->left == branch) {
			branch->parent->left = tmp;
			branch->parent = tmp;
			tmp->right = Branch_ (tmp, answer, ELEMENT);
			tmp->left = branch;

			return LOSE;
		}
	}
	return ERROR;
}

void Game (tree_t *tree) {
	printf ("Oh Hello There, I am AKINATOR 47\n");
	printf ("If don't know what to do with me ask krutoi_muzhik\n");
	if (tree->root->data == NULL) {
		printf ("WTF the base is empty, type 3 things in this order:\n");
		printf ("Characteristic, subject corresponding to it, the opposite one\n");
		char *feature = (char *) calloc (STR_LEN, sizeof (char));
		char *elem1 = (char *) calloc (STR_LEN, sizeof (char));
		char *elem2 = (char *) calloc (STR_LEN, sizeof (char));
		scanf ("%s %s %s", feature, elem1, elem2);
		tree->root->data = feature;
		tree->root->type = FEATURE;
		tree->root->right = Branch_ (tree->root, elem1, ELEMENT);
		tree->root->left = Branch_ (tree->root, elem2, ELEMENT);
	}
	int result;
	char *ans = (char *) calloc (STR_LEN, sizeof (char));
	do {
		printf ("\nOK LESS GOOO\n\n");
		result = Guess (tree->root);
		if (result == ERROR) {
			printf ("ERROROROROR\n\n");
			return;
		}
		if (result == LOSE) {
			tree->size++;
		}
		printf ("Do you want to play one more time?\n");
		scanf ("%s", ans);
	} while (!strcmp (ans, "Yes") || !strcmp (ans, "yes"));
	free (ans);
}

int main () {
	tree_t tree;
	TreeConstruct (&tree);
	OpenBase ("base.txt", &tree);
	Game (&tree);
	GVDump (&tree);
	// SaveBase ("base.txt", &tree);
	TreeDestruct (&tree);
	exit (EXIT_SUCCESS);
}