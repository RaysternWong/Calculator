#include "unity.h"
#include "Evaluate.h"
#include "mock_Token.h"
#include "mock_StringObject.h"
#include <string.h>
#include "Stack.h"
#include "OperatorToken.h"
#include "NumberToken.h"
#include "Operator.h"
#include "TokenDebug.h"
#include "ErrorCode.h"
#include "CException.h"


#define STACK_LENGTH 100

void setUp(void){}

void tearDown(void){}

//   before:           after:
//   |  |   |  |       |  |   |   |
//   |  |   |  |       |  |   | + | (infix)
//   +--+   +--+       +--+   +---+
//    ds     os         ds     os
void test_tryToPushOperatorAndEvaluate_given_plus_should_push_to_stack(void){

	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack	 = stackNew(STACK_LENGTH) ;
	Operator *Plus		 = operatorNewByName("+");
	Operator *ptrOpr;

	tryToPushOperatorAndEvaluate( Plus , operatorStack, dataStack );
	TEST_ASSERT_EQUAL_PTR ( Plus, (Operator *)stackPop( operatorStack));
	TEST_ASSERT_NULL ( (Number *)stackPop( dataStack ) );
}

//   before:             after:
//   | 4 |   |   |       |   |   |   |
//   | 2 |   | + |       | 6 |   | - | (infix)
//   +---+   +---+       +---+   +---+
//    ds     os           ds     os
void test_tryToPushOperatorAndEvaluate_given_2_Plus_4_Plus_should_answer_the_token_six(void){

	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	 = stackNew(STACK_LENGTH);
	Operator *Plus1		 = operatorNewByName("+");
	Operator *minus		 = operatorNewByName("-");
	Operator *op;
	Number *two = numberNew(2);
	Number *four = numberNew(4);
	Number *num;

	//2+4+ same predecedence
	stackPush( dataStack , two );
	stackPush( dataStack , four );
	stackPush( operatorStack , Plus1 );
	tryToPushOperatorAndEvaluate( minus , operatorStack, dataStack );

	num = (Number *)stackPop( dataStack );
	TEST_ASSERT_NOT_NULL ( num );
	TEST_ASSERT_EQUAL (	NUMBER_TOKEN, num->type);
	TEST_ASSERT_EQUAL ( 6 , num->value );
  TEST_ASSERT_NULL ( (Number *)stackPop( dataStack ) );

	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
	TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( SUB_OP , op->info->id );
	TEST_ASSERT_NULL ( (Operator *)stackPop( operatorStack ) );
}

//   before:           after:
//   |   |   |   |       |   |   |   |
//   | 4 |   |   |       | 4 |   | * |
//   | 2 |   | + |       | 2 |   | + | (infix)
//   +---+   +---+       +---+   +---+
//     ds     os          ds      os
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

//   before:           after:
//   |  |   |   |       |  |   |   |
//   |  |   |   |       |  |   | ( |
//   |  |   | ( |       |  |   | ( | (prefix)
//   +--+   +---+       +--+   +---+
//    ds     os         ds     os
void test_tryToPushOperatorAndEvaluate_given_bracket_bracket_put_into_stack(void){

  Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	 = stackNew(STACK_LENGTH);
	Operator *openBracket1	 = operatorNewByName("(");
	Operator *openBracket2	 = operatorNewByName("(");

  stackPush( operatorStack , openBracket1 );
	tryToPushOperatorAndEvaluate(openBracket2 , operatorStack, dataStack );

  Operator *op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( OPEN_BRACKET , op->info->id );

  op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( OPEN_BRACKET , op->info->id );
  TEST_ASSERT_NULL ( (Operator *)stackPop( operatorStack ) );
}

//   before:      +   intermediate: +      after:
//   | 5 |   |   |    |   |   |   |        |   |   |   |
//   | 4 |   | * |    |20 |   |   |        |   |   |   |
//   | 2 |   | + |    | 2 |   | + |        |22 |   | + | (infix)
//   +---+   +---+    +---+   +---+        +---+   +---+
//     ds     os        ds     os          ds     os
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

