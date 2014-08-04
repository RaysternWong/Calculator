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
						oprNew->info->execute( dataStack );    
					}
					
				ptrOpr = (Operator *)stackPeep(operatorStack);
			}		
      stackPush( operatorStack , opr ); //while the operator stack is empty then push into the last operator

	}
 
}

void doOperatorStackRewinding ( Stack *dataStack , Stack *operatorStack ){

  Operator *ptrOpr;   // pointer to operator	
	ptrOpr = (Operator *)stackPeep(operatorStack);

  while( ptrOpr != NULL)
			{     
						Operator *oprNew = stackPop( operatorStack);        
						oprNew->info->execute( dataStack );    
				  	ptrOpr = (Operator *)stackPeep(operatorStack);
			}		
     
}

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


