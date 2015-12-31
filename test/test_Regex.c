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
 *  text    = a
 *  pattern = \d
 *
 */
void test_Regex_given_text_not_matches_digit_pattern_should_return_NULL_matches(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a";

  pattern=nodeDigit;

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NULL(matchObj->ptr[0]);
}

/**
 *  text    = a
 *  pattern = \w
 *
 */
void test_Regex_given_text_matches_WORD_pattern_should_return_matchObj(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a";

  pattern=nodeWord;

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NOT_NULL(matchObj->ptr[0]);
  TEST_ASSERT_EQUAL_STRING("a",matchObj->ptr[0]->text);
  TEST_ASSERT_EQUAL(1,matchObj->ptr[0]->length);
  TEST_ASSERT_EQUAL(0,matchObj->ptr[0]->possition);

}

/**
 *  text    = a1
 *  pattern = \w\d
 *
 */
void test_Regex_given_text_matches_pattern_should_return_matched_text(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a1";

  pattern=nodeWord;
  addNode(&pattern,nodeDigit);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_EQUAL_PTR(nodeWord,pattern);
  TEST_ASSERT_EQUAL_PTR(nodeDigit,pattern->next);
  TEST_ASSERT_NULL(pattern->next->next);

  TEST_ASSERT_NOT_NULL(matchObj->ptr[0]);
  TEST_ASSERT_EQUAL_STRING("a1",matchObj->ptr[0]->text);
  TEST_ASSERT_EQUAL(2,matchObj->ptr[0]->length);
  TEST_ASSERT_EQUAL(0,matchObj->ptr[0]->possition);
}

/**
 *  text    = aa
 *  pattern = \w\d
 *
 */
void test_Regex_given_text_not_matches_pattern_should_return_NULL_match(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="aa";

  pattern=nodeWord;
  addNode(&pattern,nodeDigit);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NULL(matchObj->ptr[0]);

}

/**
 *  text    = a1
 *  pattern = \w\d\d
 *
 */
void test_Regex_given_pattern_longer_than_text_should_return_NULL_match(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a1";

  pattern=nodeWord;
  addNode(&pattern,nodeDigit);
  addNode(&pattern,nodeDigit1);


  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NULL(matchObj->ptr[0]);
}

/**
 *  text    = a123
 *  pattern = \w\d
 *
 */
void test_Regex_given_text_longer_than_pattern_should_return_NULL_match(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a123";

  pattern=nodeWord;
  addNode(&pattern,nodeDigit);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NULL(matchObj->ptr[0]);
}

/**
 *  text    = a1
 *  pattern = \w\d
 *
 */
void test_Regex_given_text_longer_than_pattern_with_only_space_should_return_NULL_match(void)
{
  ErrorObject *err;

  Node *pattern=NULL;

  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a1 ";

  pattern=nodeWord;
  addNode(&pattern,nodeDigit);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NOT_NULL(matchObj->ptr[0]);
  TEST_ASSERT_EQUAL_STRING("a1",matchObj->ptr[0]->text);
  TEST_ASSERT_EQUAL(2,matchObj->ptr[0]->length);
  TEST_ASSERT_EQUAL(0,matchObj->ptr[0]->possition);
}

/**
 *  text    = a1 a2
 *  pattern = \w\d
 *
 */
void test_Regex_given_text_longer_than_pattern_with_after_space_still_have_text_should_return_all_matchObj(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a1 a2";

  pattern=nodeWord1;
  addNode(&pattern,nodeDigit);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NOT_NULL(matchObj->ptr[0]);
  TEST_ASSERT_NOT_NULL(matchObj->ptr[1]);
  TEST_ASSERT_EQUAL_STRING("a1",matchObj->ptr[0]->text);
  TEST_ASSERT_EQUAL_STRING("a2",matchObj->ptr[1]->text);
  TEST_ASSERT_EQUAL(2,matchObj->ptr[0]->length);
  TEST_ASSERT_EQUAL(2,matchObj->ptr[1]->length);
  TEST_ASSERT_EQUAL(0,matchObj->ptr[0]->possition);
  TEST_ASSERT_EQUAL(3,matchObj->ptr[1]->possition);
}

/**
 *  text    = aa a2
 *  pattern = \w\d
 *
 */
void test_Regex_given_before_space_not_match_after_space_matches_should_return_matchObj(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="aa a2";

  pattern=nodeWord;
  addNode(&pattern,nodeDigit);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NOT_NULL(matchObj->ptr[0]);
  TEST_ASSERT_EQUAL_STRING("a2",matchObj->ptr[0]->text);
  TEST_ASSERT_EQUAL(2,matchObj->ptr[0]->length);
  TEST_ASSERT_EQUAL(3,matchObj->ptr[0]->possition);

}

/**
 *  text    = a1
 *  pattern = a\d
 *
 */
void test_Regex_given_pattern_with_alpha_a_and_digit_matches_text_should_return_matchObj(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a1";

  pattern=nodeA;
  addNode(&pattern,nodeDigit);

  matchObj=matchObjectRegEx(matchObj,str,pattern);
  TEST_ASSERT_NOT_NULL(matchObj->ptr[0]);
  TEST_ASSERT_EQUAL_STRING("a1",matchObj->ptr[0]->text);
  TEST_ASSERT_EQUAL(2,matchObj->ptr[0]->length);
  TEST_ASSERT_EQUAL(0,matchObj->ptr[0]->possition);

}

/**
 *  text    = a111b
 *  pattern = a\d*b
 *
 */
