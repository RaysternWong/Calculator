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
	TEST_ASSERT_NOT_NULL ( op );
	TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( ADD_OP , op->info->id );
			
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
	tryToPushOperatorAndEvaluate( Multi , operatorStack, dataStack ); 
	
	
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
  TEST_ASSERT_NOT_NULL ( op );
	TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( BITWISE_AND_OP , op->info->id );
		
}

void test_tryToPushOperatorAndEvaluate_given_2_Plus_4_Multi_5_Plus_should_answer_the_token_twenty_two(void){


	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	 = stackNew(STACK_LENGTH);
	Operator *Plus1		 = operatorNewByName("+");
	Operator *Plus2		 = operatorNewByName("+");
	Operator *Multi		 = operatorNewByName("*");
	Operator *op;
	Number *two  = numberNew(2);
	Number *four = numberNew(4);
	Number *five = numberNew(5);
	Number *num;

	//2+4*5+ same precedence
	stackPush( dataStack , two );
	stackPush( dataStack , four );
	stackPush( dataStack , five );
	stackPush( operatorStack , Plus1 );
	stackPush( operatorStack , Multi );
  
	tryToPushOperatorAndEvaluate(Plus2 , operatorStack, dataStack ); 
	
	num = (Number *)stackPop( dataStack );
	TEST_ASSERT_NOT_NULL ( num );
	TEST_ASSERT_EQUAL (	NUMBER_TOKEN, num->type);
	TEST_ASSERT_EQUAL ( 22 , num->value );
		
	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( ADD_OP , op->info->id );
  
}

void test_tryToPushOperatorAndEvaluate_given_2_Multi_13_Plus_7_AND_should_answer_the_token_ninety_three(void){


	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	 = stackNew(STACK_LENGTH);
	Operator *Plus		 = operatorNewByName("+");
	Operator *BIT_AND   	 = operatorNewByName("&");
	Operator *Multi		 = operatorNewByName("*");
	Operator *op;
	Number *two       = numberNew(2);
	Number *thirteen  = numberNew(13);
	Number *seven     = numberNew(7);
	Number *num;

	//2+13*7& same precedence
	stackPush( dataStack , two );
	stackPush( dataStack , thirteen );
	stackPush( dataStack , seven );
  stackPush( operatorStack , Plus );
	stackPush( operatorStack , Multi );
	
	tryToPushOperatorAndEvaluate( BIT_AND , operatorStack, dataStack ); 
	
	num = (Number *)stackPop( dataStack );
	TEST_ASSERT_NOT_NULL ( num );
	TEST_ASSERT_EQUAL (	NUMBER_TOKEN, num->type);
	TEST_ASSERT_EQUAL ( 93 , num->value );
		
	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( BITWISE_AND_OP , op->info->id );
 
}

void test_tryToPushOperatorAndEvaluate_given_2_plus_4_plus_5__Multi_should_answer_the_token_five(void){


	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	 = stackNew(STACK_LENGTH);
	Operator *Plus1		 = operatorNewByName("+");
	Operator *Plus2		 = operatorNewByName("+");
	Operator *Multi		 = operatorNewByName("*");
	Operator *op;
	Number *two  = numberNew(2);
	Number *four = numberNew(4);
	Number *five = numberNew(5);
	Number *num;

  //2+4+5*
	stackPush( dataStack , two  );
	stackPush( dataStack , four );
  stackPush( dataStack , five );
  stackPush( operatorStack , Plus1 );
	stackPush( operatorStack , Plus2 );
	tryToPushOperatorAndEvaluate(  Multi , operatorStack , dataStack );

  num = (Number *)stackPop( dataStack );
	TEST_ASSERT_NOT_NULL ( num );
	TEST_ASSERT_EQUAL (	NUMBER_TOKEN, num->type);
	TEST_ASSERT_EQUAL ( 5 , num->value );
		
	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( MUL_OP , op->info->id );
		
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

void test_evaluate_given_token_2_plus_3_Mutiple_5_plus_6_should_get_23(void){

	int Result;
  Number *two   = numberNew(2);
	Number *three = numberNew(3);
  Number *five  = numberNew(5);
  Number *six   = numberNew(6);
	Operator *Plus1		 = operatorNewByName("+");
  Operator *Plus2		 = operatorNewByName("+");
	Operator *Multi		 = operatorNewByName("*");
	String expression = {.string="2+3*5+6"};
   
  getToken_ExpectAndReturn(&expression, (Token*)two	  );	//2
	getToken_ExpectAndReturn(&expression, (Token*)Plus1 );	//+
  getToken_ExpectAndReturn(&expression, (Token*)three );	//3
	getToken_ExpectAndReturn(&expression, (Token*)Multi );	//*	
	getToken_ExpectAndReturn(&expression, (Token*)five  );	//5
  getToken_ExpectAndReturn(&expression, (Token*)Plus2 );	//+
	getToken_ExpectAndReturn(&expression, (Token*)six   );	//6
  getToken_ExpectAndReturn(&expression, NULL );	

	Result = evaluate(&expression);
  TEST_ASSERT_EQUAL( 23 , Result);

}

