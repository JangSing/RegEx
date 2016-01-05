#include "addNode.h"
#include "Node.h"
#include <stdlib.h>

void addNode(Node **currentNode,int index,Node *newNode){
  (*currentNode)->next[index]=newNode;
  (*currentNode)->next[index+1]=NULL;
}



