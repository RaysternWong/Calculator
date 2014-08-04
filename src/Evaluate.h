#ifndef Evaluate_H
#define Evaluate_H
#include "StringObject.h"
#include "OperatorToken.h"
#include "NumberToken.h"
#include "Stack.h"


void verifyAllStacksAreEmpty(Stack *dataStack, Stack *operatorStack);
void tryToPushOperatorAndEvaluate(  Operator *opr, Stack *operatorStack, Stack *dataStack );
void doOperatorStackRewinding ( Stack *dataStack , Stack *operatorStack );
int evaluate(String *expression);


#endif // ShuntingYard_H
