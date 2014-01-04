# include <stdio.h>
# include <stdlib.h>

int main (int argc, char **argv) {

	while (*++argv) {
		FILE *fp;
		int num=0, size=0;
		char *str = NULL;

		if (!(fp = fopen (*argv, "r"))) {
			fprintf (stderr, "file %s not found\n", *argv);
			continue;
		}
		fprintf (stdout, "======== Start of file %s ==========\n", *argv);
		fseek (fp, 0, SEEK_END);
		while (!(fseek(fp, -2, SEEK_CUR))) {
			if (num >= size-1) str = realloc (str, size += 50);
			if (((str[num++] = fgetc(fp)) == '\n') || (ftell(fp) == 1)) {
				if (ftell(fp) == 1)
					str[num++] = '\n';
				while (num) putchar (str[--num]);	
			}
		}
		putchar ('\n');
		free (str);
		fclose(fp);
		fprintf (stdout, "======== End of file %s ==========\n\n\n", *argv);
	}
	return 0;
}	
