#include <stdio.h>
#include "Evaluate.h"
#include "Token.h"
#include "TokenDebug.h"
#include <malloc.h>
#include "Stack.h"
#include "OperatorToken.h"
#include "NumberToken.h"
#include "Operator.h"


#define STACK_LENGTH 100
	

void ChooseTheOperation(  Operator *opr, Stack *dataStack ){

 

	switch(opr->info->id)
	{	
		case  ADD_OP:
		executeAdd(dataStack);
		break;
	
		

	

		
	}
}

void tryToPushOperatorAndEvaluate( Stack *operatorStack, Operator *opr, Stack *dataStack ){
		
	Operator *ptrOpr;   // pointer to operator	
	
	ptrOpr = (Operator *)stackPeep(operatorStack);
	if(  (ptrOpr == NULL)  || (opr->info->precedence > ptrOpr->info->precedence)  ) {	
		
		
		stackPush( operatorStack , opr );

		
	} else if  (opr->info->precedence <= ptrOpr->info->precedence) { 
		
		Operator *oprNew = stackPop( operatorStack);
		ChooseTheOperation(  oprNew , dataStack );
				//stackPush( operatorStack , opr );
		
	}

}

int evaluate(String *expression){

	Token *token;
	Stack *dataStack     = stackNew(STACK_LENGTH);
	Stack *operatorStack = stackNew(STACK_LENGTH);
	// stack = stackNew(STACK_LENGTH);
	// stackOperator = stackNew(STACK_LENGTH);
	
	do {
	token =getToken(expression);
	
	if ( token!=NULL)    
	{
	
	//token dump function
	if ( token->type == NUMBER_TOKEN)
	{
	 
	     Number *num = (Number*)token;	
		 stackPush( dataStack   , &num );
			
	}
	
	else if ( token->type == OPERATOR_TOKEN)
	{
		
		Operator *opr = (Operator*)token;
		//tryToPushOperator( operatorStack , opr  );
		
	}
	//token dump function
			
	}
	} while (token !=NULL);


}





