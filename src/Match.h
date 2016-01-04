#ifndef Match_H
#define Match_H

#include "Regex.h"

void matchDigit(MatchObject **matchObj,Match **match,char *text,int i,int *j);
void matchCapAlpha(MatchObject **matchObj,Match **match,char *text,int i,int *j);
void matchAlpha(MatchObject **matchObj,Match **match,char *text,int i,int *j);
void matchWord(MatchObject **matchObj,Match **match,char *text,int i,int *j);
void matchSpace(MatchObject **matchObj,Match **match,char *text,int i,int *j);
void matchText(MatchObject **matchObj,Match **match,char *text,Node *pattern,int i,int *j);
void checkMatches(MatchObject **matchObj,Match **match,int i,int *j);
void checkForOneOrMore(MatchObject **matchObj,Node **pattern,int *j,int *count);
void checkForZeroOrOne(MatchObject **matchObj,Node **pattern,int *j,int *count);
void checkForRange(MatchObject **matchObj,Node **pattern,int *j,int *count,int begin,int end);
void checkForExact(MatchObject **matchObj,Node **pattern,int *j,int *count,int begin);

#endif // Match_H
