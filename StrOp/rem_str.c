# include <stdio.h>
# include <stdlib.h>

int main (int argc, char **argv) {
	int c, *flag, *pos, delim, num, i, j;
	char **sub, temp[50];
	FILE *fp;

	fprintf (stdout, "Enter the number of substrings : ");
	fscanf (stdin, "%d", &num);
	sub = calloc (num, sizeof (char*));
	flag = calloc (num, sizeof (int));
	pos = calloc (num, sizeof (int));

	for (i = 0; i < num; i++) {
		fprintf (stdout, "Enter sub-string %d: ", i+1);
		if (!i) getchar();
		while ((c = fgetc(stdin))) {
			if (!(pos[i] % 10)) sub[i] = realloc (sub[i], pos[i] + 10);
			if (c == '\n') {
				sub[i][pos[i]] = '\0';
				pos [i] = 0;
				break;
			}
			else sub[i][pos[i]++] = c;
		}
	}

	if (argc == 1) {
		fprintf (stdout, "Main String : ");
		fp = stdin;
		delim = '\n';
	} else {
		fp = fopen (*++argv, "r");
		delim = EOF;
	}

	while ((c = fgetc(fp)) != delim) {
		for (i = 0; i < num; i++) {
			if (!(sub[i][pos[i]]))
				pos[i] = 0;
			if (c != sub[i][pos[i]]) {
				flag[i] = 0;
				pos[i] = 0;
				continue;
			} 
			temp[j++] = c;
			flag[i] = 1;
			pos[i]++;
		}
		for (i = 0; i < num; i++) {
			if (flag[i]) {
				i = -1;
				break;
			}
		}
		if (i != -1) {
			temp[j] = '\0';
			putchar (c);
			//printf ("%s", temp);
			j = 0;
		} //else putchar (c);
	}
	return 0;
}
