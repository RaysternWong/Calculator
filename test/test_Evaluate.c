#include "unity.h"
#include "Evaluate.h"
#include "mock_Token.h"
#include "StringObject.h"
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


// void test_tryToPushOperatorAndEvaluate_given_plus_should_push_to_stack(void)
// {
   // Stack *operatorStack = stackNew(STACK_LENGTH);
	// Stack *dataStack	 = stackNew(STACK_LENGTH) ;
	// Operator *Plus		 = operatorNewByName("+");
	// Operator *ptrOpr;
	
	// tryToPushOperatorAndEvaluate( Plus , operatorStack, dataStack );
	// TEST_ASSERT_EQUAL_PTR ( Plus, (Operator *)stackPop( operatorStack));
	// TEST_ASSERT_NULL ( (Number *)stackPop( dataStack ) );
// }

// void test_tryToPushOperatorAndEvaluate_given_2_Plus_4_Plus_should_answer_the_token_six(void)
// {
	// Stack *operatorStack = stackNew(STACK_LENGTH);
	// Stack *dataStack 	 = stackNew(STACK_LENGTH);
	// Operator *Plus1		 = operatorNewByName("+");
	// Operator *Plus2		 = operatorNewByName("+");
	// Operator *op;
	// Number *two = numberNew(2);
	// Number *four = numberNew(4);
	// Number *num;
	
	// 2+4+ same predecedence 
	// stackPush(dataStack , two);
	// stackPush(dataStack , four);
	// stackPush(operatorStack , Plus1);
	// tryToPushOperatorAndEvaluate(Plus2 , operatorStack, dataStack); 
		
	// num = (Number *)stackPop(dataStack);
	// TEST_ASSERT_NOT_NULL(num);
	// TEST_ASSERT_EQUAL(NUMBER_TOKEN, num->type);
	// TEST_ASSERT_EQUAL( 6 , num->value);
	// TEST_ASSERT_NULL((Number *)stackPop(dataStack));
	
	// op = (Operator *)stackPop(operatorStack);
	// TEST_ASSERT_NOT_NULL (op);
	// TEST_ASSERT_EQUAL(OPERATOR_TOKEN, op->type);
	// TEST_ASSERT_EQUAL(ADD_OP , op->info->id);
	// TEST_ASSERT_NULL((Operator *)stackPop(operatorStack));		
// }

// void test_tryToPushOperatorAndEvaluate_given_2_Plus_4_Multi_should_answer_the_token_four(void)
// {
	// Stack *operatorStack = stackNew(STACK_LENGTH);
	// Stack *dataStack 	 = stackNew(STACK_LENGTH);
	// Operator *Plus		 = operatorNewByName("+");
	// Operator *Multi		 = operatorNewByName("*");
	// Operator *op;
	// Number *two = numberNew(2);
	// Number *four = numberNew(4);
	// Number *num;

	// 2+4* higher precedence
	// stackPush(dataStack, two);
	// stackPush(dataStack, four);
	// stackPush(operatorStack, Plus);
	// tryToPushOperatorAndEvaluate(Multi, operatorStack, dataStack); 
		
	// num = (Number *)stackPop(dataStack);
	// TEST_ASSERT_NOT_NULL (num);
	// TEST_ASSERT_EQUAL(NUMBER_TOKEN, num->type);
	// TEST_ASSERT_EQUAL(4, num->value);

	// num = (Number *)stackPop(dataStack);
	// TEST_ASSERT_NOT_NULL(num);
	// TEST_ASSERT_EQUAL(NUMBER_TOKEN, num->type);
	// TEST_ASSERT_EQUAL(2, num->value);
	// num = (Number *)stackPop(dataStack);
	// TEST_ASSERT_NULL(num);
  
	// op = (Operator *)stackPop(operatorStack);
	// TEST_ASSERT_NOT_NULL(op);
	// TEST_ASSERT_EQUAL(OPERATOR_TOKEN, op->type);
	// TEST_ASSERT_EQUAL(MUL_OP , op->info->id);
  
	// op = (Operator *)stackPop(operatorStack);
	// TEST_ASSERT_NOT_NULL(op);
	// TEST_ASSERT_EQUAL(OPERATOR_TOKEN, op->type);
	// TEST_ASSERT_EQUAL(ADD_OP , op->info->id);  
  
	// op = (Operator *)stackPop(operatorStack);
	// TEST_ASSERT_NULL(op);
