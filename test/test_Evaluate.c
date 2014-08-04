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
	TEST_ASSERT_NULL ( (Number *)stackPop( dataStack ) );
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
  TEST_ASSERT_NULL ( (Number *)stackPop( dataStack ) );

	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
	TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( ADD_OP , op->info->id );
	TEST_ASSERT_NULL ( (Operator *)stackPop( operatorStack ) );
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

  num = (Number *)stackPop( dataStack );
	TEST_ASSERT_NOT_NULL ( num );
	TEST_ASSERT_EQUAL (	NUMBER_TOKEN, num->type);
	TEST_ASSERT_EQUAL ( 2 , num->value );
  num = (Number *)stackPop( dataStack );
	TEST_ASSERT_NULL ( num );

	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
	TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( MUL_OP , op->info->id );

	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
	TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( ADD_OP , op->info->id );

	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NULL ( op );
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
	TEST_ASSERT_NULL ( (Number *)stackPop( dataStack ) );

	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( ADD_OP , op->info->id );
  TEST_ASSERT_NULL ( (Operator *)stackPop( operatorStack ) );
}

void test_tryToPushOperatorAndEvaluate_given_2_Plus_13_Multi_7_AND_should_answer_the_token_ninety_three(void){


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
	TEST_ASSERT_EQUAL ( 2+(13*7) , num->value );
	TEST_ASSERT_NULL ( (Number *)stackPop( dataStack ) );

	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( BITWISE_AND_OP , op->info->id );
  TEST_ASSERT_NULL ( (Operator *)stackPop( operatorStack ) );
}

void test_doOperatorStackRewinding_given_2_and_3_plus_4_multi_5_should_get_correct_result(void){

	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	   = stackNew(STACK_LENGTH);
  Number *two   = numberNew(2);
	Number *three = numberNew(3);
  Number *four  = numberNew(4);
  Number *five  = numberNew(5);
  Number *num;
	Operator *plus		 = operatorNewByName("+");
  Operator *and 		 = operatorNewByName("&");
	Operator *multi		 = operatorNewByName("*");
  Operator *op;
  
  //2&3+4*5
  stackPush( dataStack , two );
	stackPush( dataStack , three);
	stackPush( dataStack , four );
  stackPush( dataStack , five );
  stackPush( operatorStack , and );
  stackPush( operatorStack , plus );
	stackPush( operatorStack , multi );

  doOperatorStackRewinding ( dataStack , operatorStack );
  
  num = (Number *)stackPop( dataStack );
  TEST_ASSERT_NOT_NULL ( num );
	TEST_ASSERT_EQUAL (	NUMBER_TOKEN, num->type);
	TEST_ASSERT_EQUAL ( 2&3+4*5 , num->value );
  TEST_ASSERT_NULL ( (Number *)stackPop( dataStack ) );
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

void test_evaluate_given_token_2_plus_3_Mutiple_5_plus_6_get_the_correct_result(void){

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
  TEST_ASSERT_EQUAL( 2+3*5+6 , Result);

}

void test_evaluate_given_token_2_plus_3_Mutiple_5_or_26_should_get_the_correct_result(void){

	int Result;
  Number *two   = numberNew(2);
	Number *three = numberNew(3);
  Number *five  = numberNew(5);
  Number *twentySix   = numberNew(26);
	Operator *plus		 = operatorNewByName("+");
  Operator *or  		 = operatorNewByName("|");
	Operator *multi		 = operatorNewByName("*");
	String expression = {.string="2+3*5|26"};

  getToken_ExpectAndReturn(&expression, (Token*)two	       );	//2
	getToken_ExpectAndReturn(&expression, (Token*)plus       );	//+
  getToken_ExpectAndReturn(&expression, (Token*)three      );	//3
	getToken_ExpectAndReturn(&expression, (Token*)multi      );	//*
	getToken_ExpectAndReturn(&expression, (Token*)five       );	//5
  getToken_ExpectAndReturn(&expression, (Token*)or         );	//|
	getToken_ExpectAndReturn(&expression, (Token*)twentySix  );	//26
  getToken_ExpectAndReturn(&expression, NULL );

	Result = evaluate(&expression);
  TEST_ASSERT_EQUAL( 2+3*5|26 , Result);

}


void test_evaluate_given_2_and_3_plus_4_multi_5_should_get_correct_result(void){

	int Result;
  Number *two   = numberNew(2);
	Number *three = numberNew(3);
  Number *four  = numberNew(4);
  Number *five  = numberNew(5);
	Operator *plus		 = operatorNewByName("+");
  Operator *and 		 = operatorNewByName("&");
	Operator *multi		 = operatorNewByName("*");
	String expression  = {.string="2&3+4*5"};

  getToken_ExpectAndReturn(&expression, (Token*)two	  );	//2
	getToken_ExpectAndReturn(&expression, (Token*)and   );	//&
  getToken_ExpectAndReturn(&expression, (Token*)three );	//3
	getToken_ExpectAndReturn(&expression, (Token*)plus  );	//+
	getToken_ExpectAndReturn(&expression, (Token*)four  );	//4
  getToken_ExpectAndReturn(&expression, (Token*)multi );	//*
	getToken_ExpectAndReturn(&expression, (Token*)five  );	//5
  getToken_ExpectAndReturn(&expression, NULL );


	Result = evaluate(&expression);
  TEST_ASSERT_EQUAL( 2&3+4*5 , Result);

}
