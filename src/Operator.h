#ifndef Operator_H
#define Operator_H
#include "OperatorToken.h"
#include "Token.h"
#include "Stack.h"
#include "ErrorCode.h"

void getInfixValues(int *left, int *right, Stack *dataStack);
void pushNewNumber(int result, Stack *dataStack);
void executeAdd(Stack *dataStack);
void executeSub(Stack *dataStack);
void executeMul(Stack *dataStack);
void executeModulo(Stack *dataStack);
void executeDiv(Stack *dataStack);
void executeOr(Stack *dataStack);
void executeXor(Stack *dataStack);
void executeAnd(Stack *dataStack);
void executeBitAnd(Stack *dataStack);
void executeBitOr(Stack *dataStack);
void executeShiftLeft(Stack *dataStack);
void executeShiftRight(Stack *dataStack);
void executeLesser(Stack *dataStack);
void executeGreater(Stack *dataStack);
void executeEqual(Stack *dataStack);

#endif // Operator_H
