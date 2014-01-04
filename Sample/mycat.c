# include <stdio.h>
# include <string.h>
# include <stdlib.h>

unsigned long addr;

void display_file (FILE*, char*);
void display_character (unsigned char);

int main (int argc, char **argv) {
	FILE *fp;

	if (argc == 1) display_file (stdin, "stdin");
	else {
		while (--argc) {
			if (!(strcmp (*++argv, "-"))) {
				display_file (stdin, "-");
				continue;
			}
			if (!(fp = fopen (*argv, "r"))) {
				fprintf (stderr, "%s cannot be opened \n", *argv);
				continue;
			}
			display_file (fp, *argv);
			fclose (fp);
		}
	}
	exit (0);
}

void display_file (fp, file) FILE *fp; char *file; {
	int c;

	addr = 0;
	printf ("====================================================================\n");
	printf ("                           FILE : %s\n", file);
	printf ("====================================================================\n");
	while ((c = getc (fp)) != EOF)
		display_character ((unsigned char) c);
	putchar ('\n');
}

void display_character (c) unsigned char c; {
	static unsigned char collect[8];
	int index;

	index = addr & 7;
	collect [index] = c;
	addr++;
	if (!(addr & 7)) {
		printf ("\n%08lx:", addr);
		for (index = 0; index < 8; index++) {
			if (!(index & 3)) printf (" ");
			printf ("%02x ", collect[index]);
		}
		putchar (' ');
		for (index = 0; index < 8; index++) {
			if (!(index & 3)) printf (" ");
			printf ("%03o ", collect[index]);
		}
		putchar (' ');
		for (index = 0; index < 8; index++) {
			if (collect[index] >= ' ' && collect[index] <= '~') putchar (collect[index]);
			putchar ('.');
		}
	}
}
