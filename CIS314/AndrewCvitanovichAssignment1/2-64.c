#include <stdio.h>

/* Return 1 when any odd bit of x equals 1; 0 otherwise. Assume w=32. */

int any_odd_one(unsigned x) {
	/* mask of ones in ODD positions for 32-bit words */
	unsigned int mask = 0xAAAAAAAA;
	return (x & mask) != 0x0;
};

int main() {
	int result;
	/* testing values */
	printf("0x0: %d\n",any_odd_one(0x0));
	printf("0x1: %d\n",any_odd_one(0x1));
	printf("0x2: %d\n",any_odd_one(0x2));
	printf("0x3: %d\n",any_odd_one(0x3));
	printf("0xFFFFFFFF: %d\n",any_odd_one(0xFFFFFFFF));
	printf("0x55555555: %d\n",any_odd_one(0x55555555));
}
