#include <stdio.h>
#include "Evaluate.h"
#include "Token.h"
#include "TokenDebug.h"
#include <malloc.h>
#include "Stack.h"
#include "OperatorToken.h"
#include "NumberToken.h"
#include "Operator.h"
#include "ErrorCode.h"
#include "CException.h"


#define STACK_LENGTH 100

/*This function is perform try to push the operator into the operator stack
   while the operator stack is empty
   precedence of coming operator is higher then the precedence inside the operator stack,
   then will push in and do for the next operator too
   else will start to perform operation

    input:
    ~operator , ~operatorStack , ~dataStack

    output:
    ~the returned number token and it is pushed into data stack, final return the data stack to the main function  */
void tryToPushOperatorAndEvaluate( Operator *opr, Stack *operatorStack,  Stack *dataStack ){

	Operator *ptrOpr;
	ptrOpr = (Operator *)stackPeep(operatorStack);

  //Opr is the operator coming from the string expressoin
  //ptrOpr is the operator that coming from the operator stack

	if( (   ptrOpr == NULL)  || (opr->info->precedence > ptrOpr->info->precedence) ||
      (  (opr->info->precedence == ptrOpr->info->precedence) && ( opr->info->associativity == RIGHT_TO_LEFT ) )   
    ) 
    stackPush( operatorStack , opr ); 
	else {
			while( ptrOpr != NULL){
				if  (opr->info->precedence <= ptrOpr->info->precedence || opr == NULL ){
						Operator *oprNew = stackPop( operatorStack);
						oprNew->info->execute( dataStack , operatorStack );
				}
				ptrOpr = (Operator *)stackPeep(operatorStack);
			}
      stackPush( operatorStack , opr ); //while the operator stack is empty then push the opr into the last operator stack
	}
}

/*
This function is used to perform operation with the two stacks that already contain element
then start operation based on the elements of the stacks

input:
~ dataStack, ~operatorStack  */
void doOperatorStackRewinding ( Stack *dataStack , Stack *operatorStack ){

  Operator *ptrOpr;   // pointer to operator
	ptrOpr = (Operator *)stackPeep(operatorStack);

  while( ptrOpr != NULL )	{
		Operator *oprNew = stackPop( operatorStack);
		oprNew->info->execute( dataStack , operatorStack );
		ptrOpr = (Operator *)stackPeep(operatorStack);

	}

}


/* This function is used to verify the two stacks isn"t empty after the evaluation
  input:
  ~dataStack, ~operatorStack*/
void verifyAllStacksAreEmpty(Stack *dataStack, Stack *operatorStack) {

  if(stackPop( operatorStack) != NULL) {
    printf("Error: operatorStack is not empty\n");
    exit(EXIT_FAILURE);
  }
  if(stackPop( dataStack) != NULL) {
    printf("Error: dataStack is not empty\n");
    exit(EXIT_FAILURE);
  }
}

/*
  This function will convert those INFIX operators to PREFIX
  Input:
    The operator and the info that is passed into this function
  Output:
    The returned token with new PREFIX OperatorInfo
*/
Token *convertToPrefixIfNotAlready(Operator *op) {
  if(op->info->affix == INFIX) {
    operatorTryConvertToPrefix(op);
  }
  return (Token *)op;
}

/*
  This function will get the Token if it is Operator Token it will keep
  get the token until it get a number token then it will stop
  Input:
    Token that is being passed in, expression of the string, dataStack and operatorStack
*/
void evaluatePrefixesAndNumber(Token *token, String *expression, Stack *dataStack, Stack *operatorStack) {
  if(token != NULL) {
    while(1) {
      if(token->type == NUMBER_TOKEN) {
      Number *num = (Number *)token;
      stackPush(dataStack, num);
      break;
      } else if(token->type == OPERATOR_TOKEN) {
        Operator *operator = (Operator *)token;
        token = convertToPrefixIfNotAlready(operator);
        stackPush(operatorStack, (Operator *)token);
      } else {
        // tokenDisplay(token);
        Throw(ERR_IDENTIFIER_NOT_SUPPORT);
      }
      token = getToken(expression);
      if(token == NULL)
        break;
    }
  }
  if(dataStack->size == 0) {
    // tokenDisplay(token);
    Throw(ERR_EXPECTING_NUMBER);
  }
}

/* This function is evaluate evaluatePostfixesAndInfix for bracket execution
	 if the first passing token is number or  prefix operator then will throw exception
	 else if the first passing token is infix operator then will pushed into stack
	 else if the first passing token is postfix operator, which means closingBracket
	   Fist, it will check is there any execution before the closingBracket,
		 Second, remove the bracket
		 third, check the coming string expression, if is postfix then remove the bracket, if is infix then pushed into stack and break.

	 For the case ( 2 ), the operation run as below shown
	 current			coming operator
	 ------				---------------
	 (2   				)
	 (2)
	  2

	 For the case ( 2 )+, the operation run as below shown
	 current			coming operator
	 ------				---------------
	 (2   				)+
	 (2)     			 +
	  2     	  	 +
	  2+

	 For the case like (2+5)+, because there is a execution inside the bracket, so before I fed in the closingBracket,
	 the 2+5 should execute first,then the operation will run as below shown
	 current			coming operator
	 ------				---------------
	 (2+5    			 )+
	 (7       		 )+
	 (7)      		 +
	  7						 +
	 7+
*/
void evaluatePostfixesAndInfix(Token *token, String *expression, Stack *dataStack ,Stack *operatorStack ){

  Operator *opr;  // closingBracket
	Operator *executionInBracket;

  if( token == NULL)
    return;
  if ( token->type == NUMBER_TOKEN)
    Throw (ERR_NOT_EXPECTING_NUMBER);
		
	while (token != NULL){	
   opr = (Operator *)token;
   if( opr->info->affix == PREFIX )
    Throw( ERR_NOT_EXPECTING_PREFIX_OPERATOR);      
   else if( opr->info->affix == POSTFIX ){
		 executionInBracket = stackPeep(operatorStack);
      while ( executionInBracket != NULL &&  executionInBracket->info->precedence > opr->info->precedence ){  //if the operator's precedence is higher then closingBracket then do execution
       executionInBracket = stackPop( operatorStack);
       executionInBracket->info->execute( dataStack , operatorStack );
       executionInBracket = (Operator *)stackPeep(operatorStack);
      }
    opr->info->execute( dataStack , operatorStack );
   }
	 else if( opr->info->affix == INFIX ){
    tryToPushOperatorAndEvaluate ( opr, operatorStack , dataStack );   
    break;
   }
    token = getToken(expression);
  }
}

/*
  This function is the main evaluate function of the ShuntingYard algorithm
  Input:
    The string expression that is passed in by the user
  Output:
    The return of the final result after the arithmetic and logic process
*/
int evaluate(String *expression) {
  int Result;
  Token *token;
  Stack *dataStack     = stackNew(STACK_LENGTH);
	Stack *operatorStack = stackNew(STACK_LENGTH);


  token = getToken(expression);

  while(token != NULL) {
    evaluatePrefixesAndNumber(token, expression, dataStack, operatorStack);
    token = getToken(expression);

    if(token == NULL)
      break;

    evaluatePostfixesAndInfix(token, expression, dataStack, operatorStack);
    token = getToken(expression);
  }

  doOperatorStackRewinding ( dataStack , operatorStack );
  Number *ans = (Number *)stackPop(dataStack);
	Result = ans->value;
  verifyAllStacksAreEmpty(dataStack, operatorStack);

	return Result;
}
