#include "Regex.h"
#include "Node.h"
#include "Match.h"
#include "ErrorObject.h"
#include <stdlib.h>
#include <stdio.h>

MatchObject *createMatchObj(){
  MatchObject *matchObj=malloc(sizeof(MatchObject)+sizeof(Match)+sizeof(char)+sizeof(Node));

  matchObj->match=0;
  matchObj->numOfMatch=0;
  matchObj->ptr[0]=NULL;
  return matchObj;
}
Match *createMatch(){
  Match *match=malloc(sizeof(Match)+sizeof(char));

  match->possition=0;
  match->length=0;
  match->text[0]=0;
  return match;
}

void attributeSelect(MatchObject **matchObj,Node *pattern,int *j,int *count){
  switch(pattern->attribute){
    case ATT_ASTERISK :(*matchObj)->match=1;count=0;break;
    case ATT_PLUS     :checkForOneOrMore(matchObj,j,count);break;
    case ATT_QUESTION :checkForZeroOrOne(matchObj,j,count);break;
    case ATT_RANGE    :checkForRange(matchObj,j,count,pattern->begin,pattern->end);break;
    case ATT_EXACT    :checkForExact(matchObj,j,count,pattern->begin);break;
    default           :break;
  }
}

MatchObject *matchObjectRegEx(MatchObject *matchObj,char *text,Node *pattern){
  if(text==NULL || pattern==NULL)
    return NULL;
  Match *match;
  int retryEn=0;int firstRetry=1;
  // i=>textIndex j=>matchTextIndex
  int i=0;int j=0;int patternIndex=0;
  int retryAnchor=0;int matchAnchor=0;
  int count=0;
  Node *startPattern=pattern;Node *retryPattern;

  while(1){
    if(pattern==NULL){
      checkMatches(&matchObj,&match,i,&j);
      pattern=startPattern;
      if(*(text+i)==0){
        break;
      }
    }
    else {
      if(*(text+i)!=0){
        do{
          matchEle(&matchObj,&match,text,pattern,i,&j);
          if(!matchObj->match && pattern->attribute!=0){
            attributeSelect(&matchObj,pattern,&j,&count);
            break;
          }
          if(pattern->attribute!=0)
            count++;
          i++;
        }while(pattern->attribute!=0);

        if(matchObj->match){
          patternIndex=0;
          pattern=pattern->next[patternIndex];
        }
        else{
          pattern=startPattern;
          j=0;
        }


      }
      else{
        j=0;
        matchObj->match=0;
        break;
      }
    }
  }
  return matchObj;
}

// void regexObject(MatchObject **matchObj,char *text,Node *pattern){
  // *matchObj=matchObjectRegEx(*matchObj,text,pattern);
  // *matchObj=possitionCalculate(*matchObj);
// }

// void endOfTextOrSpace(MatchObject **matchObj,Match **match,char *text,Node *startPattern,int *i){
  // if(*(text+(*i))!=32){
    // (*matchObj)->match=0;
  // }
  // checkMatches(matchObj,match,*i);
  // while(*(text+(*i))!=0 ){
    // int matchNo=(*matchObj)->numOfMatch;
    // if(*(text+(*i))==32 ){
      // (*matchObj)=matchObjectRegEx((*matchObj),text+(*i)+1,startPattern);
      // if( *(text+(*i)+1)!=0 && (*matchObj)->ptr[matchNo]!=NULL){
        // ((*matchObj)->ptr[matchNo]->possition)+=(*i)+1;
      // }
      // break;
    // }
    // (*i)++;
  // }
// }

// MatchObject *possitionCalculate(MatchObject *matchObj){
  // int index=0;

  // if(matchObj->ptr[index]!=NULL){
    // while(matchObj->ptr[index+1]!=NULL){
      // matchObj->ptr[index+1]->possition+=matchObj->ptr[index]->possition;
      // index++;
    // }
  // }
  // return matchObj;
// }