//   before: &        intermediate: &      after:
//   | 7 |   |   |    |   |   |   |       |   |   |   |
//   |13 |   | * |    |91 |   |   |       |   |   |   |
//   | 2 |   | + |    | 2 |   | + |       |93 |   | & | (infix)
//   +---+   +---+    +---+   +---+      +---+   +---+
//     ds     os        ds     os         ds     os
void test_tryToPushOperatorAndEvaluate_given_2_Plus_13_Multi_7_AND_should_answer_the_token_ninety_three(void){


	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	   = stackNew(STACK_LENGTH);
	Operator *Plus		   = operatorNewByName("+");
	Operator *BIT_AND    = operatorNewByName("&");
	Operator *Multi		   = operatorNewByName("*");
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

// test given two add three should be able to pop out the number 5 result from the dataStack and operatorStack is empty
void test_doOperatorStackRewinding_given_2_add_3_should_pop_out_5_from_the_dataStack_and_operatorStack_is_empty(void) {
	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	   = stackNew(STACK_LENGTH);
  Number *two = numberNew(2);
  Number *three = numberNew(3);
  Number *answer;
  Operator *add = operatorNewByName("+");
  
  stackPush(dataStack, two);
  stackPush(dataStack, three);
  stackPush(operatorStack, add);
  
  doOperatorStackRewinding(dataStack, operatorStack);
  
  answer = (Number *)stackPop(dataStack);
  TEST_ASSERT_NOT_NULL(answer);
  TEST_ASSERT_EQUAL(5, answer->value);
  TEST_ASSERT_NULL((Operator *)stackPop(operatorStack));
}

// test given 4 add 5 multiply 6 should be able to pop out the number 34 from the dataStack and operatorStack is empty
void test_doOperatorStackRewinding_given_4_add_5_multiply_6_should_pop_out_34_from_the_dataStack_and_operatorStack_is_empty(void) {
	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	   = stackNew(STACK_LENGTH);
  Number *four = numberNew(4);
  Number *five = numberNew(5);
  Number *six = numberNew(6);
  Operator *add = operatorNewByName("+");
  Operator *multiply = operatorNewByName("*");
  Number *answer;
  
  stackPush(dataStack, four);
  stackPush(dataStack, five);
  stackPush(dataStack, six);
  stackPush(operatorStack, add);
  stackPush(operatorStack, multiply);
  
  doOperatorStackRewinding(dataStack, operatorStack);
  
  answer = (Number *)stackPop(dataStack);
  TEST_ASSERT_NOT_NULL(answer);
  TEST_ASSERT_EQUAL(34, answer->value);
  TEST_ASSERT_NULL((Operator *)stackPop(operatorStack));
}

// test given 2 add should throw an error due to ERR_INCOMPLETE_NUMBER
void test_doOperatorStackRewinding_given_2_and_add_should_throw_an_error_due_to_ERR_INCOMPLETE_NUMBER(void) {
	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	   = stackNew(STACK_LENGTH);
  Number *two = numberNew(2);
  Operator *add = operatorNewByName("+");
  CEXCEPTION_T err;
  
  Try {
    stackPush(dataStack, two);
    stackPush(operatorStack, add);
    doOperatorStackRewinding(dataStack, operatorStack);
    TEST_FAIL_MESSAGE("Should throw an error due to ERR_INCOMPLETE_NUMBER");
  } Catch(err) {
      TEST_ASSERT_EQUAL_MESSAGE(ERR_INCOMPLETE_NUMBER, err, "Expect ERR_INCOMEPLETE_NUMBER");
    }
}

// test given add should throw an error due to ERR_INCOMPLETE_NUMBER
void test_doOperatorStackRewinding_given_add_should_throw_an_error_due_to_ERR_INCOMPLETE_NUMBER(void) {
	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	   = stackNew(STACK_LENGTH);
  Operator *add = operatorNewByName("+");
  CEXCEPTION_T err;
  
  Try {
    stackPush(operatorStack, add);
    doOperatorStackRewinding(dataStack, operatorStack);
    TEST_FAIL_MESSAGE("Should throw an error due to ERR_INCOMPLETE_NUMBER");
  } Catch(err) {
      TEST_ASSERT_EQUAL_MESSAGE(ERR_INCOMPLETE_NUMBER, err, "Expect ERR_INCOMEPLETE_NUMBER");
    }
}

// test given open bracket 2 should throw an error due to ERR_NO_CLOSING_BRACKET
void test_doOperatorStackRewinding_given_open_bracket_2_should_throw_an_error_due_to_ERR_NO_CLOSING_BRACKET(void) {
	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	   = stackNew(STACK_LENGTH);
  Operator *openBracket = operatorNewByName("(");
  Number *two = numberNew(2);
  CEXCEPTION_T err;
  
  Try {
    stackPush(operatorStack, openBracket);
    stackPush(dataStack, two);
    doOperatorStackRewinding(dataStack, operatorStack);
    TEST_FAIL_MESSAGE("Should throw an error due to ERR_NO_CLOSING_BRACKET");
  } Catch(err) {
      TEST_ASSERT_EQUAL_MESSAGE(ERR_NO_CLOSING_BRACKET, err, "Expect ERR_NO_CLOSING_BRACKET");
    }
}
// test given open bracket and 2 should throw an error due to ERR_NO_CLOSING_BRACKET
// void test_given_open_bracket_and_2_should_throw_an_error_due_to_ERR_NO_CLOSING_BRACKET(void) {
	// Stack *operatorStack = stackNew(STACK_LENGTH);
	// Stack *dataStack 	   = stackNew(STACK_LENGTH);
  // Operator *openBracket = operatorNewByName("(");
  // Number *two = numberNew(2);
  // CEXCEPTION_T err;
  
  // Try {
    // stackPush(dataStack, two);
    // stackPush(operatorStack, openBracket);
    // doOperatorStackRewinding(dataStack, operatorStack);
    // TEST_FAIL_MESSAGE("Should throw an error due to ERR_NO_CLOSING_BRACKET");
  // } Catch(err) {
      // TEST_ASSERT_EQUAL_MESSAGE(ERR_NO_CLOSING_BRACKET, err, "Expect ERR_NO_CLOSING_BRACKET");
    // }
// }


void test_evaluatePostfixesAndInfix_given_push_5_into_postfix_should_throw_exception(void){

  CEXCEPTION_T err;
  Stack *dataStack     = stackNew(STACK_LENGTH);
	Stack *operatorStack = stackNew(STACK_LENGTH);
  Number *five   = numberNew(5);
  Number *two    = numberNew(2);

  String expression  = {.string="2 5"};
  stackPush (dataStack, two);

  Try{
         evaluatePostfixesAndInfix((Token*)five, &expression,  dataStack,  operatorStack);
         TEST_FAIL_MESSAGE("should throw ERR_NOT_EXPECTING_NUMBER exception");
  } Catch (err)
     { TEST_ASSERT_EQUAL_MESSAGE( ERR_NOT_EXPECTING_NUMBER , err , "Expected ERR_NOT_EXPECTING_NUMBER exception"); }     
     

  Number *num = (Number *)stackPop( dataStack );
  TEST_ASSERT_EQUAL (	2 , num->value);
}

void test_evaluatePostfixesAndInfix_given_$_2_Plus_should_put_into_stack(void){

  int Result;
  Stack *dataStack       = stackNew(STACK_LENGTH);
	Stack *operatorStack   = stackNew(STACK_LENGTH);
  Number *two            = numberNew(2);
  Operator *plus		     = operatorNewByName("+");
  Operator *dollar	     = operatorNewByName("$");

  Operator *op;
  String expression  = {.string="$2    +"};

  stackPush(operatorStack, dollar);
  stackPush(dataStack    ,two);
  getToken_ExpectAndReturn(&expression, NULL  );

  evaluatePostfixesAndInfix((Token*)plus , &expression, dataStack, operatorStack);
  Number *num = (Number *)stackPop( dataStack );
  TEST_ASSERT_EQUAL (	2 , num->value);

  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( ADD_OP , op->info->id );
  
  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( DOLLAR_OP , op->info->id );

}

void test_evaluatePostfixesAndInfix_given_2_and_pass_in_NULL_should_return_only_2(void){

  int Result;
  Stack *dataStack       = stackNew(STACK_LENGTH);
	Stack *operatorStack   = stackNew(STACK_LENGTH);
  Number *two            = numberNew(2);
  Operator *op;
  String expression  = {.string="2"};


  stackPush(dataStack    ,two);

  evaluatePostfixesAndInfix( NULL , &expression, dataStack, operatorStack);
  Number *num = (Number *)stackPop( dataStack );
  TEST_ASSERT_EQUAL (	2 , num->value);

  TEST_ASSERT_NULL  ( stackPop(operatorStack) );
}

void test_evaluatePostfixesAndInfix_given_2_and_pass_in_bracket_should_throw_exception(void){

  int Result;
  CEXCEPTION_T err;
  Stack *dataStack       = stackNew(STACK_LENGTH);
	Stack *operatorStack   = stackNew(STACK_LENGTH);
  Number *two            = numberNew(2);
  Operator *op;
  Operator *openBracket  = operatorNewByName("(");
  String expression      = {.string="2   ("};

  Try{ 
      stackPush(dataStack    ,two);
      evaluatePostfixesAndInfix( (Token*)openBracket , &expression, dataStack, operatorStack);
      TEST_FAIL_MESSAGE("should throw ERR_NOT_EXPECTING_PREFIX_OPERATOR exception");
      
  } Catch (err)
     { TEST_ASSERT_EQUAL_MESSAGE( ERR_NOT_EXPECTING_PREFIX_OPERATOR , err , "Expected ERR_NOT_EXPECTING_PREFIX_OPERATOR exception"); }     
  
  
  Number *num = (Number *)stackPop( dataStack );
  TEST_ASSERT_EQUAL (	2 , num->value);

  TEST_ASSERT_NULL  ( stackPop(operatorStack) );
}

void test_evaluatePostfixesAndInfix_given_bracket_2_and_pass_in_NULL_should_only_return_2(void){

  int Result;
  Stack *dataStack       = stackNew(STACK_LENGTH);
	Stack *operatorStack   = stackNew(STACK_LENGTH);
  Number *two            = numberNew(2);
  Operator *op;
  Operator *openBracket  = operatorNewByName("(");
  String expression  = {.string="(2     "};

  stackPush(operatorStack,openBracket);
  stackPush(dataStack    ,two);

  evaluatePostfixesAndInfix( NULL , &expression, dataStack, operatorStack);
  Number *num = (Number *)stackPop( dataStack );
  TEST_ASSERT_EQUAL (	2 , num->value);

  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( OPEN_BRACKET , op->info->id );

}


void test_evaluatePostfixesAndInfix_given_2_plus_should_put_plus_into_stack(void){

  int Result;
  Stack *dataStack       = stackNew(STACK_LENGTH);
	Stack *operatorStack   = stackNew(STACK_LENGTH);
  Number *two            = numberNew(2);
  Operator *plus		     = operatorNewByName("+");
  Operator *op;
  String expression  = {.string="2    +"};

  stackPush(dataStack    ,two);
  getToken_ExpectAndReturn(&expression, NULL  );

  evaluatePostfixesAndInfix((Token*)plus , &expression, dataStack, operatorStack);
  Number *num = (Number *)stackPop( dataStack );
  TEST_ASSERT_EQUAL (	2 , num->value);

  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( ADD_OP , op->info->id );
  TEST_ASSERT_NULL  ( stackPop(operatorStack) );

}

void test_evaluatePostfixesAndInfix_given_negative2_plus_should_put_plus_into_stack(void){

  int Result;
  Stack *dataStack       = stackNew(STACK_LENGTH);
	Stack *operatorStack   = stackNew(STACK_LENGTH);
  Number *minusTwo       = numberNew(-2);
  Operator *plus		     = operatorNewByName("+");

  Operator *op;
  
  String expression  = {.string="-2    +"};


  stackPush(dataStack    ,minusTwo);
  getToken_ExpectAndReturn(&expression, NULL  );

  evaluatePostfixesAndInfix((Token*)plus , &expression, dataStack, operatorStack);
  Number *num = (Number *)stackPop( dataStack );
  TEST_ASSERT_EQUAL (	-2 , num->value);

  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( ADD_OP , op->info->id );
  TEST_ASSERT_NULL  ( stackPop(operatorStack) );

}


void test_evaluatePostfixesAndInfix_bracket_2_should_only_ans_2(void){

  int Result;
  Stack *dataStack       = stackNew(STACK_LENGTH);
	Stack *operatorStack   = stackNew(STACK_LENGTH);
  Number *two            = numberNew(2);
  Operator *openBracket  = operatorNewByName("(");
  Operator *closeBracket = operatorNewByName(")");
  Operator *op;
  String expression  = {.string="(2    )"};

  stackPush(operatorStack,openBracket);
  stackPush(dataStack    ,two         );
  
  getToken_ExpectAndReturn( &expression, NULL  );
  printf("testing");
  evaluatePostfixesAndInfix( (Token*)closeBracket , &expression, dataStack, operatorStack);

  Number *num = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL (	2 , num->value);
  TEST_ASSERT_NULL  ( stackPop(operatorStack) );  //test wheter all the brackets is removed
}

void test_evaluatePostfixesAndInfix_given_brackt_2_plus_should_put_plus_into_stack(void){

  int Result;
  Stack *dataStack       = stackNew(STACK_LENGTH);
	Stack *operatorStack   = stackNew(STACK_LENGTH);
  Number *two            = numberNew(2);
  Operator *plus		     = operatorNewByName("+");
  Operator *openBracket  = operatorNewByName("(");
  Operator *closeBracket = operatorNewByName(")");
  Operator *op;
  String expression  = {.string="(2    )+"};

  stackPush(operatorStack,openBracket);
  stackPush(dataStack    ,two);

  getToken_ExpectAndReturn(&expression, (Token*)plus  );
  getToken_ExpectAndReturn(&expression, NULL  );

  evaluatePostfixesAndInfix((Token*)closeBracket , &expression, dataStack, operatorStack);

  Number *num = (Number *)stackPop( dataStack );
  TEST_ASSERT_EQUAL (	2 , num->value);

  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( ADD_OP , op->info->id );
  TEST_ASSERT_NULL  ( stackPop(operatorStack) );
}

void xtest_evaluatePostfixesAndInfix_given_brackt_2_plus_3_should_put_plus_into_stack(void){

  int Result;
  Stack *dataStack       = stackNew(STACK_LENGTH);
	Stack *operatorStack   = stackNew(STACK_LENGTH);
  Number *two            = numberNew(2);
  Number *three          = numberNew(3);
  Operator *plus		     = operatorNewByName("+");
  Operator *openBracket  = operatorNewByName("(");
  Operator *closeBracket = operatorNewByName(")");
  Operator *op;
  String expression  = {.string="(2+3   )+"};

  stackPush(operatorStack,openBracket);
  stackPush(dataStack    ,two);
  stackPush(operatorStack,plus);
  stackPush(dataStack    ,three);
  
  getToken_ExpectAndReturn(&expression, (Token*)plus  );
  getToken_ExpectAndReturn(&expression, NULL  );

  evaluatePostfixesAndInfix((Token*)closeBracket , &expression, dataStack, operatorStack);

  Number *num = (Number *)stackPop( dataStack );
  TEST_ASSERT_EQUAL (	5 , num->value);

  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( ADD_OP , op->info->id );
  
  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NULL ( op );
}

void test_evaluatePostfixesAndInfix_given_double_bracket_2_should_only_return_2(void){

  int Result;
  Stack *dataStack       = stackNew(STACK_LENGTH);
	Stack *operatorStack   = stackNew(STACK_LENGTH);
  Number *two            = numberNew(2);
  Operator *openBracket1  = operatorNewByName("(");
  Operator *openBracket2  = operatorNewByName("(");
  Operator *closeBracket1 = operatorNewByName(")");
  Operator *closeBracket2 = operatorNewByName(")");
  Operator *op;

  String expression  = {.string=" ((2   ))"};

  stackPush(operatorStack,openBracket1);
  stackPush(operatorStack,openBracket2);
  stackPush(dataStack    ,two);

  getToken_ExpectAndReturn(&expression, (Token*)closeBracket1	  );
  getToken_ExpectAndReturn(&expression, NULL  );

  evaluatePostfixesAndInfix((Token*)closeBracket2, &expression, dataStack, operatorStack);

  Number *num = (Number *)stackPop( dataStack );
  TEST_ASSERT_EQUAL (	2 , num->value);
   
  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NULL ( op );
}

void test_evaluatePostfixesAndInfix_given_double_bracket_2_minus_should_only_return_2_and_minus(void){

  int Result;
  CEXCEPTION_T err;
  Stack *dataStack       = stackNew(STACK_LENGTH);
	Stack *operatorStack   = stackNew(STACK_LENGTH);
  Number *two            = numberNew(2);
  Operator *openBracket1  = operatorNewByName("(");
  Operator *openBracket2  = operatorNewByName("(");
  Operator *closeBracket1 = operatorNewByName(")");
  Operator *closeBracket2 = operatorNewByName(")");
  Operator *plus       = operatorNewByName("+");
  Operator *op;

  String expression  = {.string=" ((2   ))+"};

  stackPush(operatorStack,openBracket1);
  stackPush(operatorStack,openBracket2);
  stackPush(dataStack    ,two);

  getToken_ExpectAndReturn(&expression, (Token*)closeBracket1   );
  getToken_ExpectAndReturn(&expression, (Token*)plus   );
  getToken_ExpectAndReturn(&expression, NULL  );


  evaluatePostfixesAndInfix((Token*)closeBracket2	, &expression, dataStack, operatorStack);
  Number *num = (Number *)stackPop( dataStack );
  TEST_ASSERT_EQUAL (	2 , num->value);
   
  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( ADD_OP , op->info->id );
   
  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NULL ( op );
}
void test_evaluatePostfixesAndInfix_given_1plus5_multi_should_put_multi_into_stack_ans_5(void){

  int Result;
  Stack *dataStack       = stackNew(STACK_LENGTH);
	Stack *operatorStack   = stackNew(STACK_LENGTH);
  Number *one            = numberNew(1);
  Number *five           = numberNew(5);
  Operator *plus  = operatorNewByName("+");
  Operator *multi = operatorNewByName("*");
  Operator *op;
  String expression  = {.string="1+5 *"};

  stackPush(dataStack    ,one);
  stackPush(operatorStack,plus );
  stackPush(dataStack    ,five);

  getToken_ExpectAndReturn(&expression, NULL  );

  evaluatePostfixesAndInfix((Token*)multi , &expression, dataStack, operatorStack);

  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
  TEST_ASSERT_EQUAL (	multi, op);

  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
  TEST_ASSERT_EQUAL (	plus, op);

  Number *num = (Number *)stackPop( dataStack );
  TEST_ASSERT_EQUAL (	5 , num->value);
}

void test_evaluatePostfixesAndInfix_given_2multi5_plus_should_ans_10(void){

  int Result;
  Stack *dataStack       = stackNew(STACK_LENGTH);
	Stack *operatorStack   = stackNew(STACK_LENGTH);
  Number *two            = numberNew(2);
  Number *five           = numberNew(5);
  Operator *plus         = operatorNewByName("+");
  Operator *multi        = operatorNewByName("*");
  Operator *op;
  String expression  = {.string="2*5 +"};

  stackPush(dataStack     , two );
  stackPush(operatorStack ,multi);
  stackPush(dataStack     ,five );
  
  getToken_ExpectAndReturn( &expression, NULL  );
  evaluatePostfixesAndInfix( (Token*)plus , &expression, dataStack, operatorStack );

  Number *num = (Number *)stackPop( dataStack );
  TEST_ASSERT_EQUAL (	10 , num->value);

  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
  TEST_ASSERT_EQUAL (	plus, op);
  TEST_ASSERT_NULL  ( stackPop( operatorStack ));
}

// test whether the minus that is infix got change to prefix or not
void test_convertToPrefixIfNotAlready_given_infix_minus_should_be_able_to_convert_to_prefix(void) {
  OperatorInfo *info = getOperatorByID(SUB_OP);
  Operator operator = {.type = OPERATOR_TOKEN, info};

  Token *token = convertToPrefixIfNotAlready(&operator);
  Operator *operate = (Operator *)token;
  TEST_ASSERT_EQUAL(PREFIX, operate->info->affix);
}

// test given multiply should throw an exception due to multiply is not in secondaryOperatorTable
void test_convertToPrefixIfNotAlready_given_infix_multiply_should_throw_an_exception(void) {
  OperatorInfo *info = getOperatorByID(MUL_OP);
  Operator operator = {.type = OPERATOR_TOKEN, info};
  CEXCEPTION_T err;

  Try {
    Token *token = convertToPrefixIfNotAlready(&operator);
    Operator *operate = (Operator *)token;
    TEST_FAIL_MESSAGE("Should throw an exception due to ERR_NOT_PREFIX_OPERATOR");
  } Catch(err) {
      TEST_ASSERT_EQUAL_MESSAGE(ERR_NOT_PREFIX_OPERATOR, err, "Expected ERR_NOT_PREFIX_OPERATOR");
    }
}

// test given prefix operator should do nothing
void test_convertToPrefixIfNotAlready_given_prefix_should_do_nothing(void) {
  OperatorInfo *info = getOperatorByID(NOT_OP);
  Operator operator = {.type = OPERATOR_TOKEN, info};

  Token *token = convertToPrefixIfNotAlready(&operator);
  Operator *operate = (Operator *)token;
  TEST_ASSERT_EQUAL(PREFIX, operate->info->affix);
}

// test given number 2 should be able to pop out integer 2 from the dataStack
void test_evaluatePrefixesAndNumber_given_integer_two_should_be_able_to_pop_out_integer_two_from_dataStack(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "2"};
  Number *two = numberNew(2);
  Number *dataResult;

  evaluatePrefixesAndNumber((Token *)two, &expression, dataStack, operatorStack);
  dataResult = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(2, dataResult->value);

  stackDel(dataStack);
  stackDel(operatorStack);
}

