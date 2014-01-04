#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 20

int *id;
char *sz;

int root (int i) {
	while (i != id[i]) i = id[i];
	return i;
}

int main () {
	int N, i, j, c;
	char *temp,buf[BUFSZ];

	fgets (buf, BUFSZ, stdin);
	N = atoi (buf);

	id = (int *) malloc (N * sizeof(int));
	sz = (char *) malloc (N * sizeof(char));

	for (c = 0; c < N; c++) {
		id[c] = c;
		sz[c] = 1;
	}

	while (*(char *)fgets(buf, BUFSZ, stdin) != (char)'-') {
		i = root (atoi (buf));
		temp = strchr (buf, ',');
		j = root (atoi (++temp));

		if (sz[i] < sz[j]) {id[i] = j; sz[j] += sz[i]; }
		else  {id[j] = i; sz[i] += sz[j]; }
	}

	while (fgets (buf, BUFSZ, stdin) != NULL) {
		i = root (atoi (buf));
		temp = strchr (buf, ',');
		j = root (atoi (++temp));

		putchar ((i == j) ? '1' : '0');
	}
	return 0;
}
