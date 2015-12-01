#ifndef LinkedList_H
#define LinkedList_H

typedef struct ListElement_t{
  struct ListElement_t *next;
  void *value;
}ListElement;

typedef struct {
  ListElement *head;
  ListElement *tail;
  int length;
}LinkedList;

LinkedList *createLinkedList();
ListElement *createListElement(char *value);

void AddLast(ListElement *NewEle,LinkedList *List );



#endif // LinkedList_H