// Given logical NOT 3 should be able to push 3 into dataStack and logical NOT into operatorStack
void test_evaluatePrefixesAndNumber_given_logical_NOT_3_should_place_logical_NOT_and_3_in_dataStack_and_operatorStack_respectively(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "!3"};
  Operator *not = operatorNewByName("!");
  Number *three = numberNew(3);
  Number *dataResult;
  Operator *operatorResult;

  getToken_ExpectAndReturn(&expression, (Token *)three);

  evaluatePrefixesAndNumber((Token *)not, &expression, dataStack, operatorStack);
  dataResult = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(3, dataResult->value);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("!", operatorResult->info->name);

  stackDel(dataStack);
  stackDel(operatorStack);
}

// test given minus and 4 should be able to push minus into operatorStack and 4 into dataStack
void test_evaluatePrefixesAndNumber_given_minus_4_should_place_prefix_minus_and_4_into_dataStack_and_operatorStack_respectively(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "-4"};
  Operator *minus = operatorNewByName("-");
  Number *four = numberNew(4);
  Number *dataResult;
  Operator *operatorResult;

  getToken_ExpectAndReturn(&expression, (Token *)four);

  evaluatePrefixesAndNumber((Token *)minus, &expression, dataStack, operatorStack);
  dataResult = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(4, dataResult->value);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("-", operatorResult->info->name);
  TEST_ASSERT_EQUAL(PREFIX, operatorResult->info->affix);

  stackDel(dataStack);
  stackDel(operatorStack);
}

