#include <stdio.h>

/* x at %ebp + 8, n at %ebp + 12 */
int loop(int x, int n) {
  int result = -1;
  for(int mask = 1; mask != 0; mask <= n) { 
    result ^= x & mask;
  }
    return result;
}
