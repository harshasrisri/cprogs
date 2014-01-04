# include <stdio.h>
# include <stdlib.h>

int main (int argc, char **argv) {
	int c, *flag, *pos, delim, *cnt, num, i;
	char **sub;
	FILE *fp;

	fprintf (stdout, "Enter the number of substrings to be searched : ");
	fscanf (stdin, "%d", &num);
	sub = calloc (num, sizeof (char*));
	flag = calloc (num, sizeof (int));
	pos = calloc (num, sizeof (int));
	cnt = calloc (num, sizeof (int));

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
			if (!(sub[i][pos[i]])) {
				if (flag[i]) cnt[i]++;
				pos[i] = 0;
			}
			if (c != sub[i][pos[i]]) {
				flag[i] = 0;
				pos[i] = 0;
				continue;
			} 
			flag[i] = 1;
			pos[i]++;
		}
	}

	for (i = 0; i < num; i++)
		if (!cnt[i]) printf ("Substring \"%s\" not found\n", sub[i]);
		else printf("%d occurances of \"%s\"\n", cnt[i], sub[i]);
	return 0;
}