// test given multiply operator should throw an error due to ERR_NOT_PREFIX_OPERATOR
void test_evaluatePrefixesAndNumber_given_operator_multiply_should_throw_an_error(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "*5"};
  Operator *multiply = operatorNewByName("*");
  CEXCEPTION_T err;

  Try {
    evaluatePrefixesAndNumber((Token *)multiply, &expression, dataStack, operatorStack);
    TEST_FAIL_MESSAGE("Should throw an exception due to ERR_NOT_PREFIX_OPERATOR");
  } Catch(err) {
      TEST_ASSERT_EQUAL_MESSAGE(ERR_NOT_PREFIX_OPERATOR, err, "Expected ERR_NOT_PREFIX_OPERATOR");
    }

  stackDel(dataStack);
  stackDel(operatorStack);
}

// test given minus minus and 6 should be able to push minus and minus into operatorStack and 6 to dataStack
void test_evaluatePrefixesAndNumber_given_minus_minus_6_should_be_able_to_push_into_dataStack_and_operatorStack_respectively(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "--6"};
  Operator *firstMinus = operatorNewByName("-");
  Operator *secondMinus = operatorNewByName("-");
  Number *six = numberNew(6);
  Number *dataResult;
  Operator *operatorResult;

  getToken_ExpectAndReturn(&expression, (Token *)secondMinus);
  getToken_ExpectAndReturn(&expression, (Token *)six);

  evaluatePrefixesAndNumber((Token *)firstMinus, &expression, dataStack, operatorStack);
  dataResult = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(6, dataResult->value);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("-", operatorResult->info->name);
  TEST_ASSERT_EQUAL(PREFIX, operatorResult->info->affix);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("-", operatorResult->info->name);
  TEST_ASSERT_EQUAL(PREFIX, operatorResult->info->affix);

  stackDel(dataStack);
  stackDel(operatorStack);
}

