typedef struct node * NodeObj;
NodeObj newNodeObj();
void setNodeValue(NodeObj theNode, int num);
void setNextNode(NodeObj theNode, NodeObj * nodePtr);
int getNodeValue(NodeObj theNode);
NodeObj * getNextNode(NodeObj theNode);
void dumpNodeState(NodeObj theNode);
void deleteNodeObj(NodeObj theNode);
