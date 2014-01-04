/*=====================================
  C function to read the command line
  =====================================*/

# include <header.h>

char *get_cmd () {
	static char cmd_line[MAX_LINE_SIZE], *line;
	int c;

	line = cmd_line;
	while ((c = getchar ())) {
		if (c == '\n') {
			*line = '\0';
			break;
		}
		if (c == EOF) {
			fprintf (stderr, "Logout\n");
			exit (0);
		}
		*line++ = c;
	}
	return cmd_line;
}
