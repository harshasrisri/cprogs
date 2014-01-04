# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "aqueue.h"

# define SHORT 0
# define LONG 1
# define DOUBLE 2

struct Short {
	char type;
	short num;
} Short;

struct Long {
	char type;
	long num;
} Long;

struct Double {
	char type;
	double num;
} Double;

union data {
	char type;
	struct Short Short;
	struct Long Long;
	struct Double Double;
};

union data data;

void deQ (AQUEUE *aqd) {

	if (deQa (aqd, (char *) &data)) {
		fprintf (stderr, "Nothing to deQ\n");
		return;
	} else {
		putchar (data.type);
		if (data.type == SHORT)
			printf ("%d \n", data.Short.num);
		else if (data.type == LONG)
			printf ("%ld \n", data.Long.num);
		else if (data.type == DOUBLE)
			printf ("%lf \n", data.Double.num);
	}
	return;
}

# define MAX_BYTES 1000

int main () {
	AQUEUE *aqd;
	char line[20], *str;

	if (!(aqd = openQa (MAX_BYTES))) {
		fprintf (stderr, "some error\n");
		exit (1);
	}

	while (1) {
		if (Nfree < (sizeof (short) + 1))
			printf ("p to deQ, e to exit: ");
		else if (Nfree == Nbytes)
			printf ("num to enQ, e to exit: ");
		else printf ("num to enQ, p to deQ, e to exit: ");

		if (!fgets (line, 20, stdin)) exit (2);
		for (str = line; *str == ' ' || *str == '\t'; str++)
			;

		switch (*str) {
			case '\n' : default : continue;
			case 'S' :
			case 's' :	Short.type = SHORT;
						Short.num = atoi (++str);
						if (enQa (aqd, (char *) &Short, sizeof (short)))
							fprintf (stderr, "Q full\n");
						break;
			case 'L' :
			case 'l' :	Long.type = LONG;
						Long.num = atoi (++str);
						if (enQa (aqd, (char*)&Long, sizeof (long)))
							fprintf (stderr, "Q full\n");
						break;
			case 'D' :
			case 'd' :	Double.type = DOUBLE;
						Double.num = (double) atof (++str);
						if (enQa (aqd, (char*)&Double, sizeof (double)))
							fprintf (stderr, "Q full\n");
						break;
			case 'P' :
			case 'p' :	deQ (aqd);
						break;
			case 'E' :
			case 'e' :	while (Nfree < Nbytes)
							deQ (aqd);
						closeQa (aqd);
						printf ("===> End of App <===\n");
						exit (0);
		}
	}
}
