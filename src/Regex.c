#include "Regex.h"
#include "LinkedList.h"
#include "Node.h"
#include <stdlib.h>
#include <stdio.h>

Match *matchObjectregEx(char *text,Node *pattern){
  if(text==NULL || pattern==NULL)
    return NULL;
  Match *match=malloc(sizeof(Match));
  
  // i=>textIndex j=>matchTextIndex
  int i=0,j=0;

  while(1){
    if(*(text+i)==0 || pattern==NULL){
      if(pattern!=NULL && *(text+i)==0){
        match=NULL;
        return match;
      }
      else if(pattern==NULL){
        if(*(text+i)==0){
          match->length=i;
          return match;
        }
      }
    }    
    else if(strcmp(pattern->data,"\\d")==0){
      if(*(text+i)>=48 && *(text+i)<=57){
        if(j==0)
          match->possition=i;  
        match->text[j]=text[i];
        match->text[j+1]=0;
      }
      else{
        match=NULL;
      }
    }   
    else if(strcmp(pattern->data,"\\A")==0){
      if(*(text+i)>=65 && *(text+i)<=90){
        if(j==0)
          match->possition=i; 
        match->text[j]=text[i];
        match->text[j+1]=0;
      }
      else{
        match=NULL;
      }
    }    
    else if(strcmp(pattern->data,"\\a")==0){
      if(*(text+i)>=97 && *(text+i)<=122){
        if(j==0)
          match->possition=i; 
        match->text[j]=text[i];
        match->text[j+1]=0;
      }
      else{
        match=NULL;
      }
    }
    else if(strcmp(pattern->data,"\\w")==0){
      if( (*(text+i)>=48 && *(text+i)<=57) || (*(text+i)>=65 && *(text+i)<=90) || (*(text+i)>=97 && *(text+i)<=122)){
        if(j==0)
          match->possition=i; 
        match->text[j]=text[i];
        match->text[j+1]=0;
      }
      else{
        match=NULL;
      }
    }
    else if(strcmp(pattern->data,"\\s")==0){
      if(*(text+i)==32){
        if(j==0)
          match->possition=i; 
        match->text[j]=text[i];
        match->text[j+1]=0;
      }
      else{
        match=NULL;
      }
    }
    i++;j++;
    pattern=pattern->next;
    
  }
  return match;

}