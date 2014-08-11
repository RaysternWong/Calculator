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

void tryToPushOperatorAndEvaluate(Operator *opr, Stack *operatorStack,  Stack *dataStack )
{
	Operator *ptrOpr;   // pointer to operator	
	ptrOpr = (Operator *)stackPeep(operatorStack);

	if((ptrOpr == NULL) || (opr->info->precedence > ptrOpr->info->precedence)) 
	{	
		printf("stack is empty, push operator directly\n");
		stackPush( operatorStack , opr );
	}	
	else 
	{ 
		while( ptrOpr != NULL)
		{     
			if (opr->info->precedence <= ptrOpr->info->precedence || opr == NULL )
			{ 
				printf("there is operator in the stack\n");
				Operator *oprNew = stackPop(operatorStack); 
        printf("successfully pop operator out\n");
				oprNew->info->execute( dataStack );    
				printf("done executing\n");
			}
					
			ptrOpr = (Operator *)stackPeep(operatorStack);
		}		
		stackPush( operatorStack , opr ); //while the operator stack is empty then push into the last operator
	}
}

// void doOperatorStackRewinding(Stack *dataStack , Stack *operatorStack) {
  // Operator *ptrOpr;   // pointer to operator	
	// ptrOpr = (Operator *)stackPeep(operatorStack);

  // while( ptrOpr != NULL) {     
		// Operator *oprNew = stackPop( operatorStack);        
		// oprNew->info->execute(dataStack , operatorStack);    
		// ptrOpr = (Operator *)stackPeep(operatorStack);
	// }		
// }

void verifyAllStacksAreEmpty(Stack *dataStack, Stack *operatorStack) 
{
  if(stackPop( operatorStack) != NULL) 
  {
    printf("Error: operatorStack is not empty\n");
    exit(EXIT_FAILURE);
  }
  
  if(stackPop( dataStack) != NULL)
  {
    printf("Error: dataStack is not empty\n");
    exit(EXIT_FAILURE);
  }
}

Token *convertToPrefixIfNotAlready(Operator *op) {
  if(op->info->affix == INFIX) {
    operatorTryConvertToPrefix(op);
    tokenDump((Token *)op);
  } 
  return (Token *)op;
}

void evaluatePrefixesAndNumber(Token *token, String *expression, Stack *dataStack, Stack *operatorStack) {
  while(token != NULL) {
    if(token->type == OPERATOR_TOKEN) {
      tokenDump(token);
      Operator *operator = (Operator *)token;
      token = convertToPrefixIfNotAlready(operator);
      stackPush(operatorStack, (Operator *)token);
    } else if(token->type == NUMBER_TOKEN) {
        tokenDump(token);
        Number *num = (Number *)token;
        stackPush(dataStack, num);
      } else 
          Throw(ERR_IDENTIFIER_NOT_SUPPORT);
          
    token = getToken(expression);
  }
  
  if(dataStack->size == 0)
    Throw(ERR_EXPECTING_NUMBER);
}

int evaluate(String *expression) {
  Stack *dataStack     = stackNew(STACK_LENGTH);
	Stack *operatorStack = stackNew(STACK_LENGTH);
  Token *token;
  while(token != NULL) {
    token = getToken(expression);
    if(token == NULL) 
      break;
      
    evaluatePrefixesAndNumber(token, expression, dataStack, operatorStack);
  }
  // doOperatorStackRewinding(dataStack, operatorStack);
}
