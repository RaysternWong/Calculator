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
	


void ChooseTheOperation(  Operator *opr, Stack *dataStack ){

	switch(opr->info->id)
	{	
		case  ADD_OP:
		executeAdd(dataStack);
		break;
		
		case  SUB_OP:
		executeSub(dataStack);
		break;
		
		case  MUL_OP:
		executeMul(dataStack);
		break;
		
		case  DIV_OP:
		executeDiv(dataStack);
		break;
		
		case  NPERCENT_OP:
		executeModulo(dataStack);
		break;
		
		case  OR_OP:
    printf("or\n");
		executeOr(dataStack);
		break;
		
		default:
		{
			Throw(ERR_UNKNOWN_OPERATOR);
		}
		
	}
}

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
						ChooseTheOperation(  oprNew , dataStack );    
					}
					
				ptrOpr = (Operator *)stackPeep(operatorStack);
			}		
      stackPush( operatorStack , opr ); //while the operator stack is empty then push into the last operator

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

  Operator *oprNew = stackPop( operatorStack);        
  ChooseTheOperation(  oprNew , dataStack );
  
	Number *ans = (Number *)stackPop( dataStack );
	Result = ans->value;

  verifyAllStacksAreEmpty(dataStack, operatorStack);
  
	return Result;

}



	// else if  (opr->info->precedence <= ptrOpr->info->precedence || opr == NULL )
	// { 
		// Operator *oprNew = stackPop( operatorStack);
		// ChooseTheOperation(  oprNew , dataStack );    
	// }

