#ifndef Node_H
#define Node_H

typedef struct Node_t Node;
struct Node_t{
  int   data;
  int   attribute;
  int   begin;
  int   end;
  Node  *next;
};

#endif // Node_H
