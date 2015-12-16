#include "Match.h"
#include <stdlib.h>

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
    (*matchObj)->match=0;
    j=0;
  }
  
  return j;
}


void checkMatches(MatchObject **matchObj,Match **match,int i){
  if((*matchObj)->match){
    (*match)->length=i;
    (*matchObj)->numOfMatch++;
    (*matchObj)->ptr[(*matchObj)->numOfMatch-1] = *match;
  }
  else{
    (*matchObj)->ptr[(*matchObj)->numOfMatch]= NULL;
  }
}