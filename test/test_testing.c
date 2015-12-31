#include "unity.h"
#include "Regex.h"
#include "Node.h"
#include "addNode.h"
#include "Match.h"
#include "ErrorObject.h"
#include "CException.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

Node  *nodeDigit;
Node  *nodeDigit1;
Node  *nodeDigitAst;
Node  *nodeDigitPlus;
Node  *nodeDigitQuest;
Node  *nodeDigit0to5;
Node  *nodeDigitExact5;
Node  *nodeCapAlpha;
Node  *nodeAlpha;
Node  *nodeWord;
Node  *nodeWord1;
Node  *nodeSpace;
Node  *nodeA;
Node  *nodeB;
Node  *nodeC;

Node *resetNode(int pattern,int attribute,int begin,int end){
  Node *node=malloc(sizeof(Node));

  node->data = pattern;
  node->attribute = attribute;
  node->begin=begin;
  node->end=end;
  node->next =NULL;
}

void setUp(void){
  nodeDigit=resetNode(DIGIT,0,0,0);
  nodeDigit1=resetNode(DIGIT,0,0,0);
  nodeDigitAst=resetNode(DIGIT,ATT_ASTERISK,0,0);
  nodeDigitPlus=resetNode(DIGIT,ATT_PLUS,0,0);
  nodeDigitQuest=resetNode(DIGIT,ATT_QUESTION,0,0);
  nodeDigit0to5=resetNode(DIGIT,ATT_RANGE,0,5);
  nodeDigitExact5=resetNode(DIGIT,ATT_EXACT,5,0);
  nodeCapAlpha=resetNode(CAP_ALPHA,0,0,0);
  nodeAlpha=resetNode(ALPHA,0,0,0);
  nodeWord=resetNode(WORD,0,0,0);
  nodeWord1=resetNode(WORD,0,0,0);
  nodeSpace=resetNode(SPACE,0,0,0);
  nodeA=resetNode('a',0,0,0);
  nodeB=resetNode('b',0,0,0);
}

void tearDown(void)
{
}

/**
 *  text    = a1234b
 *  pattern = a\d{5}b
 *
 */
void test_testing(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="asas asas asas asasa a";

  pattern=nodeA;
  // addNode(&pattern,nodeDigitExact5);
  // addNode(&pattern,nodeB);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NOT_NULL(matchObj->ptr[0]);
  TEST_ASSERT_EQUAL_STRING("a",matchObj->ptr[0]->text);
  TEST_ASSERT_EQUAL(1,matchObj->ptr[0]->length);
  TEST_ASSERT_EQUAL(21,matchObj->ptr[0]->possition);
}