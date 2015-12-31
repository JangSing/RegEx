#ifndef Node_H
#define Node_H

typedef struct Node_t Node;
struct Node_t{
  Node  *next;
  int   data;
  int   attribute;
  int   begin;
  int   end;
};

#endif // Node_H
