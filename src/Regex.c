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
Match *createMatch(){
  Match *match=malloc(sizeof(Match)+sizeof(char));

  match->possition=0;
  match->length=0;
  match->text[0]=0;

  return match;
}
int matchDigit(MatchObject **matchObj,Match **match,char *text,int i,int j){
  if(*(text+i)>=48 && *(text+i)<=57){
    if(j==0)
      (*match)->possition=i;
    (*match)->text[j]=text[i];
    (*match)->text[j+1]=0;
    (*matchObj)->match=1;
    j++;
  }
  else{
    *match=NULL;
    (*matchObj)->match=0;
    j=0;
  }
  
  return j;
}
int matchCapAlpha(MatchObject **matchObj,Match **match,char *text,int i,int j){
  if(*(text+i)>=65 && *(text+i)<=90){
    if(j==0)
      (*match)->possition=i;
    (*match)->text[j]=text[i];
    (*match)->text[j+1]=0;
    (*matchObj)->match=1;
    j++;
  }
  else{
    *match=NULL;
    (*matchObj)->match=0;
    j=0;
  }
  
  return j;
}
int matchAlpha(MatchObject **matchObj,Match **match,char *text,int i,int j){
  if(*(text+i)>=97 && *(text+i)<=122){
    if(j==0)
      (*match)->possition=i;
    (*match)->text[j]=text[i];
    (*match)->text[j+1]=0;
    (*matchObj)->match=1;
    j++;
  }
  else{
    *match=NULL;
    (*matchObj)->match=0;
    j=0;
  }
  
  return j;
}
int matchWord(MatchObject **matchObj,Match **match,char *text,int i,int j){
  if( (*(text+i)>=48 && *(text+i)<=57) || (*(text+i)>=65 && *(text+i)<=90) || (*(text+i)>=97 && *(text+i)<=122)){
    if(j==0)
      (*match)->possition=i;
    (*match)->text[j]=text[i];
    (*match)->text[j+1]=0;
    (*matchObj)->match=1;
    j++;
  }
  else{
    *match=NULL;
    (*matchObj)->match=0;
    j=0;
  }
  
  return j;
}
int matchSpace(MatchObject **matchObj,Match **match,char *text,int i,int j){
  if(*(text+i)==32){
    if(j==0)
      (*match)->possition=i;
    (*match)->text[j]=text[i];
    (*match)->text[j+1]=0;
    (*matchObj)->match=1;
    j++;
  }
  else{
    *match=NULL;
    (*matchObj)->match=0;
    j=0;
  }
  
  return j;
}
int matchText(MatchObject **matchObj,Match **match,char *text,Node *pattern,int i,int j){
  if(*(text+i)==pattern->data){
    if(j==0)
      (*match)->possition=i;
    (*match)->text[j]=text[i];
    (*match)->text[j+1]=0;
    (*matchObj)->match=1;
    j++;
  }
  else{
    *match=NULL;
    (*matchObj)->match=0;
    j=0;
  }
  
  return j;
}

MatchObject *matchObjectRegEx(MatchObject *matchObj,char *text,Node *pattern){
  if(text==NULL || pattern==NULL)
    return NULL;
  Match *match=createMatch();

  // i=>textIndex j=>matchTextIndex
  int i=0;int j=0;

  Node *startPattern=pattern;

  while(1){
    if(pattern==NULL){
      if(*(text+i)!=0){
        while(*(text+i)!=0 ){ 
          if(*(text+i)==32 ){
            if(matchObj->match){
              match->length=i;
              matchObj->numOfMatch++;
              matchObj->ptr[matchObj->numOfMatch-1] = match;
            }
            else{
              matchObj->ptr[matchObj->numOfMatch]=match;
            }
            matchObj=matchObjectRegEx(matchObj,text+i+1,startPattern);
            if(*(text+i+1)!=0){
              (matchObj->ptr[matchObj->numOfMatch-1]->possition)+=i+1;
              
            }
          }
          i++;    
        }
      }
      else{
        if(match!=NULL){
          match->length=i;
          matchObj->numOfMatch++;
          matchObj->ptr[matchObj->numOfMatch-1] = match;
        }
        else{
          matchObj->ptr[matchObj->numOfMatch]=match;
        }
      }
      return matchObj;
    }
    else {
      if(*(text+i)!=0){
        // do{
          if(pattern->data<0xFF)
            j=matchText(&matchObj,&match,text,pattern,i,j);
          else{
            switch(pattern->data){
              case DIGIT      :j=matchDigit(&matchObj,&match,text,i,j);break;
              case CAP_ALPHA  :j=matchCapAlpha(&matchObj,&match,text,i,j);break;
              case ALPHA      :j=matchAlpha(&matchObj,&match,text,i,j);break;
              case WORD       :j=matchWord(&matchObj,&match,text,i,j);break;
              case SPACE      :j=matchSpace(&matchObj,&match,text,i,j);break;
              default         :match=NULL;j=0;break;
            }
          }
          
          
        // }while(pattern->attribute!=0);
      }
      else
        match=NULL;
      i++;
    }
    pattern=pattern->next;
  }
}