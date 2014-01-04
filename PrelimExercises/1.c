#include<stdio.h>

int main()
{
	int c;
	printf("Press numbers > 40 to get echo; 0 to exit!\n");
	while(scanf("%d",&c) == 1)
	{
		if(c >= 40) printf("%d\n",c);
		else if(c == 0) exit(0);
	}
	return 0;
}
