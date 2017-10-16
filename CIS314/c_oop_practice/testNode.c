#include "node.h"
#include <string.h>
#include <stdio.h> /* puts() */
void initNode(NodeObj obj, int val) {
	setNodeValue(obj,val);
}

void linkNode(NodeObj obj, NodeObj * nodePtr) {
	setNextNode(obj,nodePtr);
}

int main() {
	NodeObj node1;
	NodeObj node2;
	NodeObj * nodePtr;
	node1 = newNodeObj();
	node2 = newNodeObj();
	dumpNodeState(node1);
	puts("Running initNode() on node1.\n");
	initNode(node1,42);
	dumpNodeState(node1);
	puts("Linking node2 as child.\n");
	nodePtr = &node2;
	initNode(node2,43);
	linkNode(node1,nodePtr);
	dumpNodeState(node1);
	dumpNodeState(node2);
	/* testing getters */
	puts("Getting values of nodes 1 and 2\n");
	printf("Value (node1) = %d. Value (node2) = %d.\n", getNodeValue(node1),getNodeValue(node2));
}
