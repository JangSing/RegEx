#include "Regex.h"
#include "LinkedList.h"
#include "Node.h"
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

MatchObject *matchObjectregEx(MatchObject *matchObj,char *text,Node *pattern){
  if(text==NULL || pattern==NULL)
    return NULL;
  Match *match=malloc(sizeof(Match)+sizeof(char));

  // i=>textIndex j=>matchTextIndex
  int i=0,j=0;

  Node *startPattern=pattern;

  while(1){
    if(*(text+i)==0 || pattern==NULL){
      if(pattern!=NULL && *(text+i)==0){
        match=NULL;
      }
      else if(pattern==NULL){
        if(*(text+i)==0){
          match->length=i;
        }
        else{
          while(*(text+i)!=0){
            if(*(text+i)==32){
              match->length=i;
              // match->possition=i;
              matchObj->numOfMatch++;
              matchObj->ptr[ptrIndex] = match;
              i++;
              if(*(text+i)==0){
                match->length=i-1;
                matchObj->numOfMatch++;
                matchObj->ptr[ptrIndex] = match;
                return matchObj;
              }
              matchObj=matchObjectregEx(matchObj,text+i,startPattern);
              matchObj->ptr[ptrIndex]->possition+=i;
              return matchObj;
            }
            i++;
          }
          match=NULL;
        }
      }
      break;
    }
    else if(strcmp(pattern->data,"\\d")==0){
      if(*(text+i)>=48 && *(text+i)<=57){
        if(j==0)
          match->possition=i;
        match->text[j]=text[i];
        match->text[j+1]=0;
        j++;
      }
      else{
        match=NULL;
        j=0;
      }
    }
    else if(strcmp(pattern->data,"\\A")==0){
      if(*(text+i)>=65 && *(text+i)<=90){
        if(j==0)
          match->possition=i;
        match->text[j]=text[i];
        match->text[j+1]=0;
        j++;
      }
      else{
        match=NULL;
        j=0;
      }
    }
    else if(strcmp(pattern->data,"\\a")==0){
      if(*(text+i)>=97 && *(text+i)<=122){
        if(j==0)
          match->possition=i;
        match->text[j]=text[i];
        match->text[j+1]=0;
        j++;
      }
      else{
        match=NULL;
        j=0;
      }
    }
    else if(strcmp(pattern->data,"\\w")==0){
      if( (*(text+i)>=48 && *(text+i)<=57) || (*(text+i)>=65 && *(text+i)<=90) || (*(text+i)>=97 && *(text+i)<=122)){
        if(j==0)
          match->possition=i;
        match->text[j]=text[i];
        match->text[j+1]=0;
        j++;
      }
      else{
        match=NULL;
        j=0;
      }
    }
    else if(strcmp(pattern->data,"\\s")==0){
      if(*(text+i)==32){
        if(j==0)
          match->possition=i;
        match->text[j]=text[i];
        match->text[j+1]=0;
        j++;
      }
      else{
        match=NULL;
        j=0;
      }
    }
    else{
      match=NULL;
      j=0;
    }
    i++;
    pattern=pattern->next;

  }
  matchObj->numOfMatch++;
  matchObj->ptr[ptrIndex] = match;
  return matchObj;

}