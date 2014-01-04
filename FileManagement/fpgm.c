# include <stdio.h>

int main () {
	FILE *fp; int i;

	fp = tmpfile();
	for (i = 0; i < 10000; i++)
		fputc ('c', fp);
	fclose (fp);
	return 0;
}
