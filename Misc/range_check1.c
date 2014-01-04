# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int main (int argc, char **argv) {
	char num_array[] = "01234567890123456789";
	char *num1 = argv[1];
	char *num2 = argv[2];
	char *i_ptr, *i_ptr_old, *f_ptr, *f_ptr_old, *ch;
	int length, i;
	
	length = strlen (num2);
	do {
		i_ptr = strchr (num_array, *num1++);
		f_ptr = strchr (i_ptr, *num2++);
		if (i > 0) {
			if (*f_ptr_old >= *i_ptr_old) {
				f_ptr = i_ptr + 9;
			}
		}
		for (ch = i_ptr; ch <= f_ptr; ch++) 
			putchar (*ch);
		putchar ('\n');
		i_ptr_old = i_ptr;
		f_ptr_old = f_ptr;
		i_ptr = strchr (num_array, *num1);
		f_ptr = strchr (i_ptr, *num2);
	} while (i++ < length);
	return 0;
}
