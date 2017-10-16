#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

/* node class */
struct node {
	int nodeVal;
	void * nextNode;
	/* malloc any private data here */
};

/* create a new node object */
NodeObj newNodeObj() {
	NodeObj theNode = (NodeObj) malloc(sizeof(struct node));
	memset(theNode, 0, sizeof(struct node));
	return theNode;
}

/* set value of node */
void setNodeValue(NodeObj theNode, int num) {
	if(theNode==NULL) return;
	theNode->nodeVal = num;
}

/* set next node pointer */
void setNextNode(NodeObj theNode, NodeObj * nodePtr) {
	if(theNode==NULL) return;
	theNode->nextNode = nodePtr;
}

/* get node value */
int getNodeValue(NodeObj theNode) {return theNode->nodeVal;}

/* get pointer to next node */
NodeObj * getNextNode(NodeObj theNode) {return theNode->nextNode;}

/* dump the state of the node */
void dumpNodeState(NodeObj theNode) {
	if(theNode==NULL) return;
	printf("Node value is %d\n", getNodeValue(theNode));
	printf("Address of next node is %p\n", getNextNode(theNode));
}

/* delete a node */
void deleteNodeObj(NodeObj theNode) {
	/* free any malloced private date here! */
	free(theNode);
}
