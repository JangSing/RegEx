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

  TEST_ASSERT_EQUAL(pattern->data,nodeDigit->data);
  TEST_ASSERT_EQUAL(pattern->next[1],nodeDigit->next[1]);

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

  TEST_ASSERT_MATCH(0,"a",1,0,matchObj);
  TEST_ASSERT_EQUAL(1,matchObj->numOfMatch);
  TEST_ASSERT_NULL(matchObj->ptr[1]);
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
  addNode(&pattern,0,nodeDigit);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_MATCH(0,"a1",2,0,matchObj);
  TEST_ASSERT_EQUAL(1,matchObj->numOfMatch);
  TEST_ASSERT_NULL(matchObj->ptr[1]);
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
  addNode(&pattern,0,nodeDigit);

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
  addNode(&pattern,0,nodeDigit);
  addNode(&nodeDigit,0,nodeDigit1);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_NULL(matchObj->ptr[0]);
}

/**
 *  text    = a123
 *  pattern = \w\d
 *
 */
void test_Regex_given_two_matches_without_space_should_return_two_matches(void)
{
  Node *pattern=NULL;

  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a123";

  pattern=nodeWord;
  addNode(&pattern,0,nodeDigit);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_MATCH(0,"a1",2,0,matchObj);
  TEST_ASSERT_MATCH(1,"23",2,2,matchObj);
  TEST_ASSERT_EQUAL(2,matchObj->numOfMatch);
  TEST_ASSERT_NULL(matchObj->ptr[2]);
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
  addNode(&pattern,0,nodeDigit);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_MATCH(0,"a1",2,0,matchObj);
  TEST_ASSERT_EQUAL(1,matchObj->numOfMatch);
  TEST_ASSERT_NULL(matchObj->ptr[1]);
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
  addNode(&pattern,0,nodeDigit);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_MATCH(0,"a1",2,0,matchObj);
  TEST_ASSERT_MATCH(1,"a2",2,3,matchObj);
  TEST_ASSERT_EQUAL(2,matchObj->numOfMatch);
  TEST_ASSERT_NULL(matchObj->ptr[2]);
}

/**
 *  text    = asas asas asas asas a
 *  pattern = a
 *
 */
void test_Regex_given_text_matches_pattern_should_return_correct_possition(void)
{
  Node *pattern=NULL;

  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="asas asas asas asas a";

  pattern=nodeA;
  addNode(&pattern,0,NULL);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_MATCH(0,"a",1,0,matchObj);
  TEST_ASSERT_MATCH(1,"a",1,2,matchObj);
  TEST_ASSERT_MATCH(2,"a",1,5,matchObj);
  TEST_ASSERT_MATCH(3,"a",1,7,matchObj);
  TEST_ASSERT_MATCH(4,"a",1,10,matchObj);
  TEST_ASSERT_MATCH(5,"a",1,12,matchObj);
  TEST_ASSERT_MATCH(6,"a",1,15,matchObj);
  TEST_ASSERT_MATCH(7,"a",1,17,matchObj);
  TEST_ASSERT_MATCH(8,"a",1,20,matchObj);
  TEST_ASSERT_EQUAL(9,matchObj->numOfMatch);
  TEST_ASSERT_NULL(matchObj->ptr[9]);
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
  addNode(&pattern,0,nodeDigit);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_MATCH(0,"a1",2,0,matchObj);
  TEST_ASSERT_EQUAL(1,matchObj->numOfMatch);
  TEST_ASSERT_NULL(matchObj->ptr[1]);
}



/**
 *  text    = a111
 *  pattern = a\d*
 *
 */
void test_Regex_given_attribute_asterisk_digit_pattern_compare_with_multiples_digits_should_return_matchObj(void)
{
  Node *pattern=NULL;

  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a111";

  pattern=nodeA;
  addNode(&pattern,0,nodeDigitAst);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_MATCH(0,"a111",4,0,matchObj);
  TEST_ASSERT_EQUAL(1,matchObj->numOfMatch);
  TEST_ASSERT_NULL(matchObj->ptr[1]);
}

/**
 *  text    = a111b
 *  pattern = a\d*b
 *
 */
