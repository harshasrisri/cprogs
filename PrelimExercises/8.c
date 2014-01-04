#include<stdio.h>

int main()
{
	int i=0,j=0,count[27]={' '},c;
	printf("enter text :\n");
	while((c=getchar()) != EOF)
	{
		count[c - 'a']++;
		if(c=='\n' || c=='\t' || c==' ') 
			count[26]++;
	}
	count[0] = count[0] - 32;
	for(i=0 ; i<=26 ; i++)
	{
		printf("%d\v\b",count[i]);
		for(j=0; j<count[i] ; j++)
			printf(".\v\b");
		if(i!=26) printf("\t%c",'a'+i);
		else printf("white spaces");
	}
	return 0;
}
