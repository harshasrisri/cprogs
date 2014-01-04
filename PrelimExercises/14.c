# include <stdio.h>
# include <string.h>

int main ( int argc, char **argv ) {
	FILE *fp;
	char *p;

	fp = fopen (argv[1], "r+");
	while (*p = fgets (*p, strlen(argv[2]) , fp)) if (*p == argv[2]) fputs (argv[3], fp);
	fclose (fp);
	return 0;
}
