#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

Node *iteratorGetNext(Node *rootPtr){
  Node *tempNode;
  while(tempNode->next!=NULL)
    tempNode=tempNode->next;
  
  return tempNode;
}