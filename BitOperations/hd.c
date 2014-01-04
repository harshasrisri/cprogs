# include <stdio.h>

int main ( int argc, char **argv ) {

	if (argc < 2) {
		fprintf (stderr,"Usage : hexdump <filename1> ... <filename_n>\n");
		exit (1);
	}
	while (--argc) {
		FILE *fp; int pos, c;

		fp = fopen (*++argv, "r");
		if (fp == 0) {
			fprintf (stderr,"Error opening file %s\n", *argv);
			continue;
		}
		printf ("\nHex Dump for file %s :", *argv);
		for (pos = 0; (c = getc (fp)) != EOF; pos++) {
			if (!(pos & 15)) printf ("\n%04x ", (unsigned)pos);
			else if (!(pos & 7)) printf ("  ");
			else if (!(pos & 3)) putchar (' ');
			printf ("%02x ", (unsigned char)c);
		}
		printf ("\n\n");
		fclose (fp);
	}
	return 0;
}
