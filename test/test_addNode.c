#include "unity.h"
#include "Node.h"
#include "addNode.h"
#include "ErrorObject.h"
#include "CException.h"
#include "CustomAssertion.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

Node  *nodeA;
Node  *nodeB;
Node  *nodeC;
Node  *nodeD;
Node  *nodeE;

Node *resetNode(int pattern,int attribute,int begin,int end){
  Node *node=malloc(sizeof(Node)*2);

  node->data = pattern;
  node->attribute = attribute;
  node->begin=begin;
  node->end=end;
  node->next[0] =NULL;
  node->next[1] =NULL;
}

void setUp(void){
  nodeA=resetNode('a',0,0,0);
  nodeB=resetNode('b',0,0,0);
  nodeC=resetNode('c',0,0,0);
  nodeD=resetNode('d',0,0,0);
  nodeE=resetNode('e',0,0,0);
}

void tearDown(void)
{
}

/**
 *  text    = abe
 *  pattern = a[bcd]e
 *
 *           --> b -
 *         /        \
 *        a --> c --> e
 *         \        /
 *          --> d -
 */
void test_addNode_function_given_currentNode_is_NULL_should_throw_error(void)
{
  Node *nullPattern=NULL;
  ErrorObject *err;
  int i;

  Try{
    addNode(&nullPattern,0,nodeB);
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("currentNode/newNode cannot be NULL.",err->errorMsg);
    free(err);
  }
}

/**
 *  text    = abe
 *  pattern = a[bcd]e
 *
 *           --> b -
 *         /        \
 *        a --> c --> e
 *         \        /
 *          --> d -
 */
void test_addNode_function_by_adding_multiple_branch_of_nodes(void)
{
  Node *pattern=NULL;
  int i;

  pattern=nodeA;
  addNode(&pattern,0,nodeB);addNode(&nodeB,0,nodeE);
  addNode(&pattern,1,nodeC);addNode(&nodeC,0,nodeE);
  addNode(&pattern,2,nodeD);addNode(&nodeD,0,nodeE);

  TEST_ASSERT_EQUAL_PTR(nodeB,nodeA->next[0]);
  TEST_ASSERT_EQUAL_PTR(nodeC,nodeA->next[1]);
  TEST_ASSERT_EQUAL_PTR(nodeD,nodeA->next[2]);
  TEST_ASSERT_NULL(nodeA->next[3]);
  TEST_ASSERT_EQUAL_PTR(nodeE,nodeB->next[0]);
  TEST_ASSERT_NULL(nodeB->next[1]);
  TEST_ASSERT_EQUAL_PTR(nodeE,nodeC->next[0]);
  TEST_ASSERT_NULL(nodeC->next[1]);
  TEST_ASSERT_EQUAL_PTR(nodeE,nodeD->next[0]);
  TEST_ASSERT_NULL(nodeD->next[1]);
}

