#ifndef Operator_H
#define Operator_H
#include "OperatorToken.h"
#include "Token.h"
#include "Stack.h"
#include "ErrorCode.h"

void getInfixValues(int *left, int *right, Stack *dataStack);

void pushNewNumber(int result, Stack *dataStack);
void executeLesser(Stack *dataStack, Stack *operatorStack);
void executeGreater(Stack *dataStack, Stack *operatorStack);
void executeEqual(Stack *dataStack, Stack *operatorStack);
void sillyFunctionAgain();

void executeAdd(Stack *dataStack, Stack *operatorStack);
void executeSub(Stack *dataStack, Stack *operatorStack);
void executeMul(Stack *dataStack, Stack *operatorStack);
void executeModulo(Stack *dataStack, Stack *operatorStack);
void executeDiv(Stack *dataStack, Stack *operatorStack);
void executeOr(Stack *dataStack, Stack *operatorStack);
void executeXor(Stack *dataStack, Stack *operatorStack);
void executeAnd(Stack *dataStack, Stack *operatorStack);
void executeBitAnd(Stack *dataStack, Stack *operatorStack);
void executeBitOr(Stack *dataStack, Stack *operatorStack);
void executeShiftLeft(Stack *dataStack, Stack *operatorStack);
void executeShiftRight(Stack *dataStack, Stack *operatorStack);
void executeClosingBracket( Stack *dataStack, Stack *operatorStack);
void executePrefixSub(Stack *dataStack, Stack *operatorStack);
void executePrefixAdd(Stack *dataStack, Stack *operatorStack);
void executeNot(Stack *dataStack, Stack *operatorStack);
void executeBitNot(Stack *dataStack, Stack *operatorStack);

#endif // Operator_H
