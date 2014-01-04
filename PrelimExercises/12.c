# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

void tail_lines (int num, FILE *tmp) {
	int c, n = 0, m = 0;

	while ((c = fgetc (tmp)) != EOF)
		if (c == '\n') n++;
	rewind (tmp);
	printf ("\n===================");
	while ((c = fgetc (tmp)) != EOF) {
		if (c == '\n') m++;
		if (m > (n - num - 1)) putchar (c);
	}
}

void readstdin (int num) {
	FILE *fp_stdin;
	int c;

	printf ("Enter text\n");
	fp_stdin = tmpfile ();
	while ((c = getchar ()) != EOF)	fputc (c, fp_stdin);
	rewind (fp_stdin);
	tail_lines ( num, fp_stdin);
	fclose (fp_stdin);
}

int main ( int argc, char **argv ) {
	int i, num = 5, file_specified = 0;
	FILE *fp;

	while (*++argv) {
		if (**argv == '-') {
			if (*++*argv == '\0') {
				readstdin (num);
				file_specified = 1;
			} else num = atoi (*argv);
		} else {
			file_specified = 1;
			fp = fopen (*argv, "r");
			tail_lines (num, fp);
			fclose (fp);
		}
	}
	if (!file_specified) readstdin (num);
	return 0;
}
