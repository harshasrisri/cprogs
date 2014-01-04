# include <stdio.h>

int main () {
	int c, in_com = 0, in_str = 0, slash = 0, star = 0;

	while ((c = getchar ()) != EOF) {
		if (in_str) {
			if (c == '"' && !slash) {
				in_str = 0;
				putchar (c);
			}
			if (c== '/') slash = 1;
			else slash = 0;
			if (c == '\n') 
				fprintf (stderr, "\nString running into multiple lines\n");
			putchar (c);
			continue;
		}
		if (c == '"') {
			in_str = 1;
			slash = 0;
			putchar (c);
			continue;
		}
		if (in_com) {
			if (c == '/' && star) in_com = 0;
			else if (c == '*') star = 1;
			else star = 0;
			continue;
		}
		if (c == '*' && slash) {
			in_com = 1;
			slash = 0;
			star = 0;
			continue;
		}
		if (slash) putchar ('/');
		if (c == '/') slash = 1;
		else {
			putchar (c);
			slash = 0;
		}
	}
	if (in_com || in_str) {
		fprintf (stderr, "\nInvalid termination of string or comment\n");
		exit (1);
	}
	return 0;
}
