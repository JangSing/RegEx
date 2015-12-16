#ifndef Regex_H
#define Regex_H

#include "Node.h"
#include "LinkedList.h"

#define DIGIT       0x100
#define WORD        0x200
#define CAP_WORD    0x300
#define ALPHA       0x400
#define CAP_ALPHA   0x500
#define SPACE       0x600

#define ATT_ASTERISK  1
#define ATT_PLUS      2
#define ATT_QUESTION  3


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
Match *createMatch();
int matchDigit(MatchObject **matchObj,Match **match,char *text,int i,int j);
int matchCapAlpha(MatchObject **matchObj,Match **match,char *text,int i,int j);
int matchAlpha(MatchObject **matchObj,Match **match,char *text,int i,int j);
int matchWord(MatchObject **matchObj,Match **match,char *text,int i,int j);
int matchSpace(MatchObject **matchObj,Match **match,char *text,int i,int j);
int matchText(MatchObject **matchObj,Match **match,char *text,Node *pattern,int i,int j);
MatchObject *matchObjectRegEx(MatchObject *matchObj,char *text,Node *pattern);

#endif // Regex_H
