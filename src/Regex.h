#ifndef Regex_H
#define Regex_H

typedef struct{
  char *text;
  int possition;
  int length;
}Match;

typedef struct {
  int   match;
  int   numOfMatch;
  Match (*ptr)[];
}MatchObject;

void matchObjectregEx(char *text,char *pattern);

#endif // Regex_H
