#include "unity.h"
#include "Regex.h"
#include "Node.h"
#include "addNode.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

/**
 *  text    = a
 *  pattern = \w
 *
 */
void test_Regex_given_text_matches_pattern_should_return_matched_text(void)
{
  Node *pattern;

  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a";

  pattern=nodeWord;

  matchObj=matchObjectregEx(matchObj,str,pattern);

  TEST_ASSERT_EQUAL_PTR(nodeWord,pattern);
  TEST_ASSERT_NULL(pattern->next);

  TEST_ASSERT_EQUAL_STRING("a",matchObj->ptr[0]->text);
  TEST_ASSERT_EQUAL(1,matchObj->ptr[0]->length);
  TEST_ASSERT_EQUAL(0,matchObj->ptr[0]->possition);
}

/**
 *  text    = a1
 *  pattern = \w\d
 *
 */
void test_Regex_given_text_matches_pattern_should_return_matched_text1(void)
{
  Node *pattern;

  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a1";

  pattern=nodeWord;
  addNode(&pattern,nodeDecimal);

  matchObj=matchObjectregEx(matchObj,str,pattern);

  TEST_ASSERT_EQUAL_PTR(nodeWord,pattern);
  TEST_ASSERT_EQUAL_PTR(nodeDecimal,pattern->next);
  TEST_ASSERT_NULL(pattern->next->next);

  TEST_ASSERT_EQUAL_STRING("a1",matchObj->ptr[0]->text);
  TEST_ASSERT_EQUAL(2,matchObj->ptr[0]->length);
  TEST_ASSERT_EQUAL(0,matchObj->ptr[0]->possition);

}

/**
 *  text    = a1
 *  pattern = \w\d\d
 *
 */
void test_Regex_given_pattern_longer_than_text_should_return_NULL_match(void)
{
  Node *pattern;

  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a1";

  pattern=nodeWord;
  addNode(&pattern,nodeDecimal);
  addNode(&pattern,nodeDecimal1);


  matchObj=matchObjectregEx(matchObj,str,pattern);

  TEST_ASSERT_NULL(matchObj->ptr[0]);

}

/**
 *  text    = a123
 *  pattern = \w\d
 *
 */
void test_Regex_given_text_longer_than_pattern_should_return_NULL_match(void)
{
  Node *pattern;

  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a123";

  pattern=nodeWord;
  addNode(&pattern,nodeDecimal);

  matchObj=matchObjectregEx(matchObj,str,pattern);

  TEST_ASSERT_NULL(matchObj->ptr[0]);

}

/**
 *  text    = a1
 *  pattern = \w\d
 *
 */
void test_Regex_given_text_longer_than_pattern_with_only_space_should_return_NULL_match(void)
{
  Node *pattern;

  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a1 ";

  pattern=nodeWord;
  addNode(&pattern,nodeDecimal);

  matchObj=matchObjectregEx(matchObj,str,pattern);
  TEST_ASSERT_EQUAL_STRING("a1",matchObj->ptr[0]->text);
  TEST_ASSERT_EQUAL(2,matchObj->ptr[0]->length);
  TEST_ASSERT_EQUAL(0,matchObj->ptr[0]->possition);
}

/**
 *  text    = a1 a1
 *  pattern = \w\d
 *
 */
void test_Regex_given_text_longer_than_pattern_with_after_space_still_have_text_should_return_NULL_match(void)
{
  Node *pattern;

  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a1 a2";

  pattern=nodeWord;
  addNode(&pattern,nodeDecimal);

  matchObj=matchObjectregEx(matchObj,str,pattern);
  TEST_ASSERT_EQUAL_STRING("a1",matchObj->ptr[0]->text);
  TEST_ASSERT_EQUAL_STRING("a2",matchObj->ptr[1]->text);
  TEST_ASSERT_EQUAL(2,matchObj->ptr[0]->length);
  TEST_ASSERT_EQUAL(2,matchObj->ptr[1]->length);
  TEST_ASSERT_EQUAL(0,matchObj->ptr[0]->possition);
  TEST_ASSERT_EQUAL(3,matchObj->ptr[1]->possition);

}
