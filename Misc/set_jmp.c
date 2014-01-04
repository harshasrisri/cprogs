# include <stdio.h>
# include <setjmp.h>

jmp_buf main_proc;

void sub2 (int val) {
	printf ("entered 2...\n");
	if (val == 2) longjmp (main_proc, 2);
}

void sub1 (int val) {
	printf ("entered 1...\n");
	if (val == 1) longjmp (main_proc, 1);
	printf ("Calling 2...\n");
	sub2(val);
	printf ("returned from 2...\n");
}

int main (int argc, char **argv) {
	int val;

	if (argc < 2) val = 0;
	else sscanf (argv[1], "%d", &val);

	switch (setjmp (main_proc)) {
		case 0 :
			printf ("Called Setjmp\n");
			break;
		case 1 :
			printf ("Came from 1\n");
			val = 0; break;
		case 2 :
			printf ("Came from 2\n");
			val = 0; break;
	}
	if (val >= 1) {
		printf ("Calling 1...\n");
		sub1 (val);
		printf ("Returned form 1...\n");
	}
	return 0;
}
