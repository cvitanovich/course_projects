/* HW2 CIS 315 1/15/2018
 * Andrew Cvitanovich
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* allocate adjacency matrix for graph */
void allocateAdjMatrix (const int n, int ***M) {
  (*M) = (int **) malloc (n * sizeof(int *));
  for (int i = 0; i < n; ++i)
    (*M)[i] = (int *) malloc (n * sizeof(int));
}

/* initialize adjacency matrix for graph */
void initAdjMatrix (const int n, int**M) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      M[i][j] = 0;
    }
  }
}

/* print adjacency matrix (for debugging) */
void printAdjMatrix (const int n, int **M) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%5d ", M[i][j]);
    }
    printf("\n");
  }
}

/* free adjacency matrix memory */
void freeAdjMatrix (const int n, int ***M) {
  for (int i = 0; i < n; ++i) {
    free((*M)[i]);
  }
  free(*M);
}

/* stack for topological sort */
typedef struct {
  int * values;
  int top;
  int maxSize;
} stackT;

void stackInit(stackT *stackPtr, int maxSize) {
  int * v;
  v = (int *) malloc (maxSize * sizeof(int));
  stackPtr->values = v;
  stackPtr->maxSize = maxSize;
  stackPtr->top = -1; /* empty = -1 */
}

int stackEmpty(stackT *stackPtr) {
  if (stackPtr->top == -1)
    return 1;
  else
    return 0;
}

void stackFree(stackT *stackPtr) {
  free(stackPtr->values);
  stackPtr->values = NULL;
  stackPtr->maxSize = 0;
  stackPtr->top = -1;
}

void stackPush(stackT *stackPtr, int val) {
  stackPtr->values[++stackPtr->top] = val;
}

int stackPop(stackT *stackPtr) {
  return stackPtr->values[stackPtr->top--];
}

/* topological sort recursion */
void topoSortRecursion (const int n, int v, int **M, int *visited, stackT *stack) {
  /* mark this node visited */
  visited[v] = 1;

  for (int i = 0; i < n; ++i) {
    if (!visited[i] && M[v][i] > 0)
      topoSortRecursion(n,i,M,visited,stack);
  }

  /* push this node onto stack for sort */
  stackPush(stack,v);
}

/* topoSort (depends on topoSortRecursion)*/
void topoSort (const int n, int **M) {
  /* stack for topoSort function */
  stackT * stack;
  stackInit(stack,n);

  /* array of visited nodes (initialize all to zero = unvisited) */
  int * visited = (int *) calloc (n, sizeof(int));

  while(0) {
  for (int i = 0; i < n; i++) {
    if (visited[i] == 0)
      topoSortRecursion(n, i, M, visited, stack);
  }

  while (!stackEmpty(stack)) {
    printf("%d ",(int) stackPop(stack));
  }
  }

  /* free stack */
  stackFree(stack);

  /* free visited array */
  free(visited);


}

/* depth first search */
/* tracks current length of path and compares with maxLength */
/* n = number of nodes, v = start node (zero indexed) */
void DFS (const int n, int v, \
  int prevLength, int *maxLength, int **M, int *visited) {

  /* current length initialized to zero */
  int currentLength = 0;

  visited[v] = 1; /* node v is start (mark visited) */
  printf("%d\n",v+1);

  /* find adjacent nodes */
  for (int i = 0; i < n; ++i) {

    /* recurse on unvisited adjacent nodes (positive weights) */
    if (!visited[i] && M[v][i] > 0) {
      /* update path length */
      currentLength = prevLength + M[v][i];
      printf("path length: %d\n",currentLength);
      /* recursively call DFS on adjacent nodes */
      DFS (n, i, currentLength, maxLength, M, visited);
    }

    /* update maxLength if a longer path is found */
    if (currentLength > (*maxLength))
      (*maxLength) = currentLength;

    /* rezero currentLength */
    currentLength = 0;

  }

} /* end DFS */


int main(void)
{

  /* input processing */
	char buf[BUFSIZ]; /* line buffer */
	char X_str[BUFSIZ]; /* string processing */
	char Y_str[BUFSIZ]; /* string processing */
  char Z_str[BUFSIZ]; /* string processing */
  int i; /* line buffer index */

  /* adjacency matrix */
  int ** adjMat;

  /* graph properties */
	int N; /* number of nodes */
  int M; /* number of edges */
  int I; /* edge start */
  int J; /* edge end */
  int W; /* edge weight */

  /* longest path */
  int maxLength = 0;

	/* get graph parameters N and M */
	fgets(buf, sizeof(buf), stdin);
  strcpy(X_str,"");
  strcpy(Y_str,"");
  i = 0;
  while(buf[i] != ' ')
    strcat(X_str,&buf[i++]);
  while(buf[i] != '\n')
    strcat(Y_str,&buf[i++]);
  N = strtol (X_str, NULL, 0);
  M = strtol (Y_str, NULL, 0);

  /* create adjacency matrix */
  allocateAdjMatrix(N,&adjMat);
  initAdjMatrix(N,adjMat); /* empty NxN matrix */

  /* process line-by-line the remaining input */
	for(int line = 0; line < M; line++){
		strcpy(X_str,"");
		strcpy(Y_str,"");
    strcpy(Z_str,"");
		fgets(buf, sizeof(buf), stdin);
		i = 0;
    /* grab parameters of each edge */
		while(buf[i] != ' ')
			strcat(X_str,&buf[i++]);
    while(buf[++i] != ' ')
        strcat(Y_str,&buf[i]);
		while(buf[i] != '\n')
			strcat(Z_str,&buf[i++]);
		I = strtol (X_str, NULL, 0);
		J = strtol (Y_str, NULL, 0);
    W = strtol (Z_str, NULL, 0);
    /* store this edge in adjacency matrix */
    /* use 0...n-1 for proper C lang numbering */
    adjMat[I-1][J-1] = W;
  }

  /* topological sort */
  topoSort(N,adjMat);

  /* DFS starting at first vertex */
  /* arguments: no. nodes, start node, prevLength, &maxLength, adjMat, visited*/
  /* DFS(N, 0, 0, &maxLength, adjMat, visited); */

  /* print the adjacency matrix */
  printAdjMatrix(N,adjMat);

  /* free memory */
  freeAdjMatrix(N,&adjMat);

	return 0;
}
