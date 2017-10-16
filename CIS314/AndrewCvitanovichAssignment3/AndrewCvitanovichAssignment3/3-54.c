/*
	Problem 3.54
	By Andrew Cvitanovich
	decode2 function calculates x * (y - z) XORed with LSB of y - z
	If y - z is even, then x * (y - z) is returned
	If y - z is odd, then x * (y - z) is bit-flipped and the result is returned
	
	Example (a):
	x = 1, y = 2, z = 4
	x * (y - z) = -2
	y - z = -2 (even)
	returns -2 (0xFFFFFFFE)
	
	Example (b):
	x = -4, y = -8, z = -12
	x * (y - z) = -16
	y - z = 4 (even)
	returns -16 (0xFFFFFFF0)
	
	Example (c):
	x = 1, y = 1, z = 4
	x * (y - z) = -3
	y - z = -3 (odd)
	XOR flips bits
	returns 2 (0x00000001)
	
	Example (d):
	x = 1, y = 1, z = 18
	x * (y - z) = -3
	y - z = -17 (odd)
	XOR flips bits
	returns 16 (0x00000010)
	
*/

#include <stdio.h>

int decode2(int x, int y, int z) {
	return ( (x * (y - z)) ^ (((y - z) << 31) >> 31) );
};

int main () {
	printf("Examples where y - z is even.\n");
	printf("Returns x*(y-z)):\n");
	printf("%d\n", decode2(1,2,4));
	printf("%d\n", decode2(-4,-8,-12));
	printf("Examples where y - z is odd.\n");
	printf("Returns bit flip of x*(y-z):\n");
	printf("%d\n", decode2(1,1,4));
	printf("%d\n", decode2(1,1,18));
	return 0;
};