void test_Regex_given_attribute_asterisk_pattern_compare_with_multiples_digits_should_return_matchObj(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a111b";

  pattern=nodeA;
  addNode(&pattern,nodeDigitAst);
  addNode(&pattern,nodeB);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NOT_NULL(matchObj->ptr[0]);
  TEST_ASSERT_EQUAL_STRING("a111b",matchObj->ptr[0]->text);
  TEST_ASSERT_EQUAL(5,matchObj->ptr[0]->length);
  TEST_ASSERT_EQUAL(0,matchObj->ptr[0]->possition);

}

/**
 *  text    = ab
 *  pattern = a\d*b
 *
 */
void test_Regex_given_attribute_asterisk_pattern_compare_with_not_digit_should_compare_next_pattern_matches(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="ab";

  pattern=nodeA;
  addNode(&pattern,nodeDigitAst);
  addNode(&pattern,nodeB);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NOT_NULL(matchObj->ptr[0]);
  TEST_ASSERT_EQUAL_STRING("ab",matchObj->ptr[0]->text);
  TEST_ASSERT_EQUAL(2,matchObj->ptr[0]->length);
  TEST_ASSERT_EQUAL(0,matchObj->ptr[0]->possition);
}

/**
 *  text    = a1a1b
 *  pattern = a\d*b
 *
 */
void test_Regex_given_attribute_asterisk_pattern_compare_with_not_digit_should_compare_next_pattern_not_matches(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a1a1b";

  pattern=nodeA;
  addNode(&pattern,nodeDigitAst);
  addNode(&pattern,nodeB);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NULL(matchObj->ptr[0]);

}

/**
 *  text    = a111b
 *  pattern = a\d+b
 *
 */
void test_Regex_given_attribute_plus_pattern_compare_with_multiples_digits_should_return_matchObj(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a111b";

  pattern=nodeA;
  addNode(&pattern,nodeDigitPlus);
  addNode(&pattern,nodeB);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NOT_NULL(matchObj->ptr[0]);
  TEST_ASSERT_EQUAL_STRING("a111b",matchObj->ptr[0]->text);
  TEST_ASSERT_EQUAL(5,matchObj->ptr[0]->length);
  TEST_ASSERT_EQUAL(0,matchObj->ptr[0]->possition);
}

/**
 *  text    = ab
 *  pattern = a\d+b
 *
 */
void test_Regex_given_attribute_plus_pattern_compare_with_not_digits_should_return_NULL_matchObj(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="ab";

  pattern=nodeA;
  addNode(&pattern,nodeDigitPlus);
  addNode(&pattern,nodeB);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NULL(matchObj->ptr[0]);
}

/**
 *  text    = ab
 *  pattern = a\d?b
 *
 */
void test_Regex_given_attribute_question_pattern_compare_with_not_digits_should_return_matchObj(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="ab";

  pattern=nodeA;
  addNode(&pattern,nodeDigitQuest);
  addNode(&pattern,nodeB);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NOT_NULL(matchObj->ptr[0]);
  TEST_ASSERT_EQUAL_STRING("ab",matchObj->ptr[0]->text);
  TEST_ASSERT_EQUAL(2,matchObj->ptr[0]->length);
  TEST_ASSERT_EQUAL(0,matchObj->ptr[0]->possition);
}

/**
 *  text    = a11b
 *  pattern = a\d?b
 *
 */
void test_Regex_given_attribute_question_pattern_compare_with_more_than_one_digit_should_return_NULL_matchObj(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a11b";

  pattern=nodeA;
  addNode(&pattern,nodeDigitQuest);
  addNode(&pattern,nodeB);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NULL(matchObj->ptr[0]);
}

/**
 *  text    = a1234b
 *  pattern = a\d{0,5}b
 *
 */
void test_Regex_given_pattern_with_digit_attribute_range_count_number_within_range_should_return_matchObj(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a1234b";

  pattern=nodeA;
  addNode(&pattern,nodeDigit0to5);
  addNode(&pattern,nodeB);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NOT_NULL(matchObj->ptr[0]);
  TEST_ASSERT_EQUAL_STRING("a1234b",matchObj->ptr[0]->text);
  TEST_ASSERT_EQUAL(6,matchObj->ptr[0]->length);
  TEST_ASSERT_EQUAL(0,matchObj->ptr[0]->possition);
}

/**
 *  text    = a1234b
 *  pattern = a\d{0,5}b
 *
 */
void test_Regex_given_pattern_with_digit_attribute_range_count_number_not_within_range_should_return_NULL_matchObj(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a123456b";

  pattern=nodeA;
  addNode(&pattern,nodeDigit0to5);
  addNode(&pattern,nodeB);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NULL(matchObj->ptr[0]);

}

/**
 *  text    = a1234b
 *  pattern = a\d{5}b
 *
 */
void test_Regex_given_pattern_with_digit_attribute_exact_match_exact_number_should_return_matchObj(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a12345b";

  pattern=nodeA;
  addNode(&pattern,nodeDigitExact5);
  addNode(&pattern,nodeB);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NOT_NULL(matchObj->ptr[0]);
  TEST_ASSERT_EQUAL_STRING("a12345b",matchObj->ptr[0]->text);
  TEST_ASSERT_EQUAL(7,matchObj->ptr[0]->length);
  TEST_ASSERT_EQUAL(0,matchObj->ptr[0]->possition);
}

/**
 *  text    = asas asas asas asasa a
 *  pattern = a
 *
 */
void test_Regex_given_text_matches_pattern_should_return_correct_possition_and_matches_length(void)
{
  Node *pattern=NULL;


  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="aaaa aaaa aaaa aaaa a";

  pattern=nodeA;

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NOT_NULL(matchObj->ptr[0]);
  TEST_ASSERT_EQUAL_STRING("a",matchObj->ptr[0]->text);
  TEST_ASSERT_EQUAL(1,matchObj->ptr[0]->length);
  TEST_ASSERT_EQUAL(20,matchObj->ptr[0]->possition);
}



