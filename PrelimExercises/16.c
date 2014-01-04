# include <stdio.h>

int main () {
	struct x {
		char c;
		int i;
	} abc;
	printf ("%u %u\n", &abc.c, &abc.i);
}
