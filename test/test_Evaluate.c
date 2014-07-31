#include "unity.h"
#include "Evaluate.h"
#include "mock_Token.h"
#include "mock_StringObject.h"
#include <string.h>
#include "Stack.h"
#include "OperatorToken.h"
#include "OperatorToken.h"
#include "NumberToken.h"
#include "Operator.h"
#include "TokenDebug.h"
#define STACK_LENGTH 100

#define STACK_LENGTH 100

void setUp(void){}

void tearDown(void){}




void test_tryToPushOperatorAndEvaluate_given_plus_should_push_to_stack(void){
   
	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack	 = stackNew(STACK_LENGTH) ;
	Operator plus	= {.type = OPERATOR_TOKEN, .info =getOperatorByID(ADD_OP) };
	Operator *ptrOpr;
	

	tryToPushOperatorAndEvaluate( operatorStack, &plus ,dataStack );
	ptrOpr = (Operator *)stackPop( operatorStack);
	
	TEST_ASSERT_EQUAL_PTR ( &plus, ptrOpr);

}

void test_tryToPushOperatorAndEvaluate_given_plus_multi_should_push_to_stack(void){

	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	 = stackNew(STACK_LENGTH) ;
	Operator Plus	= {.type = OPERATOR_TOKEN, .info =getOperatorByID(ADD_OP) };
	Operator Multi	= {.type = OPERATOR_TOKEN, .info =getOperatorByID(MUL_OP) };

	tryToPushOperatorAndEvaluate( operatorStack, &Plus  ,dataStack );
	tryToPushOperatorAndEvaluate( operatorStack, &Multi ,dataStack );
	
	TEST_ASSERT_EQUAL_PTR ( &Multi, (Operator *)stackPop( operatorStack));
	TEST_ASSERT_EQUAL_PTR ( &Plus , (Operator *)stackPop( operatorStack));

}


// void test_tryToPushOperatorAndEvaluate_given_2plus2_should_answer_the_token_four(void){


	// Stack *operatorStack = stackNew(STACK_LENGTH);
	// Stack *dataStack 	 = stackNew(STACK_LENGTH);
	// Operator Plus		 = {.type = OPERATOR_TOKEN, .info =getOperatorByID(ADD_OP) };
	// Number two  		 = {.type = NUMBER_TOKEN, .value = 2};

	// stackPush( dataStack , &two );
	// stackPush( dataStack , &two );
	// tryToPushOperatorAndEvaluate( operatorStack, &Plus  ,dataStack );
	
// }

void xtest_evaluate_given_token_2plus3_should_get_5(void){

	int result;
	
	Number two  		={.type = NUMBER_TOKEN, .value = 2};
	Number three		={.type = NUMBER_TOKEN, .value = 3};
	Operator Plus	= {.type = OPERATOR_TOKEN, .info =getOperatorByID(ADD_OP) };	 
	String expression 	={.string="2+3"};

	getToken_ExpectAndReturn(&expression, (Token*)&two	);  	//2
	getToken_ExpectAndReturn(&expression, (Token*)&Plus  );		//+
    getToken_ExpectAndReturn(&expression, (Token*)&three );		//3


	result = evaluate(&expression);
	// TEST_ASSERT_EQUAL( 5, result);

}

void xtest_evaluate_given_token_2_plus_3_Mutiple_5_plus_6_should_get_23(void){

	int result;
    Number two  	={.type = NUMBER_TOKEN, .value = 2};
	Number three	={.type = NUMBER_TOKEN, .value = 3};
	Number five  	={.type = NUMBER_TOKEN, .value = 5};
	Number six		={.type = NUMBER_TOKEN, .value = 6};	
	Operator Plus	= {.type = OPERATOR_TOKEN, .info =getOperatorByID(ADD_OP) };
	Operator Multi	= {.type = OPERATOR_TOKEN, .info =getOperatorByID(MUL_OP) };
	String expression = {.string="2+3*5+6"};
   
    getToken_ExpectAndReturn(&expression, (Token*)&two	);	//2
	getToken_ExpectAndReturn(&expression, (Token*)&Plus );	//+
    getToken_ExpectAndReturn(&expression, (Token*)&three);	//3
	getToken_ExpectAndReturn(&expression, (Token*)&Multi);	//*	
	getToken_ExpectAndReturn(&expression, (Token*)&five );	//5
    getToken_ExpectAndReturn(&expression, (Token*)&Plus );	//+
	getToken_ExpectAndReturn(&expression, (Token*)&six);	//6

	result = evaluate(&expression);

}

