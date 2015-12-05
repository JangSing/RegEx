#ifndef Regex_H
#define Regex_H

#include "Node.h"
#include "LinkedList.h"

typedef struct{
  int possition;
  int length;
  char text[0];
}Match;

typedef struct {
  int   match;
  int   numOfMatch;
  Match (*ptr)[];
}MatchObject;

Match *matchObjectregEx(char *text,Node *pattern);

#endif // Regex_H
