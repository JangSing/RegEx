#ifndef CustomAssertion_H
#define CustomAssertion_H

#include "Node.h"

#define CUSTOM_TEST_FAIL(msg,...)              {                                                                              \
                                               char buffer[256];                                                              \
                                               sprintf(buffer,msg, ## __VA_ARGS__);                                           \
                                               UNITY_TEST_FAIL(lineNo, buffer);                                               \
                                               }

#define TEST_ASSERT_ROOT(leftNode, rootData, rightNode, actualNode)      \
                    customTestRoot(leftNode, rootData, rightNode, actualNode, __LINE__)

#define TEST_ASSERT_BALANCE(expectBalance, actual)      \
                    customTestBalance(expectBalance, actual, __LINE__)


void customTestRoot(Node *leftNode,int rootData,Node *rightNode,Node *actualNode,int lineNo);

void customTestBalance(int expectBalance,Node *actual, int lineNo);


#endif // CustomAssertion_H
