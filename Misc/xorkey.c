/* XOR key (50 Points)

   Xorq has invented an encryption algorithm which uses bitwise XOR operations extensively. This encryption algorithm uses a sequence of non-negative integers x1, x2, ... xn  as key. To implement this algorithm efficiently, Xorq needs to find maximum value for (a xor xj)  for given integers a,p and q such that p<=j<=q. Help Xorq to implement this function.

Input :
First line of input contains a single integer T (1<=T<=6). T test cases follow.
First line of each test case contains two integers N and Q separated by a single space (1<= N<=100,000; 1<=Q<= 50,000).  Next line contains N integers x1, x2, ... xn separated by a single space (0<=xi< 215). Each of next Q lines describe a query which consists of three integers ai,pi and qi (0<=ai< 215, 1<=pi<=qi<= N).

Output :
For each query, print the maximum value for (ai xor xj) such that pi<=j<=qi  in a single line.

Sample Input :
1
15 8
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
10 6 10
1023 7 7
33 5 8
182 5 10
181 1 13
5 10 15
99 8 9
33 10 14

Sample Output :
13
1016
41
191
191
15
107
47

Explanation :
First Query (10 6 10): x6 xor 10 = 12, x7 xor 10 = 13, x8 xor 10 = 2, x9 xor 10 = 3, x10 xor 10 = 0, therefore answer for this query is 13.
Second Query (1023 7 7): x7 xor 1023 = 1016, therefore answer for this query is 1016.
Third Query (33 5 8): x5 xor 33 = 36, x6 xor 33 = 39, x7 xor 33 = 38, x8 xor 33 = 41, therefore answer for this query is 41.
Fourth Query (182 5 10): x5 xor 182 = 179, x6 xor 182 = 176, x7 xor 182 = 177, x8 xor 182 = 190, x9 xor 182 = 191, x10 xor 182 = 188, therefore answer for this query is 191. */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int x[100000];
FILE *fp;

int read_next_num () {
	int num = 0, a;
	while (((a = fgetc(fp)) == ' ') || (a == '\n'))
		;
	num = a - '0';
	while ((a = fgetc(fp)) != EOF) {
		if ((a == ' ') || (a == '\n')) break;
		num *= 10;
		num += a - '0';
	}
	return num;
}

int main (int argc, char **argv) {
	int i, ntest, N, Q, p, q, j, a, max;

	if (!(fp = fopen (argv[1], "r")))
		fp = stdin;

	ntest = read_next_num();

	while (ntest--) {

		N = read_next_num();
		Q = read_next_num();

		for (i = 0; i < N; i++)
			x[i] = read_next_num();

		for (i = 0; i < Q; i++) {
			a = read_next_num();
			p = read_next_num();
			q = read_next_num();
			max = 0;

			for (j = p - 1; j < q; j++)
				if (max < (a ^ x[j])) max = (a ^ x[j]);

			printf ("%d\n", max);
		}
	}

	return 0;
}
