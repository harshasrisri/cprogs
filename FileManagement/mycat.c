# include <stdio.h>
# include <string.h>

int main ( int argc, char **argv ) {
	FILE *fp; int verbose = 0, endofline = 0, linecount = 0, c, i;
	
	if (argc == 1) goto label;
	while (*++argv) {
		if (*argv != NULL && !strcmp(*argv, "-v")) {
			verbose = 1;
			continue;
		}
		else if (*argv != NULL && !strcmp(*argv, "-e")) {
			endofline = 1;
			continue;
		}
		else if (*argv != NULL && !strcmp(*argv, "-n")) {
			linecount = 1;
			continue;
		}
		else if (!strcmp (*argv, "-")) {
label :		fp = tmpfile();
			printf ("\nEnter input:\n");
			while ((c = getchar()) != EOF)
				fputc (c, fp);
			rewind (fp);
		}
		else fp = fopen (*argv, "r");
		if (fp == NULL) {
			fprintf (stderr, "\nFile %s not found\n", *argv);
			continue;
		}
		i = 1;
		if (linecount) printf ("%d: ",i);
		while ((c = fgetc (fp)) != EOF ) {
			if (c == ' ' && verbose) {
				putchar ('^');
				c = c + 0x40;
			}
			if (endofline && c == '\n') putchar ('$');
			if (linecount && c == '\n') {
				putchar ('\n');
				printf ("%d: ", ++i);
				continue;
			}
			putchar (c);
		}
		fclose (fp);
		printf ("\n=======================\n");
	}
	return 0;
}
