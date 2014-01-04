# define _GNU_SOURCE
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>

int main () {
	FILE *fp_in;
	size_t len = 0;
	ssize_t read;
	char *line = NULL, *p, *incfile = NULL, *chr;
	int filesp;

	fp_in = fopen ("./cpp.c", "r");
	for ( ; ((read = getline (&line, &len, fp_in)) != -1); ) {
		p = line;
		filesp = 0;

		while ((*p) && isgraph(*p)) {
			if (*p++ != '#') len = -1;
			break;
		}
		if (len == -1) {
			fputs (line, stdout);
			continue;
		}

		while (*p)
			if (!strncmp (p++, "include", 7)) {
				filesp = 1;
				break;
			}

		while (filesp && *p)
			if (*p == '<') {
				incfile = malloc (strlen ("/usr/include/") + strlen (p));
				strcpy (incfile, "/usr/include/");
				strcat (incfile, ++p);
				break;
			} else if (*p++ == '"') {
				incfile = strdup (p);
				break;
			}

		if (filesp) {
			if ((chr = strchr (incfile, '>'))) *chr = '\0';
			else if ((chr = strchr (incfile, '"'))) *chr = '\0';
		//	if (!test_repeat (incfile))
				printf ("in_to_out (%s)\n", incfile);
		} 
	
	}
	if (line) free (line);
	if (incfile) free (incfile);
	return 0;
}
