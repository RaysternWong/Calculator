#include "Operator.h"
#include <stdio.h>
#include "Debug.h"
#include "Token.h"
#include "Stack.h"
#include "NumberToken.h"
#include "OperatorToken.h"
#include "Operator.h"
#include "TokenDebug.h"
#include "CException.h"
#include "ErrorCode.h"

/*
	In this function, is the result that are Pop from the stack and store it in the 
	numLeft and numRight first. Then this function will check whether the result that 
	are pop-ed are NULL or not, or it is not a number token, and finally only store it into
	the pointer that are pointing at the pop value.
	
	Input:
	- numLeft, numRight
	
	Output:
	- left, right
*/
void getInfixValues(int *left, int *right, Stack *dataStack)
{
	Number *numLeft;
	Number *numRight;
	
	numRight = (Number *)stackPop(dataStack);
	tokenDump((Token *)numRight);
	
	if((Token *)numRight == NULL)
		Throw(ERR_INCOMPLETE_NUMBER);
	
	if(numRight->type != NUMBER_TOKEN)
		Throw(ERR_NOT_NUMBER_TOKEN);
		
	numLeft = (Number *)stackPop(dataStack);
	tokenDump((Token *)numLeft);
	
	if((Token *)numLeft == NULL)
		Throw(ERR_INCOMPLETE_NUMBER);
		
	if(numLeft->type != NUMBER_TOKEN)
		Throw(ERR_NOT_NUMBER_TOKEN);
	
	*left = numLeft->value;
	*right = numRight->value;
	
	numberDel(numLeft);
	numberDel(numRight);
}

/*
	In this function basically is just create a new number token of he result that 
	had been obtained and push it back into the stack.
	
	Input:
	- result
*/
void pushNewNumber(int result, Stack *dataStack)
{
	Number *answer;
	answer = numberNew(result);
	stackPush(dataStack, answer);
}

/*
	This function will perform addition and it will function call the 
	getInfixValues and pushNewNumber function due to they work together.
*/	
void executeAdd(Stack *dataStack, Stack *operatorStack)
{
	int valueA, valueB;
	getInfixValues(&valueA, &valueB, dataStack);
	pushNewNumber(valueA + valueB, dataStack); 
}

/*
	This function will perform subtraction and it will function call the 
	getInfixValues and pushNewNumber function due to they work together.
*/
void executeSub(Stack *dataStack, Stack *operatorStack)
{
	int valueA, valueB;
	getInfixValues(&valueA, &valueB, dataStack);
	pushNewNumber(valueA - valueB, dataStack);
}

/*
	This function will perform multiplication and it will function call the 
	getInfixValues and pushNewNumber function due to they work together.
*/
void executeMul(Stack *dataStack, Stack *operatorStack)
{
	int valueA, valueB;
	getInfixValues(&valueA, &valueB, dataStack);
	pushNewNumber(valueA * valueB, dataStack);
}

/*
	This function will perform modulation and it will function call the 
	getInfixValues and pushNewNumber function due to they work together.
*/
void executeModulo(Stack *dataStack, Stack *operatorStack)
{
	int valueA, valueB;
	getInfixValues(&valueA, &valueB, dataStack);
	pushNewNumber(valueA % valueB, dataStack);
}

/*
	This function will perform division and it will function call the 
	getInfixValues and pushNewNumber function due to they work together.
*/
void executeDiv(Stack *dataStack, Stack *operatorStack)
{
	int valueA, valueB;
	getInfixValues(&valueA, &valueB, dataStack);
	pushNewNumber(valueA / valueB, dataStack);
}

/*
	This function will perform logical OR operation and it will function call the 
	getInfixValues and pushNewNumber function due to they work together.
*/
void executeOr(Stack *dataStack, Stack *operatorStack)
{
	int valueA, valueB;
	getInfixValues(&valueA, &valueB, dataStack);
	pushNewNumber(valueA || valueB, dataStack);
}

/*
	This function will perform XOR operation and it will function call the 
	getInfixValues and pushNewNumber function due to they work together.
*/
void executeXor(Stack *dataStack, Stack *operatorStack)
{
	int valueA, valueB;
	getInfixValues(&valueA, &valueB, dataStack);
	pushNewNumber(valueA ^ valueB, dataStack);
}

/*
	This function will perform logical AND operation and it will function call the 
	getInfixValues and pushNewNumber function due to they work together.
*/
void executeAnd(Stack *dataStack, Stack *operatorStack)
{
	int valueA, valueB;
	getInfixValues(&valueA, &valueB, dataStack);
	pushNewNumber(valueA && valueB, dataStack);
}

