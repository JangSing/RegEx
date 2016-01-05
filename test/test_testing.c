#include "unity.h"
#include "Regex.h"
#include "Node.h"
#include "addNode.h"
#include "Match.h"
#include "ErrorObject.h"
#include "CException.h"
#include "CustomAssertion.h"
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
 *        a --> c --> d
 *         \        /
 *          --> d -
 */
void test_Regex_given_pattern_with_multiples_branches_one_of_the_branches_matches_text_should_return_matchObj(void)
{
  Node *pattern=NULL;

  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="ace";

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


  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_MATCH(0,"ace",3,0,matchObj);
  TEST_ASSERT_EQUAL(1,matchObj->numOfMatch);
  TEST_ASSERT_NULL(matchObj->ptr[1]);
}