// test given minus plus minus and 7 should be able to push minus plus minus into operatorStack and 7 to dataStack
void test_evaluatePrefixesAndNumber_given_minus_plus_minus_and_7_should_be_able_to_push_into_dataStack_and_operatorStack_respectively(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "-+-7"};
  Operator *firstMinus = operatorNewByName("-");
  Operator *plus = operatorNewByName("+");
  Operator *secondMinus = operatorNewByName("-");
  Number *seven = numberNew(7);
  Number *dataResult;
  Operator *operatorResult;

  getToken_ExpectAndReturn(&expression, (Token *)plus);
  getToken_ExpectAndReturn(&expression, (Token *)secondMinus);
  getToken_ExpectAndReturn(&expression, (Token *)seven);

  evaluatePrefixesAndNumber((Token *)firstMinus, &expression, dataStack, operatorStack);
  dataResult = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(7, dataResult->value);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("-", operatorResult->info->name);
  TEST_ASSERT_EQUAL(PREFIX, operatorResult->info->affix);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("+", operatorResult->info->name);
  TEST_ASSERT_EQUAL(PREFIX, operatorResult->info->affix);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("-", operatorResult->info->name);
  TEST_ASSERT_EQUAL(PREFIX, operatorResult->info->affix);

  stackDel(dataStack);
  stackDel(operatorStack);
}

