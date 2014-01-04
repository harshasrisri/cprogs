# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

int main ( int argc, char **argv ) {
	int fp, j, i, n;
		char buf;

	if (argc == 1) {
		fprintf (stderr, "Usage: minicat <filename(s)>");
		exit(1);
	}
		fp = open (*++argv, O_RDONLY);
		if (fp == -1) {
			fprintf (stderr, "\nFile %s not found\n", *argv);
			exit (2);
		}
		for (i = 0; i < BUFSIZ; i++) {
			n = read (fp, &buf, 1);
			if (n > 0)
			putchar (buf);
		}
		close (fp);
		printf ("\n=======================\n");
	return 0;
}