// }



// void test_tryToPushOperatorAndEvaluate_given_2_Plus_4_Multi_5_Plus_should_answer_the_token_twenty_two(void)
// {
	// Stack *operatorStack = stackNew(STACK_LENGTH);
	// Stack *dataStack 	 = stackNew(STACK_LENGTH);
	// Operator *Plus1		 = operatorNewByName("+");
	// Operator *Plus2		 = operatorNewByName("+");
	// Operator *Multi		 = operatorNewByName("*");
	// Operator *op;
	// Number *two  = numberNew(2);
	// Number *four = numberNew(4);
	// Number *five = numberNew(5);
	// Number *num;

	// 2+4*5+ same precedence
	// stackPush(dataStack , two);
	// stackPush(dataStack , four);
	// stackPush(dataStack , five);
	// stackPush(operatorStack, Plus1);
	// stackPush(operatorStack, Multi);
  
	// tryToPushOperatorAndEvaluate(Plus2, operatorStack, dataStack); 
	
	// num = (Number *)stackPop(dataStack);
	// TEST_ASSERT_NOT_NULL( num );
	// TEST_ASSERT_EQUAL(NUMBER_TOKEN, num->type);
	// TEST_ASSERT_EQUAL(22 , num->value);
	// TEST_ASSERT_NULL((Number *)stackPop(dataStack));
	
	// op = (Operator *)stackPop(operatorStack);
	// TEST_ASSERT_NOT_NULL(op);
	// TEST_ASSERT_EQUAL(OPERATOR_TOKEN, op->type);
	// TEST_ASSERT_EQUAL(ADD_OP , op->info->id);
	// TEST_ASSERT_NULL((Operator *)stackPop(operatorStack));		
// }

// void test_tryToPushOperatorAndEvaluate_given_2_Plus_13_Multi_7_AND_should_answer_the_token_ninety_three(void)
// {
	// Stack *operatorStack = stackNew(STACK_LENGTH);
	// Stack *dataStack 	 = stackNew(STACK_LENGTH);
	// Operator *Plus		 = operatorNewByName("+");
	// Operator *BIT_AND    = operatorNewByName("&");
	// Operator *Multi		 = operatorNewByName("*");
	// Operator *op;
	// Number *two       = numberNew(2);
	// Number *thirteen  = numberNew(13);
	// Number *seven     = numberNew(7);
	// Number *num;

	// 2+13*7& same precedence
	// stackPush(dataStack, two);
	// stackPush(dataStack, thirteen);
	// stackPush(dataStack, seven);
	// stackPush(operatorStack, Plus);
	// stackPush(operatorStack, Multi);
	
	// tryToPushOperatorAndEvaluate(BIT_AND, operatorStack, dataStack); 
	
	// num = (Number *)stackPop(dataStack);
	// TEST_ASSERT_NOT_NULL(num);
	// TEST_ASSERT_EQUAL(NUMBER_TOKEN, num->type);
	// TEST_ASSERT_EQUAL(2+(13*7) , num->value);
	// TEST_ASSERT_NULL((Number *)stackPop(dataStack));
	
	// op = (Operator *)stackPop(operatorStack);
	// TEST_ASSERT_NOT_NULL(op);
	// TEST_ASSERT_EQUAL(OPERATOR_TOKEN, op->type);
	// TEST_ASSERT_EQUAL(BITWISE_AND_OP, op->info->id);
	// TEST_ASSERT_NULL((Operator *)stackPop(operatorStack));		
// }

// void test_evaluate_given_token_2_plus_3_should_get_5(void)
// {
	// int Result;
	
	// Number *two = numberNew(2);
	// Number *three = numberNew(3);
	// Operator *Plus = operatorNewByName("+"); 
	// String expression = {.string="2+3"};

	// getToken_ExpectAndReturn(&expression, (Token*)two);  	//2
	// getToken_ExpectAndReturn(&expression, (Token*)Plus);		//+
	// getToken_ExpectAndReturn(&expression, (Token*)three);		//3
	// getToken_ExpectAndReturn(&expression, NULL);	

	// Result = evaluate(&expression);
	// TEST_ASSERT_EQUAL(5, Result);
// }

