#include "unity.h"
#include "Regex.h"
#include "Node.h"
#include "addNode.h"
#include <stdio.h>
#include <stdlib.h>

Node  *nodeDecimal;
Node  *nodeDecimal1;
Node  *nodeCapAlpha;
Node  *nodeAlpha;
Node  *nodeWord;
Node  *nodeSpace;

Node *resetNode(char *pattern,int attribute){
  Node *node=malloc(sizeof(Node));

  node->data = pattern;
  node->attribute = attribute;
  node->next =NULL;
}

void setUp(void){
  nodeDecimal=resetNode("\\d",1);
  nodeDecimal1=resetNode("\\d",1);
  nodeCapAlpha=resetNode("\\A",1);
  nodeAlpha=resetNode("\\a",1);
  nodeWord=resetNode("\\w",1);
  nodeSpace=resetNode("\\s",1);
}

void tearDown(void)
{
}

void test_Regex_given_text_matches_pattern_should_return_matched_text(void)
{
  Node *pattern;

  Match *match;
  int i;

  pattern=nodeWord;

  match=matchObjectregEx("a",pattern);

  TEST_ASSERT_EQUAL_PTR(nodeWord,pattern);
  TEST_ASSERT_NULL(pattern->next);

  TEST_ASSERT_EQUAL_STRING("a",match->text);
  TEST_ASSERT_EQUAL(1,match->length);
  TEST_ASSERT_EQUAL(0,match->possition);
}

void test_Regex_given_text_matches_pattern_should_return_matched_text1(void)
{
  Node *pattern;

  Match *match;
  int i;

  pattern=nodeWord;
  addNode(&pattern,nodeDecimal);

  match=matchObjectregEx("a1",pattern);

  TEST_ASSERT_EQUAL_PTR(nodeWord,pattern);
  TEST_ASSERT_EQUAL_PTR(nodeDecimal,pattern->next);
  TEST_ASSERT_NULL(pattern->next->next);

  TEST_ASSERT_EQUAL_STRING("a1",match->text);
  TEST_ASSERT_EQUAL(2,match->length);
  TEST_ASSERT_EQUAL(0,match->possition);

}

void test_Regex_given_pattern_longer_than_text_should_return_NULL_match(void)
{
  Node *pattern;

  Match *match;
  int i;
  char *str="a1";

  pattern=nodeWord;
  addNode(&pattern,nodeDecimal);
  addNode(&pattern,nodeDecimal1);


  match=matchObjectregEx("a1",pattern);

  TEST_ASSERT_NULL(match);

}

