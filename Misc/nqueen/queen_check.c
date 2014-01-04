#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int insert_n_check (int x, int y, int limit, int **board) {
	int i;

	/* fprintf (stdout, "x : %d, y : %d, lim : %d\n", x, y, limit); */

	if (board[x][y]) return -1;

	for (i = 0; i < limit; i++) {
		board[x][i] = board[i][y] = 1;

		if (valid (x-i, y-i, limit)) board[x-i][y-i] = 1;
		if (valid (x-i, y+i, limit)) board[x-i][y+i] = 1;
		if (valid (x+i, y-i, limit)) board[x+i][y-i] = 1;
		if (valid (x+i, y+i, limit)) board[x+i][y+i] = 1;
	}
	return 0;
}

int valid (int x, int y, int limit) {
	if (x < 0) return 0;
	if (y < 0) return 0;
	if (x >= limit) return 0;
	if (y >= limit) return 0;
	return 1;
}

int **init_board (int limit) {
	int **board, i;

	board = (int **) calloc (limit, sizeof (int *));

	for (i = 0; i < limit; i++)
		board[i] = (int *) calloc (limit, sizeof (int));

	return board;
}

int main (int argc, char **argv) {
	int **board = init_board (argc - 1);
	int i, x, y;

	for (i = 1; i < argc; i++) {
		x = (tolower(argv[i][0])) - 'a';
		y = atoi (&argv[i][1]) - 1;

		if (!valid (x, y, argc - 1)) {
			fprintf (stderr, "Invalid cell position %s\n", argv[i]);
			exit (-1);
		}

		/* fprintf (stdout, "Checking cell position %s\n", argv[i]); */

		if (insert_n_check(x, y, argc - 1, board) == -1) {
			fprintf (stderr, "Incorrect Solution\n");
			exit (-2);
		}
	}

	fprintf (stdout, "\nCorrect Solution\n");
}
