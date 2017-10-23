/* "hello world" as a "method" */

#include <stdio.h>

struct person {
	int (*say) (const char *);
	char * name;
};


int main() {
	struct person p;
	struct person q;
	p.say = puts;
	p.say("hello world");
	p.name = "Andrew";
	printf("My name is: %s\n",p.name);
	q.name = "Bob";
	printf("His name is: %s\n",q.name);
	return 0;
}