// void test_evaluate_given_token_2_plus_3_Mutiple_5_plus_6_get_the_correct_result(void)
// {
	// int Result;
	// Number *two   = numberNew(2);
	// Number *three = numberNew(3);
	// Number *five  = numberNew(5);
	// Number *six   = numberNew(6);
	// Operator *Plus1 = operatorNewByName("+");
	// Operator *Plus2 = operatorNewByName("+");
	// Operator *Multi	= operatorNewByName("*");
	// String expression = {.string="2+3*5+6"};
   
	// getToken_ExpectAndReturn(&expression, (Token*)two);	//2
	// getToken_ExpectAndReturn(&expression, (Token*)Plus1);	//+
	// getToken_ExpectAndReturn(&expression, (Token*)three);	//3
	// getToken_ExpectAndReturn(&expression, (Token*)Multi);	//*	
	// getToken_ExpectAndReturn(&expression, (Token*)five);	//5
	// getToken_ExpectAndReturn(&expression, (Token*)Plus2);	//+
	// getToken_ExpectAndReturn(&expression, (Token*)six);	//6
	// getToken_ExpectAndReturn(&expression, NULL);	

	// Result = evaluate(&expression);
	// TEST_ASSERT_EQUAL( 2+3*5+6 , Result);
// }

// void test_evaluate_given_token_2_plus_3_Mutiple_5_or_26_should_get_the_correct_result(void)
// {
	// int Result;
	// Number *two = numberNew(2);
	// Number *three = numberNew(3);
	// Number *five = numberNew(5);
	// Number *twentySix = numberNew(26);
	// Operator *plus = operatorNewByName("+");
	// Operator *or = operatorNewByName("|");
	// Operator *multi = operatorNewByName("*");
	// String expression = {.string="2+3*5|26"};
  
	// tokenDump((Token*) or);
  
	// printf("Start\n");
	// getToken_ExpectAndReturn(&expression, (Token*)two);	//2
	// getToken_ExpectAndReturn(&expression, (Token*)plus);	//+
	// getToken_ExpectAndReturn(&expression, (Token*)three);	//3
	// getToken_ExpectAndReturn(&expression, (Token*)multi);	//*	
	// getToken_ExpectAndReturn(&expression, (Token*)five);	//5
	// getToken_ExpectAndReturn(&expression, (Token*)or);	//|
	// getToken_ExpectAndReturn(&expression, (Token*)twentySix);	//26
	// getToken_ExpectAndReturn(&expression, NULL);	
	// printf("end\n");

	// Result = evaluate(&expression);
	// TEST_ASSERT_EQUAL(2+3*5|26 , Result);
// }

// void test_evaluate_given_an_expression_negative_2_plus_3_should_return_1(void)
// {
	// int result;
	// String expression = {.string = "-2+3"};
	// Number *two = numberNew(2);
	// Number *three = numberNew(3);
	
	// Operator *minus = operatorNewByName("-");
	// Operator *add = operatorNewByName("+");
	

	// getToken_ExpectAndReturn(&expression, (Token *)minus);
	// getToken_ExpectAndReturn(&expression, (Token *)two);
	// getToken_ExpectAndReturn(&expression, (Token *)add);
	// getToken_ExpectAndReturn(&expression, (Token *)three);
	// getToken_ExpectAndReturn(&expression, NULL);

	// result = evaluate(&expression);
	// TEST_ASSERT_EQUAL(1, result);
// }

// void test_evaluate_given_minus_minus_2_should_return_2(void){
  // int result;
  // String expression = {.string = "--2"};
  // Number *two = numberNew(2);
  
  // Operator *firstMinus = operatorNewByName("-");
  // Operator *secondMinus = operatorNewByName("-");
  
  // getToken_ExpectAndReturn(&expression, (Token *)firstMinus);
  // getToken_ExpectAndReturn(&expression, (Token *)secondMinus);
  // getToken_ExpectAndReturn(&expression, (Token *)two);
  
  // printf("start\n");
  // result = evaluate(&expression);
  // printf("end\n");
  // printf("result: %d\n", result);
