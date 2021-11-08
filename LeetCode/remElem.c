#include <stdio.h>

void swap (int *a, int *b) {
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void printNums (int *nums, int numsSize) {
	int i;
	for (i = 0; i < numsSize; i++)
		printf ("%d ", nums[i]);
	printf ("\n");
}

int removeElement (int *nums, int numsSize, int val) {
	int *front, *back, count = 0, i;

	if (!numsSize) return 0;

	front = back = &nums[numsSize - 1];

	while (front >= nums) {
		printNums (nums, numsSize);
		if (*front == val) {
			swap (front, back);
			back--;
			count++;
		}
		front--;
	}

	return numsSize - count;
}

int test1[] = {};
int test2[] = {1};
int test3[] = {2,3};
int test4[] = {3,3};
int test5[] = {4,5};
int test6[] = {4,5,0,1,0,2,0,3};

int main (int argc, char **argv) {
	int res, i;

	printf ("%d\n\n", removeElement (test1, 0, 0));
	printf ("%d\n\n", removeElement (test2, 1, 1));
	printf ("%d\n\n", removeElement (test3, 2, 3));
	printf ("%d\n\n", removeElement (test4, 2, 3));
	printf ("%d\n\n", removeElement (test5, 2, 4));
	printf ("%d\n\n", removeElement (test6, 8, 0));

	return 0;
}
