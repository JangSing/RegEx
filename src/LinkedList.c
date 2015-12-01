#include "LinkedList.h"
#include <malloc.h>
#include <stdio.h>
#include <assert.h>

LinkedList *createLinkedList(){
  LinkedList *list;
  list = malloc(sizeof(LinkedList));
  assert(list != NULL);

  list -> head   = NULL;
  list -> tail   = NULL;
  list -> length = 0;

  return list;
}

ListElement *createListElement(char *value){

  ListElement *NewNode= malloc(sizeof(ListElement));
  assert(NewNode != NULL);

  NewNode -> value = value;
  NewNode -> next = NULL;

  return NewNode;
}

void AddLast(ListElement *NewEle,LinkedList *List ){

  if(List -> head == NULL && List -> tail == NULL){
    List -> head = NewEle;
    List -> tail = List -> head;
    (List->length)++;
  }
  else if(NewEle==NULL){}

  else {
    List -> tail->next=NewEle;
    List -> tail =List -> tail->next;
    (List->length)++;
  }
}





