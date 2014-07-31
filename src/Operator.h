#ifndef Operator_H
#define Operator_H
#include "OperatorToken.h"
#include "Token.h"
#include "Stack.h"


void executeAdd(Stack *dataStack);
void executeSub(Stack *dataStack);
void executeMul(Stack *dataStack);
void executeModulo(Stack *dataStack);
void executeDiv(Stack *dataStack);
void executeOr(Stack *dataStack);

#endif // Operator_H
