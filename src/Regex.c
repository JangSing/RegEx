#include "Regex.h"
#include "Node.h"
#include "Match.h"
#include "ErrorObject.h"
#include <stdlib.h>
#include <stdio.h>

#define ptrIndex  (matchObj->numOfMatch)-1

MatchObject *createMatchObj(){
  MatchObject *matchObj=malloc(sizeof(MatchObject)+sizeof(Match)+sizeof(char));

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

void endOfTextOrSpace(MatchObject **matchObj,Match **match,char *text,Node *startPattern,int *i){
  if(*(text+(*i))!=32){
    (*matchObj)->match=0;
  }
  checkMatches(matchObj,match,*i);
  while(*(text+(*i))!=0 ){
    int matchNo=(*matchObj)->numOfMatch;
    if(*(text+(*i))==32 ){
      (*matchObj)=matchObjectRegEx((*matchObj),text+(*i)+1,startPattern);
      if( *(text+(*i)+1)!=0){
        ((*matchObj)->ptr[matchNo]->possition)+=(*i)+1;
      }
      break;
    }
    (*i)++;
  }
}

MatchObject *possitionCalculate(MatchObject *matchObj){
  int index=0;
  while(matchObj->ptr[index+1]!=NULL){
    matchObj->ptr[index+1]->possition+=matchObj->ptr[index]->possition;
    index++;
  }
  return matchObj;
}

MatchObject *matchObjectRegEx(MatchObject *matchObj,char *text,Node *pattern){
  if(text==NULL || pattern==NULL)
    return NULL;
  Match *match=createMatch();
  // i=>textIndex j=>matchTextIndex
  int i=0;int j=0;
  int count=0;

  Node *startPattern=pattern;
  while(1){
    if(pattern==NULL){
      if(*(text+i)!=0)
        endOfTextOrSpace(&matchObj,&match,text,startPattern,&i);
      else
        checkMatches(&matchObj,&match,i);
      break;
    }
    else {
      if(*(text+i)!=0){
        do{
          if(pattern->data<0xFF){
            matchText(&matchObj,&match,text,pattern,i,&j);
          }
          else{
            switch(pattern->data){
              case DIGIT      :matchDigit(&matchObj,&match,text,i,&j);break;
              case CAP_ALPHA  :matchCapAlpha(&matchObj,&match,text,i,&j);break;
              case ALPHA      :matchAlpha(&matchObj,&match,text,i,&j);break;
              case WORD       :matchWord(&matchObj,&match,text,i,&j);break;
              case SPACE      :matchSpace(&matchObj,&match,text,i,&j);break;
              default         :throwError(ERR_UNKNOWN_TYPE,"unknown data type.");break;
            }
          }
          if(!matchObj->match && pattern->attribute!=0){
            switch(pattern->attribute){
              case ATT_ASTERISK :matchObj->match=1;count=0;break;
              case ATT_PLUS     :checkForOneOrMore(&matchObj,&pattern,&j,&count);break;
              case ATT_QUESTION :checkForZeroOrOne(&matchObj,&pattern,&j,&count);break;
              case ATT_RANGE    :checkForRange(&matchObj,&pattern,&j,&count,pattern->begin,pattern->end);break;
              case ATT_EXACT    :checkForExact(&matchObj,&pattern,&j,&count,pattern->begin);break;
              default           :break;
            }
            break;
          }
          if(pattern->attribute!=0)
            count++;
          i++;
        }while(pattern->attribute!=0);
      }
      else{
        j=0;
        matchObj->match=0;
      }
    }
    pattern=pattern->next;
  }
  return matchObj;
}

void regexObject(MatchObject **matchObj,char *text,Node *pattern){
  *matchObj=matchObjectRegEx(*matchObj,text,pattern);
  *matchObj=possitionCalculate(*matchObj);
}