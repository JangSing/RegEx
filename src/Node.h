#ifndef Node_H
#define Node_H

typedef struct Node_t Node;
struct Node_t{
  Node *next;
  char *data;
  int attribute;
};

#endif // Node_H
