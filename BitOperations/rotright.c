# include <stdio.h>

int main ( int argc, char *argv[] ) {
	int x, n, lsb;
	unsigned int mask = 1 << (sizeof (int) * 8 - 1);

	if (argc != 3) {
		fprintf (stderr, "Usage : rotright <num> <places>\n");
		exit (1);
	}
	sscanf (argv[2], "%d", &x);
	sscanf (argv[3], "%d", &n);
	while (n--) {
		lsb = x & 1;
		x >>= 1;
		if (lsb) x |= mask;
	}
	printf ("%d\n", x);
	return 0;
}
