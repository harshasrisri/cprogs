# include <stdio.h>
# include <stdlib.h>

int main ( int argc, char **argv ) {
	int size = 0, c;
	char *src, *dst;

	src = malloc (10);
	while ((c = getchar()) != EOF) {
		if (!(size % 10)) src = realloc (src, size + 10);
		src[size++] = c;
	}
	src[size++] = '\0';
	printf ("source string : %s\n", src);
	dst = malloc (size);
	do (*dst++ = *src);
	while (*src++);
	printf ("destination string : %s\n", dst -= size);
	return 0;
}
