#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len) {
	int i;
	for (i = 0; i < len; i++)
		printf(" %.2x", start[i]);
	printf("\n");
}

void show_short(short x) {
	show_bytes((byte_pointer) &x, sizeof(short));
}

void show_long(long x) {
	show_bytes((byte_pointer) &x, sizeof(long));
}

void show_double(double x) {
	show_bytes((byte_pointer) &x, sizeof(double));
}

int main() {
	short sval = 1;
	long lval = 1;
	double dval = 3.1415926;
	printf("Byte representations of data types.\n");
	printf("Testing for a short variable sval = 1: \n");
	show_short(sval);
	printf("Testing for a short variable sval = 255: \n");
	sval = 255;
	show_short(sval);
	printf("Testing for a long variable lval = 1: \n");
	show_long(lval);
	printf("Testing for a long variable lval = 255: \n");
	lval = 255;
	show_long(lval);
	printf("Testing for a double variable dval = 3.1415926: \n");
	show_double(dval);
}
