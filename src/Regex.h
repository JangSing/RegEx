#ifndef Regex_H
#define Regex_H

#include "Node.h"

#define DIGIT       0x100
#define WORD        0x200
#define CAP_WORD    0x300
#define ALPHA       0x400
#define CAP_ALPHA   0x500
#define SPACE       0x600

#define ATT_ASTERISK  1
#define ATT_PLUS      2
#define ATT_QUESTION  3
#define ATT_RANGE     4
#define ATT_EXACT     5



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
void endOfTextOrSpace(MatchObject **matchObj,Match **match,char *text,Node *startPattern,int *i);
void attributeSelect(MatchObject **matchObj,Node *pattern,int *j,int *count);
void patternPathDecision(MatchObject **matchObj, Node **pattern,Node *startPattern,Node *retryPattern,
                                          int *patternIndex,int *retryEn,int retryIndex,int *newRetryPoss,int *endOfBranch,int *i,int *j);
int maxBranch(Node *pattern);
MatchObject *matchObjectRegEx(MatchObject *matchObj,char *text,Node *pattern);

#endif // Regex_H
