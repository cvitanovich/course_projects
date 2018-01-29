/* HW0 CIS 315 1/15/2018
 * Andrew Cvitanovich
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
	char buf[BUFSIZ];
	char X_str[BUFSIZ];
	char Y_str[BUFSIZ];
	int count;
	int X;
	int Y;

	/* get line count */
	fgets(buf, sizeof(buf), stdin);
	size_t len = strlen(buf);
	if (len > 0 && buf[len-1] == '\n')
		buf[--len] = '\0';
	count = strtol (buf, NULL, 0);

	/* For each line copy characters to string buffer,
	 * then parse separate number strings and convert
	 * these to integers X and Y. Finally, output
	 * X+Y and X*Y.
	 */
  	
	for(int line = 0; line < count; line++){
		strcpy(X_str,"");
		strcpy(Y_str,"");
		fgets(buf, sizeof(buf), stdin);
		int i = 0;
		while(buf[i] != ' ')
			strcat(X_str,&buf[i++]);
		while(buf[i] != '\n')
			strcat(Y_str,&buf[i++]);
		X = strtol (X_str, NULL, 0);
		Y = strtol (Y_str, NULL, 0);
		printf("%d %d\n",X+Y,X*Y);
	}
	return 0;
}
