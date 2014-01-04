# define _GNU_SOURCE
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

void in_to_out(char *input_file, FILE * fp_out) {
	static char **inclst = NULL;
	static int noi = 0;
	FILE *fp_in;
	char *line = NULL, *p, *chr;
	char *incfile = NULL;
	size_t len = 0;
	ssize_t read;
	int filesp, line_no, cnt;

	if ( !input_file ) {
		while (noi--)
			if (inclst[noi]) free (inclst[noi]);
		free (inclst);
		return;
	}
	if (!(fp_in = fopen (input_file, "r"))) {
		fprintf (stderr, "Error opening %s\n", input_file);
		return;
	}
	for (line_no = 1; ((read = getline (&line,&len,fp_in)) != -1); line_no++) {
		p = line;
		filesp = 0;

		while ((*p) && isgraph(*p)) {
			if (*p++ != '#') len = -1;
			break;
		}

		while (*p)
			if (!strncmp (p++, "include", 7)) {
				filesp = 1;
				break;
			} 
			
		if ((len == -1) || (!filesp)) {
			fputs (line, fp_out);
			continue;
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
			for (cnt = 0; cnt < noi; cnt++)
				if (!strcmp (inclst[cnt], incfile))
					continue;

			inclst = realloc (inclst, ++noi * sizeof (char*));
			inclst[noi-1] = strdup (incfile);
			in_to_out (incfile, fp_out);
		}
	}	
	free (line);
	free (incfile);
	fclose (fp_in);
}

int main (int argc, char *argv[]) {
	int fil_cnt;
	FILE *fp_out;

	if ((argc == 1) || (argc == 2)) {
		fprintf (stderr,
			"Usage: a.out <source file(s)> <destination file>\n");
		exit (1);
	}
	printf ("Are you sure to write output to \"%s\"? (y/n) : ", argv[argc-1]);
	if ((getchar () == 'n') || (getchar () == 'N')) {
		fprintf (stderr, "No operation performed\n");
		return 0;
	}
	if (!(fp_out = fopen (argv[argc-1], "w"))) {
		fprintf (stderr, "Error opening destination file\n");
		exit (2);
	}
	for (fil_cnt = 1; fil_cnt < argc - 1; fil_cnt++)
		in_to_out (argv[fil_cnt], fp_out );
	in_to_out ( NULL, NULL );
	fclose (fp_out);
	printf ("Output file : %s\n", argv[argc-1]);
	return 0;
}
