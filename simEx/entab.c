# include <stdio.h>

int main ( int argc, char *argv[] ) {
	int c, tabstop, in_pos = 0, out_pos = 0;
	if (argc != 2) {
		fprintf (stderr, "Usage : a.out <tabstop>\n");
		exit (1);
	}
	sscanf (argv[1], "%d", &tabstop);
	if (tabstop < 2 || tabstop > 10) {
		fprintf (stderr, "Enter valid tabstop range\n");
		exit (2);
	}
	while ((c = getchar ()) != EOF) {
		if (c == '\n') {
			in_pos = out_pos = 0;
			putchar (c);
			continue;
		}
		if (c == ' ') in_pos++;
		else if (c == '\t') 
			do in_pos++;
			while (in_pos % tabstop);
		else {
			while (out_pos < (in_pos/tabstop)*tabstop) {
				putchar ('\t');
				do out_pos++;
				while (out_pos % tabstop);
			}
			while (out_pos < in_pos) {
				out_pos++;
				putchar(' ');
			}
			putchar (c);
			in_pos++;
			out_pos++;
		}
	}
	return 0;
}
