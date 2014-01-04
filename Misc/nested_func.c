# include <stdio.h>

//int dummy1();

int main () {
	int dummy (int a) {
		printf ("num : %d\n", a);
	return 0;
	}
	//dummy1(dummy);
	return (dummy (10));
}

//int dummy1(int *dummy) {
//	return (dummy(20));
//}
