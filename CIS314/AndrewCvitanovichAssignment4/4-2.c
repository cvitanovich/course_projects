#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define M 16

typedef int Marray_t[M][M]; /* 52 x 52 sized int array */

/* transposeWithPtr: Optimized transpose function according to assembly code */
void transposeWithPtr(Marray_t A) {
	int i, j;
	int * lower = &A[0][0];
	for (i = 0; i < M; i++) {
		int * upper = &A[0][0] + i;
		j = 0;	
		while(j < i) {
			int t = *(lower + j); /* movl (%esi, %ecx, 4), %edx */
			*(lower + j) = *upper; /* movl %eax, (%esi, %ecx, 4) */
			j++; /* addl $1, %ecx */
			*upper = t; /* %edx, (%ebx) */
			upper += M; /* addl $52, %ebx */
		}
		lower += M;
	}
}

/* printArray: Prints contents of an array */	
void printArray(Marray_t A) {
	printf("Printing the array: \n");
	int i, j;
	for (i = 0; i < M; i++) {
		for (j=0; j < M-1; j++) {
			printf("%d,",A[i][j]);
		}
		printf("%d\n",A[i][j]);
	}
}

/* checkSameArrays: Check if arrays A and B have identical elements */
void checkSameArrays(Marray_t A, Marray_t B) {
	int i, j;
	int test = 0;
	for (i = 0; i < M; i++) {
		for (j = 0; j < M; j++) {
			if( A[i][j] != B[i][j] )
				test++;
		}
	}
	if( test == 0 ) {
		printf("YES \n"); /* A == B */
	} else { printf("NO \n"); } /* A != B */
}

int main() {
	Marray_t A, B;
	srand(time(NULL));
	
	/* fill arrays A and B with the same random ints */
	printf("Creating matrices A and B, where A = B and elements are randomized.\n");
	int i, j, r;
	for (i = 0; i < M; i++) {
		for (j=0; j<M; j++) {
			r = rand() % 100; /* random int between 0 and 99 */		
			A[i][j] = r;
			B[i][j] = r;
		}
	}
	
	/* Transpose B twice. */
	printf("Transposing B twice...\n");
	transposeWithPtr(B);
	transposeWithPtr(B);
	
	/* test that A = B */
	printf("Does A still equal B? ");
	checkSameArrays(A,B);
}
