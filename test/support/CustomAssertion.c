#include "unity.h"
#include "CustomAssertion.h"
#include "Node.h"

#include <stdlib.h>

void customTestRoot(Node *leftNode,int rootData,Node *rightNode,Node *actualNode,int lineNo){
  if(actualNode==NULL){
    CUSTOM_TEST_FAIL("There are nothing to be tested.");
  }
  else{
    if(rootData != actualNode->data)
      CUSTOM_TEST_FAIL("Expected root data %d Was %d.",rootData,actualNode->data);
    if(leftNode != actualNode->left)
      CUSTOM_TEST_FAIL("Expected left data %d Was %d.",leftNode,actualNode->left);
    if(rightNode != actualNode->right)
      CUSTOM_TEST_FAIL("Expected right data %d Was %d.",rightNode,actualNode->right);
  }
}

void customTestBalance(int expectBalance,Node *actual, int lineNo){
  if(actual==NULL){
    CUSTOM_TEST_FAIL("There are nothing to be tested.");
  }
  else{
    if(expectBalance != actual->balanceFactor)
      CUSTOM_TEST_FAIL("Expected Balance Factor %d Was %d.",expectBalance,actual->balanceFactor);
  }
}