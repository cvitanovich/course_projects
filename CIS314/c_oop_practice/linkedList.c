#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* linked list class */
struct linkedList {
	NodeObj * head = NULL;
	int size = 0;
}

linkedListObj newLinkedListObj() {
       	linkedListObj theList;
	return theList;
}

void insert(linkedListObj theList, int num) {
	NodeObj newNode = newNodeObj();
	NodeObj * newNodePtr = &newNode;
	setNodeValue(newNode,num);
	setNextNode(theList->head,newNodePtr);
	theList->head++;
	theList->size++;
}

int listSize(linkedListObj theList) {return theList->size;}

int delete(linkedListObj) {
	NodeObj * headPtr = theList->head;
	int headValue = getNodeValue(theList->head);
	if(theList->size > 1)
		theList->head--;
	theList->size--;
	deleteNodeObj(headPtr);
	return headValue;
}

