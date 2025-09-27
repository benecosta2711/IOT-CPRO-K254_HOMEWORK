#include "stdio.h"
#include "stdlib.h"
int main()
{
	int* arr;
while(1){
arr = (int *) malloc(10 * sizeof(int));
printf("%d\n", *arr);
}
int a = 5;
arr = &a;
printf("%d\n", *arr);
return 0;
}
