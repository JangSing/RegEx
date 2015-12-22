#include "Regex.h"
#include "Node.h"
#include "Match.h"
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
      if(*(text+i)!=0){
        while(*(text+i)!=0 ){
          if(*(text+i)==32 ){
            checkMatches(&matchObj,&match,i);
            matchObj=matchObjectRegEx(matchObj,text+i+1,startPattern);
            if(*(text+i+1)!=0)
              (matchObj->ptr[matchObj->numOfMatch-1]->possition)+=i+1;
          }
          i++;
        }
      }
      else{
        checkMatches(&matchObj,&match,i);
      }
      return matchObj;
    }
    else {
      if(*(text+i)!=0){
        do{
          if(pattern->data<0xFF){
            j=matchText(&matchObj,&match,text,pattern,i,j);
          }
          else{
            switch(pattern->data){
              case DIGIT      :j=matchDigit(&matchObj,&match,text,i,j);break;
              case CAP_ALPHA  :j=matchCapAlpha(&matchObj,&match,text,i,j);break;
              case ALPHA      :j=matchAlpha(&matchObj,&match,text,i,j);break;
              case WORD       :j=matchWord(&matchObj,&match,text,i,j);break;
              case SPACE      :j=matchSpace(&matchObj,&match,text,i,j);break;
              default         :(matchObj->match)=0;j=0;break;
            }
          }
          if(pattern->attribute==ATT_ASTERISK && !(matchObj->match)){
            matchObj->match=1;
            break;
          }
          else if(pattern->attribute==ATT_PLUS && !(matchObj->match)){
            if(count==0){
              j=0;
              while(pattern->next!=NULL){
                pattern=pattern->next;
              }
            }
            else{
              matchObj->match=1;
              count=0;
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
        (matchObj->match)=0;
      }
    }
    pattern=pattern->next;
  }
}