// test given open bracket and 8 should be able to push 8 into dataStack and open bracket into operatorStack
void test_evaluatePrefixesAndNumber_given_openBracket_and_integer_two_should_be_able_to_push_into_dataStack_and_operatorStack(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "(8"};
  Operator *openBracket = operatorNewByName("(");
  Number *eight = numberNew(8);
  Number *dataResult;
  Operator *operatorResult;

  getToken_ExpectAndReturn(&expression, (Token *)eight);

  evaluatePrefixesAndNumber((Token *)openBracket, &expression, dataStack, operatorStack);
  dataResult = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(8, dataResult->value);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("(", operatorResult->info->name);
  TEST_ASSERT_EQUAL(PREFIX, operatorResult->info->affix);

  stackDel(dataStack);
  stackDel(operatorStack);
}

// test given openBracket openBracket and 9 should be able to push 9 into dataStack and open bracket open bracket into operatorStack
void test_evaluatePrefixesAndNumber_given_openBracket_openBracket_and_integer_two_should_be_able_to_push_into_dataStack_and_operatorStack(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "((9"};
  Operator *firstOpenBracket = operatorNewByName("(");
  Operator *secondOpenBracket = operatorNewByName("(");
  Number *nine = numberNew(9);
  Number *dataResult;
  Operator *operatorResult;

  getToken_ExpectAndReturn(&expression, (Token *)secondOpenBracket);
  getToken_ExpectAndReturn(&expression, (Token *)nine);

  evaluatePrefixesAndNumber((Token *)firstOpenBracket, &expression, dataStack, operatorStack);
  dataResult = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(9, dataResult->value);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("(", operatorResult->info->name);
  TEST_ASSERT_EQUAL(PREFIX, operatorResult->info->affix);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("(", operatorResult->info->name);
  TEST_ASSERT_EQUAL(PREFIX, operatorResult->info->affix);

  stackDel(dataStack);
  stackDel(operatorStack);
}

