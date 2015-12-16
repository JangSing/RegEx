#ifndef Match_H
#define Match_H

#include "Regex.h"

int matchDigit(MatchObject **matchObj,Match **match,char *text,int i,int j);
int matchCapAlpha(MatchObject **matchObj,Match **match,char *text,int i,int j);
int matchAlpha(MatchObject **matchObj,Match **match,char *text,int i,int j);
int matchWord(MatchObject **matchObj,Match **match,char *text,int i,int j);
int matchSpace(MatchObject **matchObj,Match **match,char *text,int i,int j);
int matchText(MatchObject **matchObj,Match **match,char *text,Node *pattern,int i,int j);
void checkMatches(MatchObject **matchObj,Match **match,int i);

#endif // Match_H
