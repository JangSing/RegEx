#ifndef ErrorObject_H
#define ErrorObject_H

#include <stdarg.h>

typedef enum {
  ERR_REPEATED_NODE,
  ERR_NULL_NODE,
  ERR_UNKNOWN_TYPE
}ErrorCode;

typedef struct{
  char *errorMsg;
  ErrorCode errorCode;
}ErrorObject;

void throwError(ErrorCode errCode, char *msg, ...);

#endif // ErrorObject_H
