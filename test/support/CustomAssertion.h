#ifndef CustomAssertion_H
#define CustomAssertion_H

#include "Node.h"
#include "Regex.h"

#define CUSTOM_TEST_FAIL(msg,...)              {                                                                              \
                                               char buffer[256];                                                              \
                                               sprintf(buffer,msg, ## __VA_ARGS__);                                           \
                                               UNITY_TEST_FAIL(lineNo, buffer);                                               \
                                               }

#define TEST_ASSERT_MATCH(matchIndex,text,length,possition,actualMatch)   \
                    customTestMatches(matchIndex,text,length,possition,actualMatch,__LINE__)

void customTestMatches(int matchIndex,char *text,int length,int possition,MatchObject *actualMatch,int lineNo);

#endif // CustomAssertion_H