void test_Regex_given_attribute_asterisk_digit_pattern_compare_with_multiples_digits_and_alphaB_should_return_matchObj(void)
{
  Node *pattern=NULL;

  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="a111b";

  pattern=nodeA;
  addNode(&pattern,0,nodeDigitAst);
  addNode(&nodeDigitAst,0,nodeB);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_MATCH(0,"a111b",5,0,matchObj);
  TEST_ASSERT_EQUAL(1,matchObj->numOfMatch);
  TEST_ASSERT_NULL(matchObj->ptr[1]);
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
  addNode(&pattern,0,nodeDigitAst);
  addNode(&nodeDigitAst,0,nodeB);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_MATCH(0,"ab",2,0,matchObj);
  TEST_ASSERT_EQUAL(1,matchObj->numOfMatch);
  TEST_ASSERT_NULL(matchObj->ptr[1]);
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
  addNode(&pattern,0,nodeDigitAst);
  addNode(&nodeDigitAst,0,nodeB);

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
  addNode(&pattern,0,nodeDigitPlus);
  addNode(&nodeDigitPlus,0,nodeB);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_MATCH(0,"a111b",5,0,matchObj);
  TEST_ASSERT_EQUAL(1,matchObj->numOfMatch);
  TEST_ASSERT_NULL(matchObj->ptr[1]);
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
  addNode(&pattern,0,nodeDigitPlus);
  addNode(&nodeDigitPlus,0,nodeB);

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
  addNode(&pattern,0,nodeDigitQuest);
  addNode(&nodeDigitQuest,0,nodeB);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_MATCH(0,"ab",2,0,matchObj);
  TEST_ASSERT_EQUAL(1,matchObj->numOfMatch);
  TEST_ASSERT_NULL(matchObj->ptr[1]);
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
  addNode(&pattern,0,nodeDigitQuest);
  addNode(&nodeDigitQuest,0,nodeB);

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
  addNode(&pattern,0,nodeDigit0to5);
  addNode(&nodeDigit0to5,0,nodeB);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_MATCH(0,"a1234b",6,0,matchObj);
  TEST_ASSERT_EQUAL(1,matchObj->numOfMatch);
  TEST_ASSERT_NULL(matchObj->ptr[1]);
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
  addNode(&pattern,0,nodeDigit0to5);
  addNode(&nodeDigit0to5,0,nodeB);

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
  addNode(&pattern,0,nodeDigitExact5);
  addNode(&nodeDigitExact5,0,nodeB);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_MATCH(0,"a12345b",7,0,matchObj);
  TEST_ASSERT_EQUAL(1,matchObj->numOfMatch);
  TEST_ASSERT_NULL(matchObj->ptr[1]);
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
void test_Regex_given_pattern_with_multiples_branches_one_of_the_branches_matches_text_should_return_matchObj(void)
{
  Node *pattern=NULL;

  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="ade";

  pattern=nodeA;
  addNode(&pattern,0,nodeB);addNode(&nodeB,0,nodeE);
  addNode(&pattern,1,nodeC);addNode(&nodeC,0,nodeE);
  addNode(&pattern,2,nodeD);addNode(&nodeD,0,nodeE);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_MATCH(0,"ade",3,0,matchObj);
  TEST_ASSERT_EQUAL(1,matchObj->numOfMatch);
  TEST_ASSERT_NULL(matchObj->ptr[1]);
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
void test_Regex_pattern_with_multiples_branches_before_have_text(void)
{
  Node *pattern=NULL;

  MatchObject *matchObj=createMatchObj();
  int i;
  char *str="oiajace";

  pattern=nodeA;
  addNode(&pattern,0,nodeB);addNode(&nodeB,0,nodeE);
  addNode(&pattern,1,nodeC);addNode(&nodeC,0,nodeE);
  addNode(&pattern,2,nodeD);addNode(&nodeD,0,nodeE);

  matchObj=matchObjectRegEx(matchObj,str,pattern);

  TEST_ASSERT_MATCH(0,"ace",3,4,matchObj);
  TEST_ASSERT_EQUAL(1,matchObj->numOfMatch);
  TEST_ASSERT_NULL(matchObj->ptr[1]);
}

