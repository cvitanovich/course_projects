#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b) {
	unsigned int mask = 0xFF << (i*8); /* left shift mask by i bytes */
	unsigned int replace = b << 8*i; /* replacement byte */
	x = x & ~mask; /* zero out desired byte */
	x = x | replace; /* combine x and b with bitwise or */
	return x;
}

int main() {
	unsigned int y = 0x12345678;
	unsigned int z = 0x0;
	z = replace_byte(y,2,0xAB);
	printf("Replacing byte %d with %x. Result = %x\n",2,0xAB,z);
	z = replace_byte(y,0,0xAB);
	printf("Replacing byte %d with %x. Result = %x\n",0,0xAB,z);
}