/*
	This function will perform bitwise AND operation and it will function call the 
	getInfixValues and pushNewNumber function due to they work together.
*/
void executeBitAnd(Stack *dataStack, Stack *operatorStack)
{
	int valueA, valueB;
	getInfixValues(&valueA, &valueB, dataStack);
	pushNewNumber(valueA & valueB, dataStack);
}

/*
	This function will perform bitwise OR operation and it will function call the 
	getInfixValues and pushNewNumber function due to they work together.
*/
void executeBitOr(Stack *dataStack, Stack *operatorStack)
{
	int valueA, valueB;
	getInfixValues(&valueA, &valueB, dataStack);
	pushNewNumber(valueA | valueB, dataStack);
}

/*
	This function will perform shift left operation and it will function call the 
	getInfixValues and pushNewNumber function due to they work together.
*/
void executeShiftLeft(Stack *dataStack, Stack *operatorStack)
{
	int valueA, valueB;
	getInfixValues(&valueA, &valueB, dataStack);
	pushNewNumber(valueA << valueB, dataStack);
}

/*
	This function will perform shift right operation and it will function call the 
	getInfixValues and pushNewNumber function due to they work together.
*/
void executeShiftRight(Stack *dataStack, Stack *operatorStack)
{
	int valueA, valueB;
	getInfixValues(&valueA, &valueB, dataStack);
	pushNewNumber(valueA >> valueB, dataStack);
}

/*
	This function will perform lesser operation and it will function call the 
	getInfixValues and pushNewNumber function due to they work together.
*/
void executeLesser(Stack *dataStack, Stack *operatorStack)
{
	int valueA, valueB;
	getInfixValues(&valueA, &valueB, dataStack);
	pushNewNumber(valueA < valueB, dataStack);
}

/*
	This function will perform greater operation and it will function call the 
	getInfixValues and pushNewNumber function due to they work together.
*/
void executeGreater(Stack *dataStack, Stack *operatorStack)
{
	int valueA, valueB;
	getInfixValues(&valueA, &valueB, dataStack);
	pushNewNumber(valueA > valueB, dataStack);
}

/*
	This function will perform equal operation and it will function call the 
	getInfixValues and pushNewNumber function due to they work together.
*/
void executeEqual(Stack *dataStack, Stack *operatorStack)
{
	int valueA, valueB;
	getInfixValues(&valueA, &valueB, dataStack);
	pushNewNumber(valueA == valueB, dataStack);
}

/* this function is used to execute closingBracket in multiple case
*/
void executeClosingBracket( Stack *dataStack, Stack *operatorStack)
{   
  Number *num ;
  Operator *Remove;
    
  Remove = stackPop(operatorStack);
  if( Remove ==  NULL || Remove->info->id !=OPEN_BRACKET) 
    Throw(ERR_NO_OPENING_BRACKET);
    
  if( stackisEmpty(dataStack) ) 
    Throw(  ERR_NO_NUMBER );
  
}

void executePrefixSub(Stack *dataStack, Stack *operatorStack)
{
	Number *num;
	
	num = (Number *)stackPeep(dataStack);
	tokenDump((Token *)num);
	
	if((Token *)num == NULL)
		Throw(ERR_INCOMPLETE_NUMBER);
	
	if(num->type != NUMBER_TOKEN)
		Throw(ERR_NOT_NUMBER_TOKEN);
	
	num->value = -num->value;
}

void executePrefixAdd(Stack *dataStack, Stack *operatorStack)
{
	Number *num;
	
	num = (Number *)stackPeep(dataStack);
	tokenDump((Token *)num);
	
	if((Token *)num == NULL)
		Throw(ERR_INCOMPLETE_NUMBER);
	
	if(num->type != NUMBER_TOKEN)
		Throw(ERR_NOT_NUMBER_TOKEN);
}

void executeNot(Stack *dataStack, Stack *operatorStack)
{
	Number *num;
	
	num = (Number *)stackPeep(dataStack);
	tokenDump((Token *)num);
	
	if((Token *)num == NULL)
		Throw(ERR_INCOMPLETE_NUMBER);
	
	if(num->type != NUMBER_TOKEN)
		Throw(ERR_NOT_NUMBER_TOKEN);
	
	num->value = ~num->value;
}

void executeBitNot(Stack *dataStack, Stack *operatorStack)
{
	Number *num;
	
	num = (Number *)stackPeep(dataStack);
	tokenDump((Token *)num);
	
	if((Token *)num == NULL)
		Throw(ERR_INCOMPLETE_NUMBER);
	
	if(num->type != NUMBER_TOKEN)
		Throw(ERR_NOT_NUMBER_TOKEN);
	
	num->value = !num->value;
}

void executeOpeningBracket(Stack *dataStack, Stack *operatorStack) {
  Throw(ERR_NO_CLOSING_BRACKET);
}