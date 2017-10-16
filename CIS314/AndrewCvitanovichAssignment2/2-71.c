/* 	Problem 2-71: Fixed function xbyte
	Solution: The original function fails for negative numbers
	because it does not perform proper sign extension for negative numbers.
*/

#include <stdio.h>

/* Declaration of data type where 4 bytes are packed
into an unsigned */
typedef unsigned packed_t;

/* Extract byte from word. Return as signed integer */
int xbyte(packed_t word, int bytenum);

/* FIXED xbyte */
int xbyte(packed_t word, int bytenum)
{
	/*  Left shift word so that desired byte occupies 
		most significant bits of the word. Then, cast
		as an int and right shift 3 bytes. Sign extension
		should then occur correctly.
	*/
	
	return (int) (word << ((3 - bytenum) << 3)) >> 24;
}


/* TEST DRIVER */

int main() {
	
	printf("Fixed xbyte so that sign extension works for negative numbers.\n");
	printf("xbyte(0x00007700, 1): 0x%x\n", xbyte(0x00007700, 1));
	printf("xbyte(0x00EE0000, 2): 0x%x\n", xbyte(0x00EE0000, 2));

	return 0;
}