// test given minus only should throw an error due to ERR_EXPECTING_NUMBER
void test_evaluatePrefixesAndNumber_given_minus_only_should_throw_an_error(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "-"};
  Operator *minus = operatorNewByName("-");
  CEXCEPTION_T err;

  Try {
    getToken_ExpectAndReturn(&expression, NULL);
    evaluatePrefixesAndNumber((Token *)minus, &expression, dataStack, operatorStack);
    TEST_FAIL_MESSAGE("Should throw an error due to ERR_EXPECTING_NUMBER");
  } Catch(err) {
      TEST_ASSERT_EQUAL_MESSAGE(ERR_EXPECTING_NUMBER, err, "Expected ERR_EXPECTING_NUMBER");
    }

  stackDel(dataStack);
  stackDel(operatorStack);
}

// test given minus and plus only should be able to throw an error due to ERR_EXPECTING_NUMBER
void test_evaluatePrefixesAndNumber_given_minus_and_plus_should_throw_an_error(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "-+"};
  Operator *minus = operatorNewByName("-");
  Operator *plus = operatorNewByName("+");
  CEXCEPTION_T err;

  Try {
    getToken_ExpectAndReturn(&expression, (Token *)plus);
    getToken_ExpectAndReturn(&expression, NULL);
    evaluatePrefixesAndNumber((Token *)minus, &expression, dataStack, operatorStack);
    TEST_FAIL_MESSAGE("Should throw an error due to ERR_EXPECTING_NUMBER");
  } Catch(err) {
      TEST_ASSERT_EQUAL_MESSAGE(ERR_EXPECTING_NUMBER, err, "Expected ERR_EXPECTING_NUMBER");
    }

  stackDel(dataStack);
  stackDel(operatorStack);
}

