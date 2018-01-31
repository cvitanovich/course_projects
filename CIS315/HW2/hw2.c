/* HW2 CIS 315 1/15/2018
 * Andrew Cvitanovich
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
      printf("%3d ", M[i][j]);
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

/* find all paths from start to destination "dest" */
void allPathsDFSRecursion (int **M, int n, int u, int dest, int * visited, int * path, 
		int step, int pathLength, int * Longest, int * nLongest, int * maxDist) {
  visited[u] = 1;
  path[step++] = u;
  if(maxDist[u] < pathLength) 
	  maxDist[u] = pathLength;
      	  
  /* search recursively for adjacent paths that work */
  if (u != dest) {
    for (int i = (u+1); i < n; ++i) {
      /* recurse on unvisited adjacent nodes (positive weights) */
      /* if the child node has already been visited by a longer path ignore (memoized with maxDist) */
      if (!visited[i] && (M[u][i] > 0) && (maxDist[i] <= (pathLength + M[u][i])))
        allPathsDFSRecursion(M,n,i,dest,visited,path,step,(pathLength + M[u][i]),Longest, nLongest, maxDist);
    }
  }
  
  /* reached destination */
  if (u == dest) {
    if (*Longest == pathLength)
      (*nLongest)++;
    if (*Longest < pathLength) {
      *nLongest = 1;
      *Longest = pathLength;
    }
  }

  /* back tracking */
  --step;
  visited[u] = 0;
}

/* find all paths of max length using DFS (modified) */
void allPathsDFS (int **M, int n, int start, int dest) {
  
  clock_t end, begin;
  
  begin = clock();
  /* update maxDist for this node if a longer path has been found */ 
  /* visited (init zero with calloc) */
  int * visited = (int *) calloc (n,sizeof(int));
  /* path array  (init zero with calloc) */
  int * path = (int *) calloc (n,sizeof(int));
  /* maxDist array memoizes maximum distances discovered to each node (to ignore shorter paths) */
  int * maxDist = (int *) calloc (n,sizeof(int));
  /* path length array (init zero with calloc) */
  /* int * pathLength = (int *) calloc (n,sizeof(int)); */
  int pathLength = 0;

  int step = 0; /* step along path */

  int longestPath = 0;
  int numLongestPaths = 0;

  /* call recursive subroutine allPathsRecursion */
  allPathsDFSRecursion(M, n, start, dest, visited, path, step, pathLength, \
    &longestPath, &numLongestPaths, maxDist);
  
  /* print results */
  printf("longest path: %d\n", longestPath);
  printf("number of longest paths: %d\n", numLongestPaths);

  /* free visited */
  free(visited);
  /* free path */
  free(path);
  /* free pathLength */
  /*free(pathLengh);*/
  /* free maxDist */
  free(maxDist);
  
      
  end = clock();

  begin = begin - end;
  /* printf("TIME = %f", (double)(end - begin)/CLOCKS_PER_SEC);*/
}

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
  char * s;
  s = NULL;

  /* get graph parameters N and M */
  s = fgets(buf, sizeof(buf), stdin);
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
		s = fgets(buf, sizeof(buf), stdin);
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

  /* print the adjacency matrix */
  /* printAdjMatrix(N,adjMat);*/
  allPathsDFS (adjMat, N, 0, N-1);

  /* free memory */
  freeAdjMatrix(N,&adjMat);

	return 0;
}
