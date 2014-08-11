#ifndef Evaluate_H
#define Evaluate_H
#include "StringObject.h"
#include "OperatorToken.h"
#include "NumberToken.h"
#include "Stack.h"

void tryToPushOperatorAndEvaluate(  Operator *opr, Stack *operatorStack, Stack *dataStack );
int evaluate(String *expression);
void doOperatorStackRewinding(Stack *dataStack , Stack *operatorStack);
void evaluatePrefixesAndNumber(Token *token, String *expression, Stack *dataStack, Stack *operatorStack);
Token *convertToPrefixIfNotAlready(Operator *op);


#endif // ShuntingYard_H
