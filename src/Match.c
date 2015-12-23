#include "Match.h"
#include "ErrorObject.h"
#include <stdlib.h>

int matchDigit(MatchObject **matchObj,Match **match,char *text,int i,int j){
  if(*matchObj==NULL || *match==NULL || text==NULL)
    throwError(ERR_NULL_NODE,"matchObj/match/text cannot be NULL.");

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
  }

  return j;
}
int matchCapAlpha(MatchObject **matchObj,Match **match,char *text,int i,int j){
  if(*matchObj==NULL || *match==NULL || text==NULL)
    throwError(ERR_NULL_NODE,"matchObj/match/text cannot be NULL.");
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
  }

  return j;
}
int matchAlpha(MatchObject **matchObj,Match **match,char *text,int i,int j){
  if(*matchObj==NULL || *match==NULL || text==NULL)
    throwError(ERR_NULL_NODE,"matchObj/match/text cannot be NULL.");
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
  }

  return j;
}
int matchWord(MatchObject **matchObj,Match **match,char *text,int i,int j){
  if(*matchObj==NULL || *match==NULL || text==NULL)
    throwError(ERR_NULL_NODE,"matchObj/match/text cannot be NULL.");
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
  }

  return j;
}
int matchSpace(MatchObject **matchObj,Match **match,char *text,int i,int j){
  if(*matchObj==NULL || *match==NULL || text==NULL)
    throwError(ERR_NULL_NODE,"matchObj/match/text cannot be NULL.");
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
  }

  return j;
}
int matchText(MatchObject **matchObj,Match **match,char *text,Node *pattern,int i,int j){
  if(*matchObj==NULL || *match==NULL || pattern ==NULL)
    throwError(ERR_NULL_NODE,"matchObj/match/text/pattern cannot be NULL.");
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

void checkForOneOrMore(MatchObject **matchObj,Node **pattern,int *j,int *count){
  if(*count==0){
    *j=0;
    while((*pattern)->next!=NULL){
      *pattern=(*pattern)->next;
    }
  }
  else{
    (*matchObj)->match=1;
    *count=0;
  }
}

void checkForZeroOrOne(MatchObject **matchObj,Node **pattern,int *j,int *count){
  if(*count>1){
    *j=0;
    while((*pattern)->next!=NULL){
      *pattern=(*pattern)->next;
    }
  }
  else{
    (*matchObj)->match=1;
    *count=0;
  }
}




