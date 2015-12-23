#include "unity.h"
#include "Match.h"
#include "Regex.h"
#include "ErrorObject.h"
#include "CException.h"
#include <stdlib.h>

Node *nodeA;

Node *resetNode(int pattern,int attribute){
  Node *node=malloc(sizeof(Node));
  
  node->data = pattern;
  node->attribute = attribute;
  node->next =NULL;
}

void setUp(void)
{
  nodeA=resetNode('a',0);
}

void tearDown(void)
{
}

void test_match_Digit_function_given_element_passing_into_function_is_NULL(void)
{
  ErrorObject *err;
  int j=0;int i=0;
  char *text=NULL;
  MatchObject *matchObj=NULL;
  Match *match=NULL;
  
  Try{
    j=matchDigit(&matchObj,&match,text,i,j);
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("matchObj/match/text cannot be NULL.",err->errorMsg);
    free(err);
  }
  
}

void test_match_Digit_function_given_text_is_not_digit_should_give_0_to_match_in_matchObj(void)
{
  int j=0;int i=0;
  char *text="a";
  
  MatchObject *matchObj=createMatchObj();
  Match *match=createMatch();
  
	j=matchDigit(&matchObj,&match,text,i,j);
  
  TEST_ASSERT_NOT_NULL(matchObj);
  TEST_ASSERT_EQUAL(0,matchObj->match);
  TEST_ASSERT_EQUAL(0,j);
}

void test_match_Digit_function_given_text_is_digit_should_store_to_match_structure(void)
{
  int j=0;int i=0;
  char *text="1";
  
  MatchObject *matchObj=createMatchObj();
  Match *match=createMatch();
  
	j=matchDigit(&matchObj,&match,text,i,j);
  
  TEST_ASSERT_NOT_NULL(matchObj);
  TEST_ASSERT_NOT_NULL(match);
  TEST_ASSERT_EQUAL(1,matchObj->match);
  TEST_ASSERT_EQUAL(1,j);
  TEST_ASSERT_EQUAL(0,match->possition);
  TEST_ASSERT_EQUAL_STRING("1",match->text);
}

void test_match_Cap_Alpha_function_given_text_is_Cap_Alpha_should_store_to_match_structure(void)
{
  int j=0;int i=0;
  char *text="A";
  
  MatchObject *matchObj=createMatchObj();
  Match *match=createMatch();
  
	j=matchCapAlpha(&matchObj,&match,text,i,j);
  
  TEST_ASSERT_NOT_NULL(matchObj);
  TEST_ASSERT_NOT_NULL(match);
  TEST_ASSERT_EQUAL(1,matchObj->match);
  TEST_ASSERT_EQUAL(1,j);
  TEST_ASSERT_EQUAL(0,match->possition);
  TEST_ASSERT_EQUAL_STRING("A",match->text);
}

void test_match_Alpha_function_given_text_is_Alpha_should_store_to_match_structure(void)
{
  int j=0;int i=0;
  char *text="a";
  
  MatchObject *matchObj=createMatchObj();
  Match *match=createMatch();
  
	j=matchAlpha(&matchObj,&match,text,i,j);
  
  TEST_ASSERT_NOT_NULL(matchObj);
  TEST_ASSERT_NOT_NULL(match);
  TEST_ASSERT_EQUAL(1,matchObj->match);
  TEST_ASSERT_EQUAL(1,j);
  TEST_ASSERT_EQUAL(0,match->possition);
  TEST_ASSERT_EQUAL_STRING("a",match->text);
}

void test_match_Word_function_given_text_is_Word_should_store_to_match_structure(void)
{
  int j=0;int i=0;
  char *text="a";
  
  MatchObject *matchObj=createMatchObj();
  Match *match=createMatch();
  
	j=matchWord(&matchObj,&match,text,i,j);
  
  TEST_ASSERT_NOT_NULL(matchObj);
  TEST_ASSERT_NOT_NULL(match);
  TEST_ASSERT_EQUAL(1,matchObj->match);
  TEST_ASSERT_EQUAL(1,j);
  TEST_ASSERT_EQUAL(0,match->possition);
  TEST_ASSERT_EQUAL_STRING("a",match->text);
}

void test_match_Space_function_given_text_is_Space_should_store_to_match_structure(void)
{
  int j=0;int i=0;
  char *text=" ";
  
  MatchObject *matchObj=createMatchObj();
  Match *match=createMatch();
  
	j=matchSpace(&matchObj,&match,text,i,j);
  
  TEST_ASSERT_NOT_NULL(matchObj);
  TEST_ASSERT_NOT_NULL(match);
  TEST_ASSERT_EQUAL(1,matchObj->match);
  TEST_ASSERT_EQUAL(1,j);
  TEST_ASSERT_EQUAL(0,match->possition);
  TEST_ASSERT_EQUAL_STRING(" ",match->text);
}

void test_match_Text_function_given_text_is_Text_should_store_to_match_structure(void)
{
  Node *pattern=nodeA;
  int j=0;int i=0;
  char *text="a";
  
  MatchObject *matchObj=createMatchObj();
  Match *match=createMatch();
  
	j=matchText(&matchObj,&match,text,pattern,i,j);
  
  TEST_ASSERT_NOT_NULL(matchObj);
  TEST_ASSERT_NOT_NULL(match);
  TEST_ASSERT_EQUAL(1,matchObj->match);
  TEST_ASSERT_EQUAL(1,j);
  TEST_ASSERT_EQUAL(0,match->possition);
  TEST_ASSERT_EQUAL_STRING("a",match->text);
}
  
  
  
