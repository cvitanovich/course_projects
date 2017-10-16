/*
	Problem 1 of Assignment 3
	By Andrew Cvitanovich
	Uses selection sort to sort a user specified array.
	Then prints the array to the console.
*/

#include <stdio.h>
#include <stdlib.h>

/* reads array data from user */
int * readArray(int length) {
	int i = 0;
	int * array = (int *) malloc(length);
	printf("Enter the %d elements of the array:\n",length);
	while(i < length) {
		/* get array data */
		printf("Element %d? ", i);
		scanf("%d", array + i); /* store inputed data into array indexed by i */
		i++;	
	}
	return array;
};

/* swaps int values x,y pointed to by xp and yp */
void swap(int * xp, int * yp) {
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
};

/* sort array using selection sort algorithm and swap function */
void sortArray(int * array, int length) {
	int min; /* min = index of smallest element found */
	/* outer loop: increments sorted subarray */
	for(int i = 0; i < length; i++) {
		min = i;
		/* inner loop: finds elements smaller than array[min] */
		for(int j = i + 1; j < length; j++) {
			if( *(array + j) < *(array + min) )
				min = j;
		}
		/* swap array[i] with array[min] */
		swap(array + i, array + min);
	}
};

/* print the array */
void printArray(int * array, int length) {
	int i = 0;
	printf("[");
	while(i < (length - 1) ) {
		printf("%d,", *(array + i));
		i++;
	}
	printf("%d]\n", *(array + i));
};

int main() {
	/* data type declarations */
	int len;
	int * A;
	/* get array size info from user */
	printf("Enter array size: ");
	scanf("%d",&len);
	printf("Creating array of size: %d\n", len);
	/* read user specified data into array pointed to by A */
	A = readArray(len);
	/* sort array */
	printf("The sorted array is: \n");
	sortArray(A,len);
	/* print array */
	printArray(A,len);
	/* free memory heap and return */
	free(A);
	return(0);
}
	
