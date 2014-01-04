# include <stdio.h>

int main ( int argc, char *argv[] ) {
	int c, n, m, collect = 0, pos = 0;
	char *word; char *malloc(int);

	if (argc != 3) {
		fprintf (stderr, "Usage : a.out <columns> <tabstops>\n");
		exit (1);
	}
	sscanf (argv[1], "%d", &n);
	if (n < 10 || n > 70) {
		fprintf (stderr, "enter sensible number of columns to fold\n");
		exit (2);
	}
	sscanf (argv[2], "%d", &m);
	if (m < 2 || m > 10) {
		fprintf (stderr, "enter sensible number of tabstops\n");
		exit (3);
	}
	word = malloc (n + 1);
	while ((c = getchar ()) != EOF) {
		if (c == '\n') {
			word [collect] = '\0';
			printf ("%s\n", word);
			pos = collect = 0;
			continue;
		}
		if (c == '\t')
			do pos++;
			while (pos%m);
		else pos++;
		if (pos >=n) {
			word [collect] = '\0';
			printf ("%s\n", word);
			pos = collect = 0;
		}
		word [collect++] = c;
	}
	if (collect) {
		word [collect] = '\0';
		printf ("%s\n", word);
	}
	return 0;
}
