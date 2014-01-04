# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define LINE_SIZE 50

void tail_lines (FILE *fp, int num) {
	char **str;
	int line, j, c, *size;

	printf ( "\n%d lines from %s\n", num, fp == stdin ? "stdin" : "a file" );
	str  = calloc (num, sizeof(char*));
	size = calloc (num, sizeof(int));
	line = j = 0;
	while ((c = fgetc(fp)) != EOF) {
		if (j >= size[line] - 1)
			str[line] = realloc (str[line], size[line] += LINE_SIZE);
		str[line][j++] = c;
		if (c == '\n') {
			str[line][j++] = '\0';
			j = 0;
			line++;
			line %= num;
		}
	}
	for (j = 0; j < num; j++) {
		if ( str[line] ) printf ("%s", str[line]);
		if ( ++line >= num ) line = 0;
	}
	for (j = 0; j < num; j++) 
		free (str[j]);
	free (str);
	free (size);
	printf ("\n===============================\n");
	fclose (fp);
}
//==================================================================
int main (int argc, char **argv) {
	FILE *fp; int num = 5, filesp = 0;

	while (*++argv) {
		if (!strcmp(*argv, "-")) {
			filesp = 1;
			tail_lines (stdin, num);
			continue;
		}
		else if (**argv == '-') {
			num = -atoi (*argv);
			filesp = 0;
			continue;
		}
		else {
			fp = fopen (*argv, "r");
			filesp = 1;
			if (fp == NULL) {
				fprintf (stderr,"\n File %s not found!\n", *argv);
				continue;
			}
			tail_lines (fp, num);
		}
	}
	if (!filesp) tail_lines (stdin, num);
	return 0;
}
//==================================================================
