# include <stdio.h>
# include <stdlib.h>
# include "queue.h"
# include <string.h>

int main (int argc, char **argv) {
	QUEUE *qd;
	char line[20], *str;
	int num, nmax;

	if (argc != 2) {
		fprintf (stderr, "Usage:a.out [num | -d]" 
				" where num = size of queue, -d = dynamic\n");
		exit (0);
	}

	if (!strcmp (*++argv, "-d")) nmax = 0;
	else nmax = atoi (*argv);

	if (!(qd = open_queue (sizeof(int), nmax))) {
		fprintf (stderr, "Invalid sizes specified\n");
		exit (1);
	}

	while (1) {
		if (queue_full(qd))
			printf ("d to deQ, e to exit : ");
		else if (queue_empty(qd))
			printf ("int to enQ, e to exit : ");
		else printf ("int to enQ, d to deQ, e to exit : ");

		if (!fgets (line, 20, stdin)) exit (1);
		for (str = line; *str == ' ' || *str == '\t'; str++)
			;

		switch (*str) {
			default : continue;
			case '\n' : continue;
			case '-': case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				num = atoi (str);
				if (enQ (qd, (char*)&num))
					printf ("Queue Full. de-Queue items first.\n");
				break;
			case 'd': case 'D':
				if (deQ (qd, (char*)&num))
					printf ("nothing to de-Queue\n");
				else
					printf ("%d\n", num);
				break;
			case 'e': case 'E':
				if (!queue_empty(qd)) {
					printf ("remaining queue contents : ");
					while (!queue_empty(qd)) {
						deQ (qd, (char*)&num);
						printf ("%d ", num);
					}
				}
				close_queue (qd);
				printf ("\nEnd of program\n");
				exit (0);
		}
	}
}
