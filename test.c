#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum SIZE {
	MAX_LEN = 25,
	BUF_SIZE = 256
};


int main () {
	char *str = (char *) calloc (sizeof (char), MAX_LEN);
	char buf[BUF_SIZE];
	FILE *base = fopen ("base.txt", "r");
	size_t nread = fread (buf, sizeof (char), BUF_SIZE, base);
	printf ("nread = %ld\n", nread);
	for (size_t i = 0; i < nread; i++) {
		// if (buf[i] == '(') {
		// 	i += 2;
		// 	sscanf (buf + i, "%s", str);
		// 	printf ("%s (%ld)\n", str, strlen (str));
		// }
		printf ("%c (%d)\n", buf[i], i);
	}
	exit (EXIT_SUCCESS);
}