// }
/*
// test 2 whether can push into dataStack
void test_evaluatePrefixesAndNumber_given_integer_two_should_be_able_to_push_into_dataStack(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "2"};
  Number *two = numberNew(2);
  Number *result;
  
  getToken_ExpectAndReturn(&expression, (Token *)two);
  getToken_ExpectAndReturn(&expression, NULL);
  
  evaluatePrefixesAndNumber(&expression, dataStack, operatorStack);
  result = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(2, result->value);
  
  stackDel(dataStack);
  stackDel(operatorStack);
}

// test -2 whether can push into dataStack and operatorStack 
void test_evaluatePrefixesAndNumber_given_minus_and_integer_two_should_be_able_to_push_into_dataStack_and_operatorStack(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "-2"};
  Operator *minus = operatorNewByName("-");
  Number *two = numberNew(2);
  Number *dataResult;
  Operator *operatorResult;
  
  getToken_ExpectAndReturn(&expression, (Token *)minus);
  getToken_ExpectAndReturn(&expression, (Token *)two);
  getToken_ExpectAndReturn(&expression, NULL);
  
  evaluatePrefixesAndNumber(&expression, dataStack, operatorStack);
  dataResult = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(2, dataResult->value);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("-", operatorResult->info->name);
  
  stackDel(dataStack);
  stackDel(operatorStack);
}

// test --2 whether can push into dataStack and operatorStack
void test_evaluatePrefixesAndNumber_given_minus_minus_and_integer_two_should_be_able_to_push_into_dataStack_and_operatorStack(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "--2"};
  Operator *firstMinus = operatorNewByName("-");
  Operator *secondMinus = operatorNewByName("-");
  Number *two = numberNew(2);
  Number *dataResult;
  Operator *operatorResult;
  
  getToken_ExpectAndReturn(&expression, (Token *)firstMinus);
  getToken_ExpectAndReturn(&expression, (Token *)secondMinus);
  getToken_ExpectAndReturn(&expression, (Token *)two);
  getToken_ExpectAndReturn(&expression, NULL);
  
  evaluatePrefixesAndNumber(&expression, dataStack, operatorStack);
  dataResult = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(2, dataResult->value);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("-", operatorResult->info->name);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("-", operatorResult->info->name);
  
  stackDel(dataStack);
  stackDel(operatorStack);
}

// test -+-2 whether can push into dataStack and operatorStack
void test_evaluatePrefixesAndNumber_given_minus_plus_minus_and_integer_two_should_be_able_to_push_into_dataStack_and_operatorStack(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "-+-2"};
  Operator *firstMinus = operatorNewByName("-");
  Operator *plus = operatorNewByName("+");
  Operator *secondMinus = operatorNewByName("-");
  Number *two = numberNew(2);
  Number *dataResult;
  Operator *operatorResult;

  getToken_ExpectAndReturn(&expression, (Token *)firstMinus);
  getToken_ExpectAndReturn(&expression, (Token *)plus);
  getToken_ExpectAndReturn(&expression, (Token *)secondMinus);
  getToken_ExpectAndReturn(&expression, (Token *)two);
  getToken_ExpectAndReturn(&expression, NULL);
  
  evaluatePrefixesAndNumber(&expression, dataStack, operatorStack);
  dataResult = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(2, dataResult->value);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("-", operatorResult->info->name);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("+", operatorResult->info->name);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("-", operatorResult->info->name);
  
  stackDel(dataStack);
  stackDel(operatorStack);
}

// test (2 whether it can push into dataStack and operatorStack
void test_evaluatePrefixesAndNumber_given_open_bracket_and_integer_two_should_be_able_to_push_into_dataStack_and_operatorStack(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "(2"};
  Operator *openBracket = operatorNewByName("(");
  Number *two = numberNew(2);
  Number *dataResult;
  Operator *operatorResult;
  
  getToken_ExpectAndReturn(&expression, (Token *)openBracket);
  getToken_ExpectAndReturn(&expression, (Token *)two);
  getToken_ExpectAndReturn(&expression, NULL);
  
  evaluatePrefixesAndNumber(&expression, dataStack, operatorStack);
  dataResult = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(2, dataResult->value);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("(", operatorResult->info->name);
  
  stackDel(dataStack);
  stackDel(operatorStack);
}

// test ((2 whether it can push into dataStack and operatorStack
void test_evaluatePrefixesAndNumber_given_openBracket_openBracket_and_integer_two_should_be_able_to_push_into_dataStack_and_operatorStack(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "((2"};
  Operator *firstOpenBracket = operatorNewByName("(");
  Operator *secondOpenBracket = operatorNewByName("(");
  Number *two = numberNew(2);
  Number *dataResult;
  Operator *operatorResult;
  
  getToken_ExpectAndReturn(&expression, (Token *)firstOpenBracket);
  getToken_ExpectAndReturn(&expression, (Token *)secondOpenBracket);
  getToken_ExpectAndReturn(&expression, (Token *)two);
  getToken_ExpectAndReturn(&expression, NULL);
  
  evaluatePrefixesAndNumber(&expression, dataStack, operatorStack);
  dataResult = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(2, dataResult->value);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("(", operatorResult->info->name);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("(", operatorResult->info->name);
  
  stackDel(dataStack);
  stackDel(operatorStack);
}

// test *2 should catch the error due to * is not in the secondaryOperatorTable
void test_evaluatePrefixesAndNumber_given_multiply_and_integer_two_should_produce_an_exception_ERR_NOT_PREFIX_OPERATOR(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "*2"};
  Operator *multiply = operatorNewByName("*");
  Number *two = numberNew(2);
  CEXCEPTION_T err;
  
  Try {
    getToken_ExpectAndReturn(&expression, (Token *)multiply);
    evaluatePrefixesAndNumber(&expression, dataStack, operatorStack);
    getToken_ExpectAndReturn(&expression, (Token *)two);
    getToken_ExpectAndReturn(&expression, NULL);
    TEST_FAIL_MESSAGE("Should throw an exception due to ERR_NOT_PREFIX_OPERATOR");
  } Catch(err) {
      TEST_ASSERT_EQUAL_MESSAGE(ERR_NOT_PREFIX_OPERATOR, err, "Expected ERR_NOT_PREFIX_OPERATOR");
    }
    
  stackDel(dataStack);
  stackDel(operatorStack);
}

// test - should catch the error due to it don't have number token in the dataStack
void test_evaluatePrefixesAndNumber_given_minus_should_produce_an_exception_ERR_NO_NUMBER(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);
  String expression = {.string = "-"};
  Operator *minus = operatorNewByName("-");
  CEXCEPTION_T err;
  
  Try {
    getToken_ExpectAndReturn(&expression, (Token *)minus);
    getToken_ExpectAndReturn(&expression, NULL);
    evaluatePrefixesAndNumber(&expression, dataStack, operatorStack);
    TEST_FAIL_MESSAGE("Should thrown an exception due to ERR_NO_NUMBER");
  } Catch(err) {
      TEST_ASSERT_EQUAL_MESSAGE(ERR_NO_NUMBER, err, "Expected ERR_NO_NUMBER");
    }
    
  stackDel(dataStack);
  stackDel(operatorStack);
}
*/
/*
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
*/ 
// test given number 2 should be able to pop out integer 2 from the dataStack
void test_evaluatePrefixesAndNumber_given_integer_two_should_be_able_to_pop_out_integer_two_from_dataStack(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);  
  String expression = {.string = "2"};
  Number *two = numberNew(2);
  Number *dataResult;
  
  getToken_ExpectAndReturn(&expression, NULL);
  
  evaluatePrefixesAndNumber((Token *)two, &expression, dataStack, operatorStack);
  dataResult = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(2, dataResult->value);
  
  stackDel(dataStack);
  stackDel(operatorStack);
}

