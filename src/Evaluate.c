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
				oprNew->info->execute( dataStack );    
				printf("done executing\n");
			}
					
			ptrOpr = (Operator *)stackPeep(operatorStack);
		}		
		stackPush( operatorStack , opr ); //while the operator stack is empty then push into the last operator
	}
}

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

// int evaluate(String *expression)
// {
	// int Result;
	// int firstOp = 1;
	// Token *token;
	// Operator *operator;
	// Stack *dataStack     = stackNew(STACK_LENGTH);
	// Stack *operatorStack = stackNew(STACK_LENGTH);

	// do {
		// token = getToken(expression); 
		// printf("start cycle\n");
		
		// if(token!=NULL) {
			// tokenDump(token);
			// if(token->type == NUMBER_TOKEN) {
				// Number *num = (Number*)token;
				// printf("Number token\n");
				// tokenDump(token);
				// stackPush(dataStack, num);
				// firstOp = 0; //clear firstOp if first token is NUMBER_TOKEN
			// }  
			
			// do{
        // if(token->type == OPERATOR_TOKEN) {
            // Operator *opr = (Operator*)token;
            // printf("operator\n");
            // tokenDump(token);
				
          // if(firstOp) { //if first token is OPERATOR
            // if(opr->info->affix == INFIX) {
              // printf("infix\n");
              // operatorTryConvertToPrefix(opr);
              // tokenDump(token);
              // tryToPushOperatorAndEvaluate(opr, operatorStack, dataStack);
              // firstOp = 0;
              // printf("done conversion\n");	
            // } else if(opr->info->affix == PREFIX) {
              // printf("prefix\n");
              // tryToPushOperatorAndEvaluate(opr, operatorStack, dataStack);
            // } else if(!firstOp) { //if OPERATOR is not first token
              // printf("not first operator\n");
              // tryToPushOperatorAndEvaluate(opr, operatorStack, dataStack);
            // }	
              // printf("done checking operator token\n");
           // token = getToken(expression);
        // }	
      // }while(token->type == OPERATOR_TOKEN);
		// }
	// }while(token != NULL);
	
	// printf("no more token\n");
	// Operator *oprNew = stackPop(operatorStack);        
	// oprNew->info->execute(dataStack); 
	
	// Number *ans = (Number *)stackPop(dataStack);
	// Result = ans->value;

	// verifyAllStacksAreEmpty(dataStack, operatorStack);
  
	// return Result;
// }

int evaluate(String *expression)
{
  int Result;
  Token *token;
  Stack *dataStack     = stackNew(STACK_LENGTH);
	Stack *operatorStack = stackNew(STACK_LENGTH);
  
  do{
    token = getToken(expression);
    printf("start cycle\n");
		
		if(token!=NULL) {
    //prefix convert operator token
      if(token->type == OPERATOR_TOKEN) {
        while(token->type == OPERATOR_TOKEN) {
          Operator *opr = (Operator*)token;
          printf("operator\n");
          tokenDump(token);
        
          if(opr->info->affix == INFIX) {
            printf("infix\n");
            operatorTryConvertToPrefix(opr);
            tokenDump(token);
            tryToPushOperatorAndEvaluate(opr, operatorStack, dataStack);
            printf("done conversion\n");
          } else if(opr->info->affix == PREFIX) {
              printf("prefix\n");
              tryToPushOperatorAndEvaluate(opr, operatorStack, dataStack);
            }
          printf("done checking operator token\n");
          token = getToken(expression);
        }
      }
    // check whether it is number token
      if(token->type != NUMBER_TOKEN)
        Throw(ERR_NOT_NUMBER_TOKEN);
      
      if(token->type == NUMBER_TOKEN) {
        Number *num = (Number*)token;
				printf("Number token\n");
				tokenDump(token);
				stackPush(dataStack, num);
      }
    } 
      
  }while(token != NULL);
  
  // infix process
  printf("no more token\n");
	Operator *oprNew = stackPop(operatorStack);        
	oprNew->info->execute(dataStack); 
	
	Number *ans = (Number *)stackPop(dataStack);
	Result = ans->value;

	verifyAllStacksAreEmpty(dataStack, operatorStack);
  
	return Result;
}
