#ifndef Regex_H
#define Regex_H

#include "LinkedList.h"

typedef struct{
  char text[0];
  int possition;
  int length;
}Match;

typedef struct {
  int   match;
  int   numOfMatch;
  Match (*ptr)[];
}MatchObject;

Match *matchObjectregEx(char *text,LinkedList *pattern);

#endif // Regex_H
