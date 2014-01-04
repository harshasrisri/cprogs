/* Problem :
 * You are given an N x N chessboard and N queens. Write a program such that 
 * when all queens are placed on the board, no queen will harm the other and
 * which provides at least one unique solution for a given N.
 *
 * Background :
 * On an NxN board, each row can hold only one Queen. So, I keep a note of
 * the position of the Queen in each row in an array. In that case, the 
 * index of the array denotes the row number and the value denotes the
 * position. For ease of use, I denote the position in a row as an alphabet
 * starting from 'a'. So, an example valid configuration in an 8x8 board
 * such as :
 *
 *         d8 g7 c6 h5 b4 e3 a2 f1
 *
 * arranged lexicographically, becomes :
 *
 *         a2 b4 c6 d8 e3 f1 g7 h5
 *
 * which, in my intrepration will be represented by the string 
 *
 *         "bdfhcage"
 *
 * If only one Queen is present per row, and if there are N rows, we can
 * place N Queens on a NxN board in N! ways. Each of the N! ways can be
 * obtained by permuting N variables over their positions. So, for an
 * 8x8 board, we can obtain the Queen placements by permuting the string
 * "abcdefgh", and one permutation of "abcdefgh" which provides a valid
 * placement of 8 Queens is "bdfhcage".
 *
 * In this program, I'm following the following steps to arrive at a solution
 *
 * 1. Start with a permute string of length N in lexico ascending order.
 *    So, for an 8x8 it'll be "abcdefgh".
 *
 * 2. Check if this string provides a valid placement of all the Queens.
 *
 * 3. If it is a valid placement, print the string as proper board postions.
 *
 * 4. If if is not, find the next permutation of the string and repeat step 2.
 *
 */

/*
 * Teaser : If you comment one line in this program, It gives you all
 *          possible Valid board configurations. Find it out for yourself.
 *          It is pretty easy to figure out. :-)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Setting the Globals for board size, permute string and the 2-D board */

int limit;
char *permute, *pri_diag, *sec_diag;


/* Helper function : reverse a string. Used by get_next_permute() */
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

/* Permutation Generator : generates in-place permutations, lexicographically. */
char *get_next_permute () {
	static int init = 1;
	int k, l, temp;;

	if (init) {
		permute = (char *) malloc (limit + 1);
		permute[limit] = '\0';

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

/* Checks if the position placed is valid or not.
 * Since we are dealing with permutations, only one Queen is available 
 * per each row and column. So, this function just checks if there is 
 * clash along any of the diagonals.
 */
int insert_n_check (int x, int y) {
	int d1 = x + y;
	int d2 = limit + x - y;

	if (pri_diag[d1]) return 0;
	if (sec_diag[d2]) return 0;

	return pri_diag[d1] = sec_diag[d2] = 1;
}

/* Takes string representation of the board, converts to standard position
 * and checks each position on the fly if it is valid and returns the status */
int check_board (char *positions) {
	int i;

	for (i = 0; i < limit; i++)
		if (!insert_n_check(i, (positions[i] - 'a')))
			return 0;

	return 1;
}

/* resets all positions in the board to zero */
void re_init_board () {
	memset ((void *)pri_diag, 0, limit * 2);
	memset ((void *)sec_diag, 0, limit * 2);
}

/* Main function : Does the steps listed in the introduction */
int main (int argc, char **argv) {
	char *positions, i;
	limit = atoi (argv[1]);

	pri_diag = (char *) calloc (limit * 2, sizeof (char));
	sec_diag = (char *) calloc (limit * 2, sizeof (char));

	while (1) {
		re_init_board ();

		if (!(positions = get_next_permute ())) break;

		if (check_board (positions)) {
			for (i = 0; i < limit; i++)
				printf ("%c%d ", i+'a', positions[i] - 'a' + 1);
			break;
			putchar ('\n');
		}
	}

	return 0;
}
/* Thats it. Enjoy the program, and of course, the results too :-). */
