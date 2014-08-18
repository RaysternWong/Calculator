#include "ErrorCode.h"
#include <stdio.h>

void dumpErrorCode(ErrorCode err) {
  switch(err) {
    case ERR_NO_ERROR:
      printf("\nERR_NO_ERROR (%d)\n", err);
      break;
    case ERR_INCOMPLETE_NUMBER:
      printf("\nERR_INCOMPLETE_NUMBER (%d)\n", err);
      break;
    case ERR_NOT_NUMBER_TOKEN:
      printf("\nERR_NOT_NUMBER_TOKEN (%d)\n", err);
      break;
    case ERR_STACK_EMPTY:
      printf("\nERR_STACK_EMPTY (%d)\n", err);
      break;
    case ERR_STACK_FULL:
      printf("\nERR_STACK_FULL (%d)\n", err);
      break;
    case ERR_UNKNOWN_OPERATOR:
      printf("\nERR_UNKNOWN_OPERATOR (%d)\n", err);
      break;
    case ERR_NOT_PREFIX_OPERATOR:
      printf("\nERR_NOT_PREFIX_OPERATOR (%d)\n", err);
      break;
    case ERR_NOT_EXPECTING_PREFIX_OPERATOR:
      printf("\nERR_NOT_EXPECTING_PREFIX_OPERATOR (%d)\n", err);
      break;
    case ERR_IDENTIFIER_NOT_SUPPORT:
      printf("\nERR_IDENTIFIER_NOT_SUPPORT (%d)\n", err);
      break;
    case ERR_EXPECTING_NUMBER:
      printf("\nERR_EXPECTING_NUMBER (%d)\n", err);
      break;
    case ERR_NO_OPENING_BRACKET:
      printf("\nERR_NO_OPENING_BRACKET (%d)\n", err);
      break;
    case ERR_NO_CLOSING_BRACKET:
      printf("\nERR_NO_CLOSING_BRACKET (%d)\n", err);
      break;
    case ERR_UNBALANCE_BRACKET:
      printf("\nERR_UNBALANCE_BRACKET (%d)\n", err);
      break;
    case ERR_NOT_EXPECTING_NUMBER:
      printf("\nERR_NOT_EXPECTING_NUMBER (%d)\n", err);
      break;
    case ERR_NO_NUMBER:
      printf("\nERR_NO_NUMBER (%d)\n", err);
      break;
    default:
      printf("\nUnknown Error (%d)\n", err);
      break;
  }
}