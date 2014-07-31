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
#include "ErrorCode.h"


#define STACK_LENGTH 100

void setUp(void){}

void tearDown(void){}


void test_tryToPushOperatorAndEvaluate_given_plus_should_push_to_stack(void){
   
	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack	 = stackNew(STACK_LENGTH) ;
	Operator *Plus		 = operatorNewByName("+");
	Operator *ptrOpr;
	
	tryToPushOperatorAndEvaluate( Plus , operatorStack, dataStack );
	TEST_ASSERT_EQUAL_PTR ( Plus, (Operator *)stackPop( operatorStack));

}

void test_tryToPushOperatorAndEvaluate_given_plus_multi_should_push_to_stack(void){

	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	 = stackNew(STACK_LENGTH) ;
	Operator *Plus		 = operatorNewByName("+");
	Operator *Multi		 = operatorNewByName("*");

	tryToPushOperatorAndEvaluate( Plus  , operatorStack, dataStack );
	tryToPushOperatorAndEvaluate( Multi , operatorStack, dataStack );
	
	TEST_ASSERT_EQUAL_PTR ( Multi, (Operator *)stackPop( operatorStack));
	TEST_ASSERT_EQUAL_PTR ( Plus , (Operator *)stackPop( operatorStack));

}

void test_tryToPushOperatorAndEvaluate_given_2_Plus_4_Plus_should_answer_the_token_six(void){


	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	 = stackNew(STACK_LENGTH);
	Operator *Plus1		 = operatorNewByName("+");
	Operator *Plus2		 = operatorNewByName("+");
	Operator *op;
	Number *two = numberNew(2);
	Number *four = numberNew(4);
	Number *num;
	
	//2+4+ same predecedence 
	stackPush( dataStack , two );
	stackPush( dataStack , four );
	stackPush( operatorStack , Plus1 );
	tryToPushOperatorAndEvaluate( Plus2 , operatorStack, dataStack ); 
		
	num = (Number *)stackPop( dataStack );
	TEST_ASSERT_NOT_NULL ( num );
	TEST_ASSERT_EQUAL (	NUMBER_TOKEN, num->type);
	TEST_ASSERT_EQUAL ( 6 , num->value );
	
	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NULL ( op );
	
	
		
}

void test_tryToPushOperatorAndEvaluate_given_2_Plus_4_Multi_should_answer_the_token_four(void){


	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	 = stackNew(STACK_LENGTH);
	Operator *Plus		 = operatorNewByName("+");
	Operator *Multi		 = operatorNewByName("*");
	Operator *op;
	Number *two = numberNew(2);
	Number *four = numberNew(4);
	Number *num;

	//2+4* higher precedence
	stackPush( dataStack , two );
	stackPush( dataStack , four );
	stackPush( operatorStack , Plus );
	tryToPushOperatorAndEvaluate(Multi , operatorStack, dataStack ); 
	
	
	num = (Number *)stackPop( dataStack );
	TEST_ASSERT_NOT_NULL ( num );
	TEST_ASSERT_EQUAL (	NUMBER_TOKEN, num->type);
	TEST_ASSERT_EQUAL ( 4 , num->value );
		
	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
	TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( MUL_OP , op->info->id );
}


void test_tryToPushOperatorAndEvaluate_given_2_Plus_4_BITWISE_AND_should_answer_the_token_four(void){


	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	 = stackNew(STACK_LENGTH);
	Operator *Plus		 = operatorNewByName("+");
	Operator *BIT_AND	 = operatorNewByName("&");
	Operator *op;
	Number *two = numberNew(2);
	Number *four = numberNew(4);
	Number *num;

	//2+6& lower precedence
	stackPush( dataStack , two );
	stackPush( dataStack , four );
	stackPush( operatorStack , Plus );
	tryToPushOperatorAndEvaluate( BIT_AND , operatorStack, dataStack ); 
	
	
	num = (Number *)stackPop( dataStack );
	TEST_ASSERT_NOT_NULL ( num );
	TEST_ASSERT_EQUAL (	NUMBER_TOKEN, num->type);
	TEST_ASSERT_EQUAL ( 6 , num->value );
	
	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NULL ( op );
		
}

void xtest_tryToPushOperatorAndEvaluate_given_2_Plus_4_Multi_3_should_answer_the_token_fourteen(void){


	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	 = stackNew(STACK_LENGTH);
	Operator *Plus		 = operatorNewByName("+");
	Operator *Multi		 = operatorNewByName("*");
	Number *two = numberNew(2);
	Number *four = numberNew(4);
	Number *three = numberNew(3);

	//2+4*3
	stackPush( dataStack , two );
	stackPush( dataStack , four );
	stackPush( operatorStack , Plus );
	tryToPushOperatorAndEvaluate(  Multi , operatorStack, dataStack ); 

	Number *ans = (Number *)stackPop( dataStack );
	TEST_ASSERT_EQUAL ( 14, ans->value );
		
}


void xtest_tryToPushOperatorAndEvaluate_given_2_multi_2_plus_2_should_answer_the_token_six(void){


	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	 = stackNew(STACK_LENGTH);
	Operator *Plus		 = operatorNewByName("+");
	Operator *Multi		 = operatorNewByName("*");
	Number *two = numberNew(2);

	stackPush( dataStack , two );
	stackPush( dataStack , two );
	tryToPushOperatorAndEvaluate(  Multi , operatorStack , dataStack );
	tryToPushOperatorAndEvaluate(  Plus  , operatorStack , dataStack );
	stackPush( dataStack , two );
	//2*2+2 should ans 6
	
	Number *ans = (Number *)stackPop( dataStack );
	TEST_ASSERT_EQUAL ( 6 , ans->value );
		
}

void test_evaluate_given_token_2_plus_3_should_get_5(void){

	int Result;
	
	Number *two = numberNew(2);
	Number *three = numberNew(3);
	Operator *Plus = operatorNewByName("+"); 
	String expression = {.string="2+3"};

	getToken_ExpectAndReturn(&expression, (Token*)two	);  	//2
	getToken_ExpectAndReturn(&expression, (Token*)Plus  );		//+
    getToken_ExpectAndReturn(&expression, (Token*)three );		//3
    getToken_ExpectAndReturn(&expression, NULL );	

	Result = evaluate(&expression);
	TEST_ASSERT_EQUAL( 5 , Result);

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

