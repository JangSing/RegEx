#include "Match.h"
#include "ErrorObject.h"
#include <stdlib.h>
#include <stdio.h>

void matchDigit(MatchObject **matchObj,Match **match,char *text,int i,int *j){
  if(*matchObj==NULL || text==NULL)
    throwError(ERR_NULL_NODE,"matchObj/text cannot be NULL.");

  if(*(text+i)>=48 && *(text+i)<=57){
    if(*j==0){
      (*match)=createMatch();
      (*match)->possition=i;
    }
    (*match)->text[*j]=text[i];
    (*match)->text[(*j)+1]=0;
    (*matchObj)->match=1;
    (*j)++;
    (*match)->length=*j;
  }
  else{
    (*matchObj)->match=0;
  }

}
void matchCapAlpha(MatchObject **matchObj,Match **match,char *text,int i,int *j){
  if(*matchObj==NULL || text==NULL)
    throwError(ERR_NULL_NODE,"matchObj/text cannot be NULL.");
  if(*(text+i)>=65 && *(text+i)<=90){
    if(*j==0){
      (*match)=createMatch();
      (*match)->possition=i;
    }
    (*match)->text[*j]=text[i];
    (*match)->text[(*j)+1]=0;
    (*matchObj)->match=1;
    (*j)++;
    (*match)->length=*j;
  }
  else{
    (*matchObj)->match=0;
  }

}
void matchAlpha(MatchObject **matchObj,Match **match,char *text,int i,int *j){
  if(*matchObj==NULL || text==NULL)
    throwError(ERR_NULL_NODE,"matchObj/text cannot be NULL.");
  if(*(text+i)>=97 && *(text+i)<=122){
    if(*j==0){
      (*match)=createMatch();
      (*match)->possition=i;
    }
    (*match)->text[*j]=text[i];
    (*match)->text[(*j)+1]=0;
    (*matchObj)->match=1;
    (*j)++;
    (*match)->length=*j;
  }
  else{
    (*matchObj)->match=0;
  }

}
void matchWord(MatchObject **matchObj,Match **match,char *text,int i,int *j){
  if(*matchObj==NULL || text==NULL)
    throwError(ERR_NULL_NODE,"matchObj/text cannot be NULL.");
  if( (*(text+i)>=48 && *(text+i)<=57) || (*(text+i)>=65 && *(text+i)<=90) || (*(text+i)>=97 && *(text+i)<=122)){
    if(*j==0){
      (*match)=createMatch();
      (*match)->possition=i;
    }
    (*match)->text[*j]=text[i];
    (*match)->text[(*j)+1]=0;
    (*matchObj)->match=1;
    (*j)++;
    (*match)->length=*j;
  }
  else{
    (*matchObj)->match=0;
  }

}
void matchSpace(MatchObject **matchObj,Match **match,char *text,int i,int *j){
  if(*matchObj==NULL || text==NULL){
    throwError(ERR_NULL_NODE,"matchObj/text cannot be NULL.");
  }
  if(*(text+i)==32){
    if(*j==0){
      (*match)=createMatch();
      (*match)->possition=i;
    }
    (*match)->text[*j]=text[i];
    (*match)->text[(*j)+1]=0;
    (*matchObj)->match=1;
    (*j)++;
    (*match)->length=*j;
  }
  else{
    (*matchObj)->match=0;
  }

}
void matchText(MatchObject **matchObj,Match **match,char *text,Node *pattern,int i,int *j){
  if(*matchObj==NULL || pattern == NULL || text == NULL)
    throwError(ERR_NULL_NODE,"matchObj/pattern/text cannot be NULL.");
  if(*(text+i)==pattern->data){
    if(*j==0){
      (*match)=createMatch();
      (*match)->possition=i;
    }
    (*match)->text[*j]=text[i];
    (*match)->text[(*j)+1]=0;
    (*matchObj)->match=1;
    (*j)++;
    (*match)->length=*j;
  }
  else{
    (*matchObj)->match=0;
  }

}

void matchEle(MatchObject **matchObj,Match **match,char *text,Node *pattern,int i,int *j){
  if(*matchObj==NULL || pattern ==NULL || text==NULL)
    throwError(ERR_NULL_NODE,"matchObj/pattern/text cannot be NULL.");
  if(pattern->data<0xFF){
    matchText(matchObj,match,text,pattern,i,j);
  }
  else{
    switch(pattern->data){
      case DIGIT      :matchDigit(matchObj,match,text,i,j);break;
      case CAP_ALPHA  :matchCapAlpha(matchObj,match,text,i,j);break;
      case ALPHA      :matchAlpha(matchObj,match,text,i,j);break;
      case WORD       :matchWord(matchObj,match,text,i,j);break;
      case SPACE      :matchSpace(matchObj,match,text,i,j);break;
      default         :throwError(ERR_UNKNOWN_TYPE,"unknown data type.");break;
    }
  }
}


void checkMatches(MatchObject **matchObj,Match **match,int i,int *j){
  if(*matchObj==NULL || *match == NULL || j == NULL)
    throwError(ERR_NULL_NODE,"matchObj/match/j cannot be NULL.");
  if((*matchObj)->match){
    (*matchObj)->numOfMatch++;
    (*matchObj)->ptr[(*matchObj)->numOfMatch-1] = *match;
    (*matchObj)->ptr[(*matchObj)->numOfMatch]   = NULL;
  }
  else{
    (*matchObj)->ptr[(*matchObj)->numOfMatch]= NULL;
  }
  *j=0;
  (*matchObj)->match=0;
}

void checkForOneOrMore(MatchObject **matchObj,int *j,int *count){
  if(*matchObj==NULL || j == NULL || count == NULL)
    throwError(ERR_NULL_NODE,"matchObj/j/count cannot be NULL.");
  if(*count==0){
    *j=0;
  }
  else{
    (*matchObj)->match=1;
    *count=0;
  }
}

void checkForZeroOrOne(MatchObject **matchObj,int *j,int *count){
  if(*matchObj==NULL || j == NULL || count == NULL)
    throwError(ERR_NULL_NODE,"matchObj/j/count cannot be NULL.");
  if(*count>1){
    *j=0;
  }
  else{
    (*matchObj)->match=1;
    *count=0;
  }
}

void checkForRange(MatchObject **matchObj,int *j,int *count,int begin,int end){
  if(*matchObj==NULL || j == NULL || count == NULL)
    throwError(ERR_NULL_NODE,"matchObj/j/count cannot be NULL.");
  if(*count<begin || *count>end){
    *j=0;
  }
  else{
    (*matchObj)->match=1;
    *count=0;
  }
}

void checkForExact(MatchObject **matchObj,int *j,int *count,int begin){
  if(*matchObj==NULL || j == NULL || count == NULL)
    throwError(ERR_NULL_NODE,"matchObj/j/count cannot be NULL.");
  if(*count!=begin){
    *j=0;
  }
  else{
    (*matchObj)->match=1;
    *count=0;
  }
}
