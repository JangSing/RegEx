#include "unity.h"
#include "CustomAssertion.h"
#include "Node.h"
#include "Regex.h"

#include <stdlib.h>

void customTestMatches(int matchIndex,char *text,int length,int possition,MatchObject *actualMatch,int lineNo){
  if(actualMatch==NULL){
    CUSTOM_TEST_FAIL("There are nothing to be tested.");
  }
  else{
    if(actualMatch->ptr[matchIndex]==NULL){
      CUSTOM_TEST_FAIL("the No.%d of the match Element is Expected Non-NULL",matchIndex);
    }
    else{
      if(strcmp(text,actualMatch->ptr[matchIndex]->text)!=0)
        CUSTOM_TEST_FAIL("For match Element No.%d,Expected text %s Was %s.",matchIndex,text,actualMatch->ptr[matchIndex]->text);
      if(length != actualMatch->ptr[matchIndex]->length)
        CUSTOM_TEST_FAIL("For match Element No.%d,Expected length %d Was %d.",matchIndex,length,actualMatch->ptr[matchIndex]->length);
      if(possition != actualMatch->ptr[matchIndex]->possition)
        CUSTOM_TEST_FAIL("For match Element No.%d,Expected possition %d Was %d.",matchIndex,length,actualMatch->ptr[matchIndex]->possition);
    }
  }
}