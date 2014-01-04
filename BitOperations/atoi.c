# include <stdio.h>

int main ( int argc, char **argv ) {
	int i = 0;

	argv++;
	if (**argv == '-') {
		putchar ('-');
		*++*argv;
	}
	while (**argv) {
		i = (i << 3) + (i << 1) + (**argv - '0');
		*++*argv;
	}
	printf ("%d\n", i);
	return 0;
}
