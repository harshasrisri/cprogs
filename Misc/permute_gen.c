#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int limit;
char *permute;

char *strrev (char *str) {
	char *start, *end, temp;

	start = str; end = str + strlen(str) - 1;

	while (end >= start) {
		temp = *start;
		*start = *end;
		*end = temp;
		start++; end--;
	}

	return str;
}

char *get_next_permute () {
	static int init = 1;
	int k, l, temp;;

	permute[limit] = '\0';

	if (init) {
		temp = 1;
		for (temp = 1; temp <= limit; temp++)
			permute[temp-1] = temp + 'a' - 1;
		init = 0;
		return permute;
	}

	for (k = limit - 2; k >= 0; k--)
		if (permute[k] < permute[k+1])
			break;

	if (k == -1) return NULL;

	for (l = limit - 1; l > k; l--)
		if (permute[l] > permute[k])
			break;

	temp = permute[k];
	permute[k] = permute[l];
	permute[l] = temp;

	strrev(&permute[k+1]);

	return permute;
}


int main (int argc, char **argv) {
	char *board;
	limit = atoi (argv[1]);
	permute = (char *) malloc (limit + 1);

	while ((board = get_next_permute())) {
		printf ("%s\n", board);
	}
	return 0;
}
