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
		
	Operator *ptrOpr;   // pointer to operator	
	ptrOpr = (Operator *)stackPeep(operatorStack);

	if( (ptrOpr == NULL)  || (opr->info->precedence > ptrOpr->info->precedence)  ) 
	{	
		stackPush( operatorStack , opr );
  
	}	else { 

			while( ptrOpr != NULL)
			{     
				if  (opr->info->precedence <= ptrOpr->info->precedence || opr == NULL )
					{ 
						Operator *oprNew = stackPop( operatorStack);        
						oprNew->info->execute( dataStack , operatorStack );    
					}
					
				ptrOpr = (Operator *)stackPeep(operatorStack);
			}		
      stackPush( operatorStack , opr ); //while the operator stack is empty then push into the last operator

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

  while( ptrOpr != NULL)
			{     
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

/* This function is the main module to do mathematics calculation 
   Fist, it is taking the coming token from the string expression
   if the token is number type then push into dataStack
   else if the token is operator type then push into operatorStack, and the operator will be arranged and execute by
   shunting algorithm
   After the coming token is been taken until NULL
   there is a function call doOperatorStackRewinding to double check the operation and all the elements was been perform*/
int evaluate(String *expression){

	int Result;
	Token *token;
	Stack *dataStack     = stackNew(STACK_LENGTH);
	Stack *operatorStack = stackNew(STACK_LENGTH);

  do {
    token =getToken(expression);

    if ( token!=NULL)    
    {
        if ( token->type == NUMBER_TOKEN)
        {
          Number *num = (Number*)token;	
          stackPush( dataStack   , num );
        }  
        else if ( token->type == OPERATOR_TOKEN)
        {
          Operator *opr = (Operator*)token; 
          tryToPushOperatorAndEvaluate ( opr, operatorStack , dataStack  );
        }		
    }
  } while (token != NULL);

  doOperatorStackRewinding ( dataStack , operatorStack );
  
	Number *ans = (Number *)stackPop( dataStack );
	Result = ans->value;
  verifyAllStacksAreEmpty(dataStack, operatorStack);
  
	return Result;

}


void evalauatePostfixesAndInfix(Token *token){

        if ( token->type == NUMBER_TOKEN)
        {
            Throw (ERR_DONT_EXPECT_NUMBER);
        }  
         else if ( token->type == OPERATOR_TOKEN)
         {
          // Operator *opr = (Operator*)token; 
          // tryToPushOperatorAndEvaluate ( opr, operatorStack , dataStack  );
         }	
}

