# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "tree.h"

void add_to_total (char *data, void *app_data) {
	*(int *)app_data += *(int *)data;
}

int find_total (TREE *td) {
	int total = 0;
	void add_to_total (char *, void*);
	navigate (td, add_to_total, (void *)&total);
	return total;
}

void print_leaf (char *data) {
	printf ("%d ", *(int *)data);
}

void print_tree (TREE *td) {
	int num;
	void print_leaf (char *);
	navigate (td, print_leaf, (void *)&num);
	printf ("\nNumber of leaves : %d\n", nleaves(td));
}

int compare_int (char *a, char *b) {
	return (*(int *)a - *(int *)b);
}

int main () {
	TREE *td;
	char line[50], *s;
	int num = 0;

	if (!(td = open_tree (sizeof(int), compare_int))) {
		fprintf (stderr, "Error creating tree\n");
		exit (1);
	}

	printf ("Type h/?/H for help\n");
	while (1) {
		printf ("tree> ");
		fgets (line, 50, stdin);

		for (s = line; *s == ' ' || *s == '\t'; s++)
			;

		switch (*s) {
			case '\n' :
				break;
			default : 
				printf ("Invalid Command\n");
				break;
			case 'h' : case '?' : case 'H' :
				printf ("List of commands :\n"\
						"<num> - add <num> to tree\n"\
						"p - print sorted tree\n"\
						"t - print total of all nodes\n"\
						"r<num> - remove <num> if number present\n"\
						"f<num> - check if <num> present in tree\n"\
						"e - Exit\n");
				break;
			case 'p' : case 'P' :
				print_tree (td);
				break;
			case '1' : case '2' : case '3' : case '4' : case '5' : 
			case '6' : case '7' : case '8' : case '9' : case '0' : 
				num = atoi (s);
				add_leaf (td, (char *) (&num));
				break;
			case 't' : case 'T' :
				printf ("Total of all nodes is %d\n", find_total (td));
				break;
			case 'f' : case 'F' :
				for (s++; *s == ' ' || *s == '\t'; s++)
					;
				if (*s == '\n') break;
				num = atoi (s);
				if (find_leaf (td, (char *) (&num)))
					printf ("%d found\n", num);
				else printf ("%d not found\n", num);
				break;
			case 'r' : case 'R' :
				for (s++; *s == ' ' || *s == '\t'; s++)
					;
				if (*s == '\n') break;
				num = atoi (s);
				if (remove_leaf (td, (char *) (&num)))
					printf ("%d removed\n", num);
				else printf ("%d not found\n", num);
				break;
			case 'e' : case 'E' :
				print_tree(td);
				free_tree (Root);
				exit (0);
		}
	}
}
