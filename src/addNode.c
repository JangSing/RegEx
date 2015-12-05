#include "addNode.h"
#include "Node.h"
#include <stdlib.h>

void addNode(Node **rootPtr,Node *newNode){
  Node *tempNode=*rootPtr;
  while(tempNode->next!=NULL)
    tempNode=tempNode->next;
  tempNode->next=newNode;
  
}



