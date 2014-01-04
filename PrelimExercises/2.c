#include<stdio.h>

int main( int argc, char *argv[] )
{
	int i,init[] = {0,1,2,3,4}, final[5], n;
	sscanf (argv[1], "%d", &n);
	for(i=0;i<5;i++)
	final[i] = init[(i+n) % 5];
	printf("initial array\t= ");
	for(i=0;i<5;i++) printf("\t %d",init[i]);
	printf("\nfinal array\t= ");
	for(i=0;i<5;i++) printf("\t %d",final[i]);
	return 0;
}
