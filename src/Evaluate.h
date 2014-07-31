#ifndef Evaluate_H
#define Evaluate_H
#include "StringObject.h"
#include "OperatorToken.h"
#include "NumberToken.h"
#include "Stack.h"

void ChooseTheOperation(  Operator *opr, Stack *dataStack );
void tryToPushOperatorAndEvaluate( Stack *operatorStack, Operator *opr, Stack *dataStack );
void ChooseTheAffix(Stack *dataStack , Operator *opr);
int calculation(Number *num1 , Operator *opr , Number *num2);

#endif // ShuntingYard_H