// test given minus plus and multiply should throw ana error due to ERR_NOT_PREFIX_OPERATOR
void test_evaluatePrefixesAndNumber_given_minus_plus_and_multiply_should_throw_an_error(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "-+*"};
  Operator *minus = operatorNewByName("-");
  Operator *plus = operatorNewByName("+");
  Operator *multiply = operatorNewByName("*");
  CEXCEPTION_T err;

  Try {
    getToken_ExpectAndReturn(&expression, (Token *)plus);
    getToken_ExpectAndReturn(&expression, (Token *)multiply);
    evaluatePrefixesAndNumber((Token *)minus, &expression, dataStack, operatorStack);
    TEST_FAIL_MESSAGE("Should throw an error due to ERR_NOT_PREFIX_OPERATOR");
  } Catch(err) {
      TEST_ASSERT_EQUAL_MESSAGE(ERR_NOT_PREFIX_OPERATOR, err, "Expected ERR_NOT_PREFIX_OPERATOR");
    }

  stackDel(dataStack);
  stackDel(operatorStack);
}

// test given 2 should be able to return the result 2
void test_evaluate_given_2_should_return_ans_2(void){

   int result;
   String expression = {.string = "2"};
   Number *two = numberNew(2);

   getToken_ExpectAndReturn(&expression, (Token *)two);
   getToken_ExpectAndReturn(&expression, NULL);

   result = evaluate ( &expression );
   TEST_ASSERT_EQUAL(2 , result);

}

// test given minus 3 should be able to return the result -3
void test_evaluate_given_minus_3_should_be_able_to_return_the_result_negative_3(void){
  int result;
  String expression = {.string = "-3"};
  Number *three = numberNew(3);
  Operator *minus = operatorNewByName("-");
  
  getToken_ExpectAndReturn(&expression, (Token *)minus);
  getToken_ExpectAndReturn(&expression, (Token *)three);
  getToken_ExpectAndReturn(&expression, NULL);
  
  result = evaluate(&expression);
  TEST_ASSERT_EQUAL(-3, result);
}

// test given minus plus 4 should be able to return the result -4
void test_evaluate_given_minus_plus_4_should_be_able_to_return_the_result_negative_4(void){
  int result;
  String expression = {.string = "-+4"};
  Number *four = numberNew(4);
  Operator *minus = operatorNewByName("-");
  Operator *plus = operatorNewByName("+");
  
  getToken_ExpectAndReturn(&expression, (Token *)minus);
  getToken_ExpectAndReturn(&expression, (Token *)plus);
  getToken_ExpectAndReturn(&expression, (Token *)four);
  getToken_ExpectAndReturn(&expression, NULL);
  
  result = evaluate(&expression);
  TEST_ASSERT_EQUAL(-4, result);
}

// test given plus minus and multiply 234 should throw an error due to ERR_NOT_PREFIX_OPERATOR
void test_evaluate_given_plus_minus_multiply_234_should_throw_an_error_due_to_ERR_NOT_PREFIX_OPERATOR(void){
  int result;
  String expression = {.string = "+-*234"};
  Number *num = numberNew(234);
  Operator *plus = operatorNewByName("+");
  Operator *minus = operatorNewByName("-");
  Operator *multiply = operatorNewByName("*");
  CEXCEPTION_T err;
  
  Try {
    getToken_ExpectAndReturn(&expression, (Token *)plus);
    getToken_ExpectAndReturn(&expression, (Token *)minus);
    getToken_ExpectAndReturn(&expression, (Token *)multiply);
    result = evaluate(&expression);
    TEST_FAIL_MESSAGE("Should throw an error due to ERR_NOT_PREFIX_OPERATOR");
  } Catch(err) {
      TEST_ASSERT_EQUAL_MESSAGE(ERR_NOT_PREFIX_OPERATOR, err, "Expect ERR_NOT_PREFIX_OPERATOR");
    }
}

// test given minus only should throw an error due to ERR_EXPECT_NUMBER
void test_evaluate_given_minus_should_throw_an_error_due_to_ERR_EXPECT_NUMBER(void) {
  int result;
  String expression = {.string = "-"};
  Operator *minus = operatorNewByName("-");
  CEXCEPTION_T err;
  
  Try {
    getToken_ExpectAndReturn(&expression, (Token *)minus);
    getToken_ExpectAndReturn(&expression, NULL);
    result = evaluate(&expression);
    TEST_FAIL_MESSAGE("Should throw an error due to ERR_EXPECTING_NUMBER");
  } Catch(err) {
      TEST_ASSERT_EQUAL_MESSAGE(ERR_EXPECTING_NUMBER, err, "Expect ERR_EXPECTING_NUMBER");
    }
}