// test given multiply operator should throw an error due to ERR_NOT_PREFIX_OPERATOR
void test_evaluatePrefixesAndNumber_given_operator_multiply_should_throw_an_error(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);  
  String expression = {.string = "*2"};  
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

// test given minus and integer two should be able to push into dataStack and operatorStack
void test_evaluatePrefixesAndNumber_given_minus_and_integer_two_should_be_able_push_into_dataStack_and_operatorStack(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);  
  String expression = {.string = "-2"};  
  Operator *minus = operatorNewByName("-");  
  Number *two = numberNew(2);
  Number *dataResult;
  Operator *operatorResult;
  
  getToken_ExpectAndReturn(&expression, (Token *)two);
  getToken_ExpectAndReturn(&expression, NULL);
  
  evaluatePrefixesAndNumber((Token *)minus, &expression, dataStack, operatorStack);
  dataResult = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(2, dataResult->value);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("-", operatorResult->info->name);
  
  stackDel(dataStack);
  stackDel(operatorStack);
}

// test given minus minus and integer two should be able to push into dataStack and operatorStack
void test_evaluatePrefixesAndNumber_given_minus_minus_and_integer_two_should_be_able_to_push_into_dataStack_and_operatorStack(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);  
  String expression = {.string = "--2"};  
  Operator *firstMinus = operatorNewByName("-");  
  Operator *secondMinus = operatorNewByName("-");  
  Number *two = numberNew(2);
  Number *dataResult;
  Operator *operatorResult;
  
  getToken_ExpectAndReturn(&expression, (Token *)secondMinus);
  getToken_ExpectAndReturn(&expression, (Token *)two);
  getToken_ExpectAndReturn(&expression, NULL);
  
  evaluatePrefixesAndNumber((Token *)firstMinus, &expression, dataStack, operatorStack);
  dataResult = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(2, dataResult->value);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("-", operatorResult->info->name);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("-", operatorResult->info->name);

  stackDel(dataStack);
  stackDel(operatorStack);
}

