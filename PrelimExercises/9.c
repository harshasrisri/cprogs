# include <stdio.h>
# include <stdlib.h>

char flag_1752 = 0;

void print_cal ( int first, int no_d) {
	int i;
	printf ("---------------------\n");
	printf ("Su Mo Tu We Th Fr Sa \n");
	printf ("---------------------\n");
	for (i = 0; i < first; i++)
		printf ("   ");
	for(i = 1; i <= no_d; i++) {
		if (flag_1752 && i == 3) i = 14;
		if ( (first + i - 1) % 7 == 0 ) printf ("\n");
		printf ("%2d ",i);
	}
	printf ("\n---------------------\n");
}

int no_of_days (int month, int year) {
	int no_d[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

	if ((year % 4) == 0) no_d[1] = 29;
	if ((year % 100) == 0) no_d[1] = 28;
	if ((year % 400) == 0) no_d[1] = 29;
	if ((year == 1752) && (month == 9)) flag_1752 = 1;
	return no_d[month - 1];
}

int first_day (int month, int year) {
	int i, j, nod=4;

	if ( year < 2009 ) {
		for (i = 2008; i >= year; i--)
			for (j = 12; j >= 1; j--) {
				nod = ((nod - no_of_days (j, i)) % 7);
				if (i == year && j == month) break;
			}
		nod = nod + 7;
	}
	else if ( year > 2008 ) {
		for (i = 2009; i <= year ; i++)
			for (j = 1; j <= 12; j++) {
				if (i == year && j == month) break;
				nod = (nod + no_of_days (j, i)) % 7;
			}
	}
	return nod;
}

int main (int argc, char **argv) {
	int month, year;
	
	if (argc==1) {
		fprintf (stderr, "Usage : mycal <month> <year>\n");
		exit (1);
	}

	sscanf (argv[1], "%d", &month);
	sscanf (argv[2], "%d", &year);

	if ( month < 1 || month > 12 || year < 0 ) {
		fprintf (stderr, "Enter valid requirements\n");
		exit(2);
	}
	else print_cal (first_day (month, year), no_of_days (month, year));
	return 0;
}
