#include "Regex.h"
#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>

Match *matchObjectregEx(char *text,LinkedList *pattern){
  Match *match=malloc(sizeof(Match));
  ListElement *listEle;
  int i=0;
  
  listEle=pattern->head;
  // printf("%s\n",listEle->next->value);

  while(1){
    if(*(text+i)==0 || listEle==NULL){
      if(listEle==NULL && (*(text+i)==0 || *(text+i)==32))
        return match;
      else
        return NULL;
    }    
    else if(strcmp(listEle->value,"\\d")==0){
      if(*(text+i)>=48 && *(text+i)<=57){
        match->text[i]=text[i];
        match->text[i+1]=0;
      }
      else{
        return NULL;
      }
    }   
    else if(strcmp(listEle->value,"\\A")==0){
      if(*(text+i)>=65 && *(text+i)<=90){
        match->text[i]=text[i];
        match->text[i+1]=0;
      }
      else{
        return NULL;
      }
    }    
    else if(strcmp(listEle->value,"\\a")==0){
      if(*(text+i)>=97 && *(text+i)<=122){
        match->text[i]=text[i];
        match->text[i+1]=0;
      }
      else{
        return NULL;
      }
    }
    else if(strcmp(listEle->value,"\\w")==0){
      if( (*(text+i)>=48 && *(text+i)<=57) || (*(text+i)>=65 && *(text+i)<=90) || (*(text+i)>=97 && *(text+i)<=122)){
        match->text[i]=text[i];
        match->text[i+1]=0;
      }
      else{
        return NULL;
      }
    }
    else if(strcmp(listEle->value,"\\s")==0){
      if(*(text+i)==32){
        match->text[i]=text[i];
        match->text[i+1]=0;
      }
      else{
        return NULL;
      }
    }
    i++;
    listEle=listEle->next;
  }

}