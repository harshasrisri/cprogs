# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int binary (char *s) {
	while (*s)
		if ((*s != '0') && (*s != '1')) return 0;
		else s++;
	return 1;
}

int main (int argc, char **argv) {
	char *smaller, *bigger, *result, *pos;
	int big_len, small_len, carry, temp, i;

	if (argc != 3) {
		error:
		fprintf (stderr, "Usage : ./a.out <bin_no> <bin_no>\n");
		exit (1);
	}

	if ((big_len = strlen (argv[1])) > (small_len = strlen (argv[2]))) {
		bigger = argv[1];
		smaller = argv[2];
	} else {
		bigger = argv[2];
		smaller = argv [1];
		temp = big_len;
		big_len = small_len;
		small_len = temp;
	}

	if (!binary(bigger) || !binary(smaller)) goto error;

	smaller += small_len - 1;
	bigger += big_len - 1;
	result = (char *) malloc (big_len + 1 + 1);				// Extra space for carry and null cahracter
	pos = result + big_len + 1;
	*pos-- = '\0';
	carry = 0;

	for (i = 0; i < big_len; i++) {
		temp = carry + *bigger-- - '0';
		if (i < small_len)
			temp += *smaller-- - '0';
		carry = temp/2;
		temp %= 2;
		*pos-- = temp + '0';
	}
	*pos = carry + '0';

	printf ("Result = %s\n", result);
	return 0;
}
