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
  Operator *IsItClosingBracket ;
  Operator *IsItOpenBracket;
  Operator *Remove;
  int counter1=0, counter2=0 ;
  
  if( stackisEmpty(dataStack) ) 
    { Throw (ERR_STACK_EMPTY); }

  IsItClosingBracket  = stackPeep(operatorStack);
   if ( IsItClosingBracket == NULL || IsItClosingBracket->info->id != CLOSE_BRACKET )
     {   Throw ( ERR_NO_CLOSING_BRACKET);  }
   else {  
           
           while (  IsItClosingBracket->info->id == CLOSE_BRACKET  ){  //to remove the closing bracket and ounting it      
             Remove  = stackPop(operatorStack);
             counter1 = counter1+1 ;
             IsItClosingBracket  = stackPeep(operatorStack); 
             
             if( IsItClosingBracket  == NULL)     //if stackPeep is NULL, then means that is no open bracket
               {   Throw( ERR_NO_OPEN_BRACKET); }
           } 
           
          
         IsItOpenBracket  = stackPeep(operatorStack);
           if ( IsItOpenBracket == NULL  )
             {      Throw( ERR_NO_OPEN_BRACKET); }
            else {
               while (  (IsItOpenBracket != NULL)){
                Remove  = stackPop(operatorStack);
                counter2 = counter2+1 ;
                IsItOpenBracket  = stackPeep(operatorStack);
              }  
             } 
            if(counter1 != counter2 || counter2!=counter1)
            Throw ( ERR_UNBALANCE_BRACKET);
       }   
   
}
