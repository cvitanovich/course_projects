/* 
 * QUESTION 3 ... CIS314 ... Assignment 7
 * By Andrew Cvitanovich
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#define SIZE 10000
#define NTESTS 100
#define FNAME "data.csv"
#define COLLECT_TEST_DATA 1

void inner(float *u, float *v, int length, float *dest) {
  int i;
  float sum = 0.0f;
  for (i = 0; i < length; ++i) {
    sum += u[i] * v[i];
  }
  *dest = sum;
} 

void inner2(float *u, float *v, int length, float *dest) {
  int i;
  int limit = length - 3; /* n - k + 1 where n = length and k = 4 */
  float sum0 = 0.0f;
  float sum1 = 0.0f;
  float sum2 = 0.0f;
  float sum3 = 0.0f;
  
  /* Combine 4 pairs of elements at a time */
  for (i = 0; i < limit; i+=4) {
    sum0 = sum0 + (u[i] * v[i]);
    sum1 = sum1 + (u[i+1] * v[i+1]);
    sum2 = sum2 + (u[i+2] * v[i+2]);
    sum3 = sum3 + (u[i+3] * v[i+3]);
  }
  
  
  
  /* wrap up remaining elements */
  for (; i < length; i++) {
    sum0 = sum0 + (u[i] * v[i]);
  }
  
  *dest = sum0 + sum1 + sum2 + sum3;
}

int main() {
	/* new seed for random number gernerator */
	srand((unsigned int)time(NULL));
	
	/* timing variables */
	clock_t start, end;
	double cpu_time = 0;
	double cpu_time2 = 0;
	double speedup = 0;
	
	/* declare two static arrays of 100 float elements */
	float u[SIZE];
	float v[SIZE];
	
	/* output */
	float ip;
	float ip2;
	
	for(int j = 0; j < NTESTS; j++) {
		/* fill each array with random floats */
		for (int i = 0; i < SIZE; i++) {
		  u[i] = ((float)rand()/(float)(RAND_MAX));
		  v[i] = ((float)rand()/(float)(RAND_MAX));
		}
	
		/* test inner() */
		start = clock();
		inner(u,v,SIZE,&ip);
		end = clock();
		cpu_time += (double)(end - start) / CLOCKS_PER_SEC;
		/* printf("Time taken for inner(): %f\n", cpu_time); */
	
		/* test inner2() */
		start = clock();
		inner2(u,v,SIZE,&ip2);
		end = clock();
		cpu_time2 += (double)(end - start) / CLOCKS_PER_SEC;
		/* printf("Time taken for inner2(): %f\n", cpu_time2); */
	}
	
	/* calculate and display speedup and average cpu time */
	speedup = (double) cpu_time / cpu_time2;
	printf("Testing arrays of %i elements %i times, speedup is: %f\n", SIZE, NTESTS, speedup);
	printf("Old function average clock time is: %f\n", cpu_time / NTESTS);
	printf("New function average clock time is: %f\n", cpu_time2 / NTESTS);
	
	if(COLLECT_TEST_DATA) {
		printf("HELP!");
		/* trying several array sizes */
		int lengths[10] = {800,1600,3200,6400,12800,25600,51200,102400,204800,409600}; 
		FILE * f = fopen(FNAME,"w");
		if(f==NULL) return -1;
		float * a;
		float * b;
		for(int i = 0; i < 10; i++) {
			/* allocate arrays and fill with random floats */
			a = (float *) malloc(sizeof(float)*lengths[i]);
			b = (float *) malloc(sizeof(float)*lengths[i]);
			if(a == NULL || b == NULL) {
			  printf("malloc of size %d failed!\n",lengths[i]);
			  exit(1);
			}
			for (int j = 0; j < lengths[i]; j++) {
			  a[j] = ((float)rand()/(float)(RAND_MAX));
			  b[j] = ((float)rand()/(float)(RAND_MAX));
			}
			/* test this array length 10 times */
			for (int k = 0; k < 10; k++) {
				/* time inner() */
				start = clock();
				inner(a,b,lengths[i],&ip);
				end = clock();
				cpu_time = (double)(end - start) / CLOCKS_PER_SEC;
				/* time inner2() */
				start = clock();
				inner2(a,b,lengths[i],&ip2);
				end = clock();
				cpu_time2 = (double)(end - start) / CLOCKS_PER_SEC;
				speedup = (double) cpu_time / cpu_time2;
				/* write line to csv file */
				fprintf(f,"%i,%f,%f,%f\n",lengths[i],cpu_time,cpu_time2,speedup);
			}
		}
		fclose(f);
	}
	return 0;
}
  