// test given minus plus minus and integer two should be able to push into dataStack and operatorStack
void test_evaluatePrefixesAndNumber_given_minus_plus_minus_and_integer_two_should_be_able_to_push_into_dataStack_and_operatorStack(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);  
  String expression = {.string = "-+-2"};  
  Operator *firstMinus = operatorNewByName("-");  
  Operator *plus = operatorNewByName("+");
  Operator *secondMinus = operatorNewByName("-");  
  Number *two = numberNew(2);
  Number *dataResult;
  Operator *operatorResult;
  
  getToken_ExpectAndReturn(&expression, (Token *)plus);
  getToken_ExpectAndReturn(&expression, (Token *)secondMinus);
  getToken_ExpectAndReturn(&expression, (Token *)two);
  getToken_ExpectAndReturn(&expression, NULL);
 
  evaluatePrefixesAndNumber((Token *)firstMinus, &expression, dataStack, operatorStack);
  dataResult = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(2, dataResult->value);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("-", operatorResult->info->name);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("+", operatorResult->info->name);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("-", operatorResult->info->name);

  stackDel(dataStack);
  stackDel(operatorStack);
} 

// test given open bracket and integer two should be able to push into dataStack and operatorStack
void test_evaluatePrefixesAndNumber_given_openBracket_and_integer_two_should_be_able_to_push_into_dataStack_and_operatorStack(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);  
  String expression = {.string = "(2"};  
  Operator *openBracket = operatorNewByName("(");   
  Number *two = numberNew(2);
  Number *dataResult;
  Operator *operatorResult;
  
  getToken_ExpectAndReturn(&expression, (Token *)two);
  getToken_ExpectAndReturn(&expression, NULL);
  
  evaluatePrefixesAndNumber((Token *)openBracket, &expression, dataStack, operatorStack);
  dataResult = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(2, dataResult->value);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("(", operatorResult->info->name);
  
  stackDel(dataStack);
  stackDel(operatorStack);
}

// test given openBracket openBracket and integer two should be able to push into dataStack and operatorStack
void test_evaluatePrefixesAndNumber_given_openBracket_openBracket_and_integer_two_should_be_able_to_push_into_dataStack_and_operatorStack(void) {
  Stack *dataStack     = stackNew(100);
	Stack *operatorStack = stackNew(100);  
  String expression = {.string = "(2"};  
  Operator *firstOpenBracket = operatorNewByName("(");   
  Operator *secondOpenBracket = operatorNewByName("(");   
  Number *two = numberNew(2);
  Number *dataResult;
  Operator *operatorResult;
  
  getToken_ExpectAndReturn(&expression, (Token *)secondOpenBracket);
  getToken_ExpectAndReturn(&expression, (Token *)two);
  getToken_ExpectAndReturn(&expression, NULL);
  
  evaluatePrefixesAndNumber((Token *)firstOpenBracket, &expression, dataStack, operatorStack);
  dataResult = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(2, dataResult->value);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("(", operatorResult->info->name);
  operatorResult = (Operator *)stackPop(operatorStack);
  TEST_ASSERT_EQUAL_STRING("(", operatorResult->info->name);
  
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

// test evaluate given integer 2 should be able to push into dataStack
