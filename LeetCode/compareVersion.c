#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int compareVersion (char *version1, char *version2) {
	int major1 = atoi (version1);
	int major2 = atoi (version2);
	if (major1 > major2) return 1;
	else if (major1 < major2) return -1;
	else {
		char *sub1, *sub2;
		sub1 = strchr (version1, '.');
		sub2 = strchr (version2, '.');
		if (!sub1 && !sub2) return 0;
		if (sub1) ++sub1; else sub1 = "0";
		if (sub2) ++sub2; else sub2 = "0";
		return compareVersion (sub1, sub2);
	}
}

int main () {
	printf ("%d\n", compareVersion ("0","0.0"));
	printf ("%d\n", compareVersion ("1","1.1"));
	printf ("%d\n", compareVersion ("1.0","1.1"));
	printf ("%d\n", compareVersion ("10.6","10.6.5"));
	printf ("%d\n", compareVersion ("1.2.3.4","1.2.3.4.5"));
}
