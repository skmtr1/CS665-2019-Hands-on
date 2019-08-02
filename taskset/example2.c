/*
 * C program to find sum of two integers using command line arguments
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[])
{
	int a, b, sum=0;
	
	assert(argc == 3);
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	sum = a+b;
	
	while(1)
		printf("Sum of %d and %d is : %d\n ", a, b, sum);

	return 0;
}
