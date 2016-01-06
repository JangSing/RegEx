#include "addNode.h"
#include "Node.h"
#include "ErrorObject.h"
#include <stdlib.h>

void addNode(Node **currentNode,int index,Node *newNode){
  if(*currentNode==NULL  )
    throwError(ERR_NULL_NODE,"currentNode/newNode cannot be NULL.");
  else{
    (*currentNode)->next[index]=newNode;
    (*currentNode)->next[index+1]=NULL;
  }
}



