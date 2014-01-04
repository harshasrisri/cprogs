#include <stdio.h>
#include <string.h>
 
int main()
{
  long i = 1;
  int size = ((char*)(&i)+1)-((char*)(&i));
  printf("%d\n", size);
 
  return 0;
}
