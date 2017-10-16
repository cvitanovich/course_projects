#include <stdio.h>

unsigned f2u(float f) {
	return *((unsigned*)&f);
}

int float_le(float x, float y) {
	unsigned ux = f2u(x);
	unsigned uy = f2u(y);
	/* Get the sign bits */
	unsigned sx = ux >> 31;
	unsigned sy = uy >> 31;
	/* Give an expression using only ux, uy, sx, and sy */
	return sx | ((ux <= uy) & ~sy);
}



/* Test Driver */

int main() {
	
	printf("float_le(0.0f,0.0f): %d\n", float_le(0.0f, 0.0f));
	printf("float_le(-0.0f,0.0f): %d\n", float_le(-0.0f, 0.0f));
	printf("float_le(-1.0f,0.0f): %d\n", float_le(-1.0f, 0.0f));
	printf("float_le(0.0f,1.0f): %d\n", float_le(0.0f, 1.0f));
	printf("float_le(1.0f,0.0f): %d\n", float_le(1.0f, 0.0f));
	printf("float_le(0.0f,-1.0f): %d\n", float_le(0.0f, -1.0f));
	# can't handle this:
	printf("float_le(-1.0f,-2.0f): %d\n", float_le(-1.0f, -2.0f));
	return 0;
}