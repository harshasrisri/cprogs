# include <stdio.h>

int main ( int argc, char *argv[] ) {
	int n, c, m=0;

	sscanf (argv[1], "%d", &n);
	while ((c = getchar ()) != EOF) {
		if (m >= n) {
			putchar ('\n');
			m = 0;
		} else if (c == '\n') m = 0;
		else if (c == '\t')
			do m++;
			while (m%4);
		putchar (c);
		m++;
	}
	return 0;
}
