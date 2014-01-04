# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define NMAX 25
# define check if(!items){printf ("No items in List\n");continue;}

char flag[NMAX] = {};

void sort_n_print (int *list, int size) {
	int i, j, tmp;

	for (i = 0; i < size; i++)
		for (j = 0; j < size-i; j++)
			if (list[j] > list[j+1]) {
				tmp = list[j];
				list[j] = list[j+1];
				list[j+1] = tmp;
				tmp = flag[j];
				flag[j] = flag[j+1];
				flag[j+1] = tmp;
			}
	for (i = 0 ; i <= size; i++) {
		if (flag[i]) continue;
		printf ("%d ",list[i]);
	}
	putchar ('\n');
}

int main () {
	int list[NMAX]={}, num, items = 0, i, *ptr, size = 0;
	char line[20], *str; 

	printf ("Type \'help\' if required\n");
	while (1) {
		printf ("list> ");

		fgets (line, 20, stdin);
		for (str = line; *str == ' ' || *str == '\t'; str++)
			;
		if (!strncmp (str, "help", 4)) {
			printf ("Type <num> to add to list\n"
					"r<num> to remove <num> from list\n"
					"\'s\' sort in ascending order\n"
					"\'p\' to take a peek at list\n"
					"\'f\' to take a peek at flags\n"
					"\'e\' to sort, print and exit\n");
			continue;
		} 
		switch (*str) {
			default : printf ("Invalid operation!\n");
			case '\n' : continue;
			case 'r' :
				check;
				  if ((num =  atoi(++str)))
					for (i = 0; i < size; i++)
						if (num == list[i]) {
							ptr = &list[i];
							list[i] = 0;
							flag[ptr-list] = 1;
							--items;
							printf ("%d removed\n", num);
							break;
						}
				break;
			case '1' : case '2' : case '3' : case '4' : case '5' : 
			case '6' : case '7' : case '8' : case '9' : case '0' : 	
				if (items == NMAX) {
					printf ("List full, remove items first\n");
					continue;
				}
				i = num = atoi (str);
				for (ptr = list; ptr - list < size; ptr++)
					if (flag[ptr-list] == 1) {
						*ptr = num;
						flag[ptr-list] = 0;
						i = 0;
						break;
					}
				if (i == num) {
					list[size++] = num;
				}
				items++;
				break;
			case 's' :
				check;
				sort_n_print (list, size-1);
				break;
			case 'p' :
				check;
				for (i = 0; i < size; i++) if(!flag[i]) printf ("%d ",list[i]);
				putchar ('\n');
				break;
			case 'f' :
				check;
				for (i = 0; i < size; i++) printf ("%d ",flag[i]);
				putchar ('\n');
				break;
			case 'e' :
				if (items) 
					printf ("Remaining list elements in ascending order : ");
				sort_n_print (list, size-1);
				printf ("===>End of App<===\n");
				exit (0);
		}
	}
}
