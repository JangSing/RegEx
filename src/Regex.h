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
  Match *ptr[];
}MatchObject;

MatchObject *createMatchObj();
MatchObject *matchObjectregEx(MatchObject *matchObj,char *text,Node *pattern);

#endif // Regex_H
