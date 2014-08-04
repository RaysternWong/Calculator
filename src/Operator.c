#include "Operator.h"
#include <stdio.h>
#include "Debug.h"
#include "Token.h"
#include "Stack.h"
#include "NumberToken.h"
#include "OperatorToken.h"
#include "TokenDebug.h"
#include "CException.h"
#include "ErrorCode.h"


void executeAdd(Stack *dataStack)
{
	Number *left;
	Number *right;
	Number *answer;
	int result = 0;
	
	right = (Number *)stackPop(dataStack);
//	//  //  tokenDump((Token *)right);
	
	if((Token *)right == NULL)
		Throw(ERR_INCOMPLETE_NUMBER);
	
	if(right->type != NUMBER_TOKEN)
		Throw(ERR_NOT_NUMBER_TOKEN);
		
	left = (Number *)stackPop(dataStack);
//	//  //  tokenDump((Token *)left);
	
	if((Token *)left == NULL)
		Throw(ERR_INCOMPLETE_NUMBER);
		
	if(left->type != NUMBER_TOKEN)
		Throw(ERR_NOT_NUMBER_TOKEN);
		
	result = left->value + right->value;
	
	numberDel(left);
	numberDel(right);
	
	answer = numberNew(result);
	stackPush(dataStack, answer);	
}

void executeSub(Stack *dataStack)
{
	Number *left;
	Number *right;
	Number *answer;
	int result = 0;
	
	right = (Number *)stackPop(dataStack);
	//  //  tokenDump((Token *)right);
	
	if((Token *)right == NULL)
		Throw(ERR_INCOMPLETE_NUMBER);
	
	if(right->type != NUMBER_TOKEN)
		Throw(ERR_NOT_NUMBER_TOKEN);
		
	left = (Number *)stackPop(dataStack);
	//  //  tokenDump((Token *)left);
	
	if((Token *)left == NULL)
		Throw(ERR_INCOMPLETE_NUMBER);
		
	if(left->type != NUMBER_TOKEN)
		Throw(ERR_NOT_NUMBER_TOKEN);
		
	result = left->value - right->value;
	
	numberDel(left);
	numberDel(right);
	
	answer = numberNew(result);
	stackPush(dataStack, answer);	
}

void executeMul(Stack *dataStack)
{
	Number *left;
	Number *right;
	Number *answer;
	int result = 0;
	
	right = (Number *)stackPop(dataStack);
	//  //  tokenDump((Token *)right);
	
	if((Token *)right == NULL)
		Throw(ERR_INCOMPLETE_NUMBER);
	
	if(right->type != NUMBER_TOKEN)
		Throw(ERR_NOT_NUMBER_TOKEN);
		
	left = (Number *)stackPop(dataStack);
	//  //  tokenDump((Token *)left);
	
	if((Token *)left == NULL)
		Throw(ERR_INCOMPLETE_NUMBER);
		
	if(left->type != NUMBER_TOKEN)
		Throw(ERR_NOT_NUMBER_TOKEN);
		
	result = left->value * right->value;
	
	numberDel(left);
	numberDel(right);
	
	answer = numberNew(result);
	stackPush(dataStack, answer);	
}

void executeModulo(Stack *dataStack)
{
	Number *left;
	Number *right;
	Number *answer;
	int result = 0;
	
	right = (Number *)stackPop(dataStack);
	//  //  tokenDump((Token *)right);
	
	if((Token *)right == NULL)
		Throw(ERR_INCOMPLETE_NUMBER);
	
	if(right->type != NUMBER_TOKEN)
		Throw(ERR_NOT_NUMBER_TOKEN);
		
	left = (Number *)stackPop(dataStack);
	//  //  tokenDump((Token *)left);
	
	if((Token *)left == NULL)
		Throw(ERR_INCOMPLETE_NUMBER);
		
	if(left->type != NUMBER_TOKEN)
		Throw(ERR_NOT_NUMBER_TOKEN);
		
	result = left->value % right->value;
	
	numberDel(left);
	numberDel(right);
	
	answer = numberNew(result);
	stackPush(dataStack, answer);	
}

void executeDiv(Stack *dataStack)
{
	Number *left;
	Number *right;
	Number *answer;
	int result = 0;
	
	right = (Number *)stackPop(dataStack);
	//  //  tokenDump((Token *)right);
	
	if((Token *)right == NULL)
		Throw(ERR_INCOMPLETE_NUMBER);
	
	if(right->type != NUMBER_TOKEN)
		Throw(ERR_NOT_NUMBER_TOKEN);
		
	left = (Number *)stackPop(dataStack);
	//  //  tokenDump((Token *)left);
	
	if((Token *)left == NULL)
		Throw(ERR_INCOMPLETE_NUMBER);
		
	if(left->type != NUMBER_TOKEN)
		Throw(ERR_NOT_NUMBER_TOKEN);
		
	result = left->value / right->value;
	
	numberDel(left);
	numberDel(right);
	
	answer = numberNew(result);
	stackPush(dataStack, answer);	
}

void executeOr(Stack *dataStack)
{
	Number *left;
	Number *right;
	Number *answer;
	int result = 0;
	
	right = (Number *)stackPop(dataStack);
	//  //  tokenDump((Token *)right);
	
	if((Token *)right == NULL)
		Throw(ERR_INCOMPLETE_NUMBER);
	
	if(right->type != NUMBER_TOKEN)
		Throw(ERR_NOT_NUMBER_TOKEN);
		
	left = (Number *)stackPop(dataStack);
	//  //  tokenDump((Token *)left);
	
	if((Token *)left == NULL)
		Throw(ERR_INCOMPLETE_NUMBER);
		
	if(left->type != NUMBER_TOKEN)
		Throw(ERR_NOT_NUMBER_TOKEN);
		
	result = (left->value) || (right->value);
	
	numberDel(left);
	numberDel(right);
	
	answer = numberNew(result);
	stackPush(dataStack, answer);	
}