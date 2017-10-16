/*	Original function copy_int is buggy because
	sizeof(val) has unsigned return type. So,
	the >= comparison is always true (a tautology).
	by casting the result of sizeof as an int we
	can avoid this error.
*/

#include <stdio.h>
#include <string.h>


/* Copy integer into buffer if space is available 	*/
/* FIXED: conditional evaluates size cast as int 	*/
/* so that comparison is correctly made.			*/
int copy_int(int val, void *buf, int maxbytes) {
	if (maxbytes - (int) sizeof(val) >= 0) {
 		memcpy(buf, (void *) &val, sizeof(val));
 		return 1; /* copy success */
 	}
 	return 0; /* copy failure */
} 

int main() {
	int buf[1];
	
	/* memcpy should be called (success) */
	printf("copy_int(%d,buffer,%d): Expect success, Got %s\n", 42, 4,
		(copy_int(42,buf,4) ? "success" : "failure")
		);
	/* memcpy should fail */
	printf("copy_int(%d,buffer,%d): Expect failure, Got %s\n", 42, 2,
		(copy_int(42,buf,2) ? "success" : "failure")
		);
	/* memcpy should fail */
	printf("copy_int(%d,buffer,%d): Expect failure, Got %s\n", 56, 1,
		(copy_int(56,buf,1) ? "success" : "failure")
		);
	/* memcpy should be called (success) */
	printf("copy_int(%d,buffer,%d): Expect success, Got %s\n", 56, 5,
		(copy_int(56,buf,5) ? "success" : "failure")
		);
	return 0;
}