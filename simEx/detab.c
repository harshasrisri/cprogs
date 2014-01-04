# include <stdio.h>

int main ( int argc, char *argv[] ) {
	int c, n = 0, tabstop;
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
		n++;
		if (c == '\n') n = 0;
		if (c == '\t')
			for (putchar (' '); n % tabstop > 0; n++) putchar (' ');
		else putchar (c);
	}
	return 0;
}
