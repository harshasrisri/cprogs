/* 
 * Recursive function to calculate the square root of a number. Not very precise. 
 * rounds to the ceil of the actual numbers before the precision loses out 
 */

#include <stdio.h>

#define my_sqrt(limit) _my_sqrt(0,limit)

typedef unsigned long long ull;

ull limit;

ull _my_sqrt (ull low, ull high) {
    ull mid = 0, prod = 0, ret = 0;

    mid = (low + high);
    mid = (mid % 2) ? (mid/2)+1 : (mid/2);
    prod = mid * mid;

    if (mid == low) 
        return mid + 1;
    if ((mid == high) || (prod == limit))
        return mid;
    else if (prod > limit)
        ret = _my_sqrt (low, mid);
    else 
        ret = _my_sqrt (mid, high);
    return ret;
}

int main (int argc, char **argv) {
	return printf ("%llu\n", my_sqrt(limit = atoll (argv[1])));
}
