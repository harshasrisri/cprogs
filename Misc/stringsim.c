# include <stdio.h>
# include <string.h>
# include <stdlib.h>

int stringsim (char *array, int offset) {
	int sum = 0;
	char *p1 = array;
	char *p2 = p1 + offset;

	if (!*p2) return 0;

	/* printf ("%s : ", p2); */

	while (*p2 && *p2 != '\n')
		if (*p1++ == *p2++)
			sum++;
		else break;

	/* printf ("%d\n", sum); */

	return sum + stringsim (array, ++offset);
}

int main (int argc, char **argv) {
	FILE *infile;
	int count;
	char *buf;

	if (!(infile = fopen (argv[1], "r")))
		infile = stdin;

	buf = (char *) malloc (100000);
	buf = fgets (buf, 10, infile);
	count = atoi (buf);

	while (count--) {
		printf ("%d\n", stringsim (buf = fgets (buf, 100000, infile), 0));
	}

	return 0;
}
