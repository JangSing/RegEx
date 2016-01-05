#include "addNode.h"
#include "Node.h"
#include <stdlib.h>

void addNode(Node **rootPtr,Node *newNode){
  Node *tempNode=*rootPtr;
  while(tempNode->next[0]!=NULL)
    tempNode=tempNode->next[0];
  tempNode->next[0]=newNode;

}



