#include <stdio.h>

/*
 * Mask with least significant n bits set to 1
 * Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
 * Assue 1 <= n <= w
*/

int lower_one_mask(int n) {
	int mask = 1;
	/* left shift by n-1 bits */
	mask <<= (n-1);
	/* subtract one to get n-1 lsb's set to one */
	mask -= 1;
	/* left shift by 1 bit (avoids errors when n==w) */
	mask <<= 1;
	/* add 1 so that lowest bit is 1 */
	mask += 1;
	return mask;
}

int main() {
	printf("Output of lower_one_mask(n) in decimal notation: \n");
	printf("1: %d\n",lower_one_mask(1));
	printf("2: %d\n",lower_one_mask(2));
	printf("3: %d\n",lower_one_mask(3));
	printf("5: %d\n",lower_one_mask(5));
	printf("17: %d in decimal, %x in hex.\n", lower_one_mask(17), lower_one_mask(17));
}
