#include "unity.h"
#include "Operator.h"
#include <stdio.h>
#include "Stack.h"
#include "Token.h"
#include "NumberToken.h"
#include "OperatorToken.h"	
#include "TokenDebug.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}

void tearDown(void){}



void test_OperatorByID_should_print_out_ADD_OP_details_due_to_ADD_OP_parameter_is_passed_in(void)
{
	OperatorInfo *info = getOperatorByID(ADD_OP);
	TEST_ASSERT_NOT_NULL(info);
	TEST_ASSERT_EQUAL(ADD_OP, info->id);	
}

void test_OperatorByID_should_print_out_DIV_OP_details_due_to_DIV_OP_parameter_is_passed_in(void)
{
	OperatorInfo *info = getOperatorByID(DIV_OP);
	TEST_ASSERT_NOT_NULL(info);
	TEST_ASSERT_EQUAL(DIV_OP, info->id);	
	
}

void test_OperatorByID_should_print_out_BITWISE_OR_OP_details_due_to_BITWISE_OR_OP_parameter_is_passed_in(void)
{
	OperatorInfo *info = getOperatorByID(OR_OP);
	TEST_ASSERT_NOT_NULL(info);
	TEST_ASSERT_EQUAL(OR_OP, info->id);	
}

void test_OperatorByID_should_not_print_out_due_to_the_operator_is_not_in_the_table(void)
{
	OperatorInfo *info = getOperatorByID(UNKNOWN_OP);
	TEST_ASSERT_NULL(info);
}

void test_OperatorByName_should_print_out_ADD_OP_details_due_to_ADD_OP_parameter_is_passed_in(void)
{
	OperatorInfo *info = getOperatorByName("+");
	TEST_ASSERT_NOT_NULL(info);
	TEST_ASSERT_EQUAL_STRING("+", info->name);	
}

void test_OperatorByName_should_print_out_DIV_OP_details_due_to_DIV_OP_parameter_is_passed_in(void)
{
	OperatorInfo *info = getOperatorByName("/");
	TEST_ASSERT_NOT_NULL(info);
	TEST_ASSERT_EQUAL_STRING("/", info->name);	
}

void test_OperatorByName_should_print_out_BITWISE_OR_OP_details_due_to_BITWISE_OR_OP_parameter_is_passed_in(void)
{
	OperatorInfo *info = getOperatorByName("||");
	TEST_ASSERT_NOT_NULL(info);
	TEST_ASSERT_EQUAL_STRING("||", info->name);	
}

void test_OperatorByName_should_not_print_out_UNKNOWN_OP_details_due_to_UNKNOWN_OP_parameter_is_passed_in(void)
{
	OperatorInfo *info = getOperatorByName("asd");
	TEST_ASSERT_NULL(info);
}

void test_getInfixValues_after_integer_1_and_2_is_pushed_should_display_out_1_and_2(void)
{
	Stack *dataStack = stackNew(10);
	int valueA, valueB;
	
	Number *value1 = numberNew(1);
	Number *value2 = numberNew(2);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	getInfixValues(&valueA, &valueB, dataStack);
	TEST_ASSERT_EQUAL(1, valueA);
	TEST_ASSERT_EQUAL(2, valueB);
	
	stackDel(dataStack);
}

void test_getInfixValues_after_push_an_operator_type_should_throw_an_exception(void)
{
	Stack *dataStack = stackNew(10);
	int valueA, valueB;
	Operator *operator;
	operator = operatorNewByID(ADD_OP);
	CEXCEPTION_T err;
	
	Try
	{
		stackPush(dataStack, operator);
		getInfixValues(&valueA, &valueB, dataStack);
		TEST_FAIL_MESSAGE("Should have throw an exception due to it is not a number token!");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_NOT_NUMBER_TOKEN, err, "Expect ERR_NOT_NUMBER_TOKEN exception");
	}
	stackDel(dataStack);
}

void test_getInfixValues_will_throw_an_exception_if_the_first_or_second_popResult_is_NULL(void)
{
	Stack *dataStack = stackNew(10);
	int valueA, valueB;
	Number *value1 = numberNew(1);
	CEXCEPTION_T err;
	
	Try
	{
		stackPush(dataStack, value1);
		getInfixValues(&valueA, &valueB, dataStack);
		TEST_FAIL_MESSAGE("Should have throw an exception due to incomplete number");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_INCOMPLETE_NUMBER, err, "Expect ERR_INCOMPLETE_NUMBER exception");
	}
	stackDel(dataStack);
}

void test_getInfixValues_will_throw_an_exception_if_nothing_is_pushed_into_the_dataStack(void)
{
	Stack *dataStack = stackNew(10);
	int valueA, valueB;
	Number *value1 = numberNew(1);
	CEXCEPTION_T err;
	
	Try
	{
		getInfixValues(&valueA, &valueB, dataStack);
		TEST_FAIL_MESSAGE("Should have throw an exception due to incomplete number");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_INCOMPLETE_NUMBER, err, "Expect ERR_INCOMPLETE_NUMBER exception");
	}
	stackDel(dataStack);
}

void test_pushNewNumber_after_getInfixValues_is_called_whether_2_plus_3_will_give_us_the_result_5(void)
{
	Stack *dataStack = stackNew(10);
	int valueA, valueB;
	Number *result;
	Number *value1 = numberNew(2);
	Number *value2 = numberNew(3);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	getInfixValues(&valueA, &valueB, dataStack);
	pushNewNumber(valueA + valueB, dataStack);
	
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(5, result->value);
	stackDel(dataStack);
}

void test_executeAdd_after_push_an_operator_type_should_throw_an_exception(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Operator *operator;
	operator = operatorNewByID(ADD_OP);
	CEXCEPTION_T err;
	
	Try
	{
		stackPush(dataStack, operator);
		executeAdd(dataStack, operatorStack);
		TEST_FAIL_MESSAGE("Should have throw an exception due to it is not a number token!");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_NOT_NUMBER_TOKEN, err, "Expect ERR_NOT_NUMBER_TOKEN exception");
	}
	stackDel(dataStack);
}

void test_executeAdd_will_throw_an_exception_if_the_first_or_second_popResult_is_NULL(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *value1 = numberNew(1);
	CEXCEPTION_T err;
	
	Try
	{
		stackPush(dataStack, value1);
		executeAdd(dataStack, operatorStack);
		TEST_FAIL_MESSAGE("Should have throw an exception due to incomplete number");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_INCOMPLETE_NUMBER, err, "Expect ERR_INCOMPLETE_NUMBER exception");
	}
	stackDel(dataStack);
}

void test_executeAdd_will_throw_an_exception_if_nothing_is_pushed_into_the_dataStack(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *value1 = numberNew(1);
	CEXCEPTION_T err;
	
	Try
	{
		executeAdd(dataStack, operatorStack);
		TEST_FAIL_MESSAGE("Should have throw an exception due to incomplete number");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_INCOMPLETE_NUMBER, err, "Expect ERR_INCOMPLETE_NUMBER exception");
	}
	stackDel(dataStack);
}

void test_executeAdd_after_push_the_value_4_and_5_it_should_pop_out_the_result_9(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(4);
	Number *value2 = numberNew(5);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeAdd(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(9, result->value);
	stackDel(dataStack);
}

void test_executeSub_after_integer_5_and_4_processed_it_should_return_1(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(5);
	Number *value2 = numberNew(4);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeSub(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(1, result->value);
	stackDel(dataStack);
}

void test_executeMul_after_integer_2_and_1_is_processed_it_should_return_2(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(2);
	Number *value2 = numberNew(1);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeMul(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(2, result->value);
	stackDel(dataStack);
}

void test_executeModulo_after_integer_1_and_2_is_processed_it_should_return_the_remainder_1(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(1);
	Number *value2 = numberNew(2);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeModulo(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(1, result->value);
	stackDel(dataStack);
}

void test_executeDiv_after_integer_2_and_2_is_processed_it_should_return_1(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(2);
	Number *value2 = numberNew(2);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeDiv(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(1, result->value);
	stackDel(dataStack);
}

void test_executeOr_after_integer_1_and_0_is_processed_it_should_return_1(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(1);
	Number *value2 = numberNew(0);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeOr(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(1, result->value);
	stackDel(dataStack);
}

void test_executeOr_after_integer_0_and_0_is_processed_it_should_return_0(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(0);
	Number *value2 = numberNew(0);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeOr(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(0, result->value);
	stackDel(dataStack);
}

void test_executeXor_after_integer_2_and_5_is_processed_it_should_return_7(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(2);
	Number *value2 = numberNew(5);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeXor(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(7, result->value);
	stackDel(dataStack);
}

void test_executeAnd_after_integer_1_and_0_is_processed_it_should_return_0(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(1);
	Number *value2 = numberNew(0);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeAnd(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(0, result->value);
	stackDel(dataStack);
}

void test_executeAnd_after_integer_1_and_1_is_processed_it_should_return_1(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(1);
	Number *value2 = numberNew(1);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeAnd(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(1, result->value);
	stackDel(dataStack);
}

void test_executeBitAnd_after_integer_2_and_3_is_processed_it_should_return_2(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(2);
	Number *value2 = numberNew(3);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeBitAnd(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(2, result->value);
	stackDel(dataStack);
}

void test_executeBitOr_after_integer_14_and_1_is_processed_it_should_return_15(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(14);
	Number *value2 = numberNew(1);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeBitOr(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(15, result->value);
	stackDel(dataStack);
}

void test_executeShiftLeft_after_integer_7_and_1_is_processed_it_should_return_14(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(7);
	Number *value2 = numberNew(1);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeShiftLeft(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(14, result->value);
	stackDel(dataStack);
}

void test_executeShiftLeft_after_integer_1_and_4_is_processed_it_should_return_16(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(1);
	Number *value2 = numberNew(4);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeShiftLeft(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(16, result->value);
	stackDel(dataStack);
}

void test_executeShiftRight_after_integer_4_and_1_is_processed_it_should_return_2(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(4);
	Number *value2 = numberNew(1);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeShiftRight(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(2, result->value);
	stackDel(dataStack);
}

void test_executeShiftRight_after_integer_1_and_1_is_processed_it_should_return_0(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(1);
	Number *value2 = numberNew(1);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeShiftRight(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(0, result->value);
	stackDel(dataStack);
}

void test_executeLesser_after_integer_1_and_3_is_processed_it_should_return_1(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(1);
	Number *value2 = numberNew(3);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeLesser(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(1, result->value);
	stackDel(dataStack);
}

void test_executeLesser_after_integer_3_and_1_is_processed_it_should_return_0(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(3);
	Number *value2 = numberNew(1);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeLesser(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(0, result->value);
	stackDel(dataStack);
} 

void test_executeGreater_after_integer_5_and_2_is_processed_it_should_return_1(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(5);
	Number *value2 = numberNew(2);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeGreater(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(1, result->value);
	stackDel(dataStack);
} 

void test_executeGreater_after_integer_2_and_5_is_processed_it_should_return_0(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(2);
	Number *value2 = numberNew(5);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeGreater(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(0, result->value);
	stackDel(dataStack);
} 

void test_executeEqual_after_integer_1_and_1_is_processed_it_should_return_1(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(1);
	Number *value2 = numberNew(1);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeEqual(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(1, result->value);
	stackDel(dataStack);
} 

void test_executeEqual_after_integer_2_and_1_is_processed_it_should_return_0(void)
{
	Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *value1 = numberNew(2);
	Number *value2 = numberNew(1);
	
	stackPush(dataStack, value1);
	stackPush(dataStack, value2);
	
	executeEqual(dataStack, operatorStack);
	result = (Number *)stackPop(dataStack);
	TEST_ASSERT_EQUAL(0, result->value);
	stackDel(dataStack);
} 


void test_executeClosingBracket_given_bracket_2_bracket_should_get_result_of_2(void){

  Stack *dataStack = stackNew(10);
  Stack *operatorStack = stackNew(100);
	Number *result;
	Number *two = numberNew(2);
  Operator *openBracket	 = operatorNewByName("(");
	Operator *closeBracket = operatorNewByName(")");
 
  //(2)
  stackPush(operatorStack,openBracket);
	stackPush(operatorStack,closeBracket);
  stackPush(dataStack, two);
  
  executeClosingBracket( dataStack, operatorStack);
  result = (Number *)stackPop(dataStack);
  TEST_ASSERT_EQUAL(2, result->value);
	stackDel(dataStack);
   
}

void test_executeClosingBracket_given_empty_operatorStack_should_throw_exception(void){

  CEXCEPTION_T err;
  Stack *dataStack     = stackNew(10);
  Stack *operatorStack = stackNew(100);
  Number *two          = numberNew(2);
	
 
  Try{  //2
        stackPush(dataStack, two);;
        executeClosingBracket( dataStack, operatorStack);
        TEST_FAIL_MESSAGE("should throw ERR_NO_BRACKET exception");
   } Catch(err)
      { TEST_ASSERT_EQUAL_MESSAGE( ERR_NO_BRACKET , err , "Expected ERR_NO_BRACKET exception"); }
}

void test_executeClosingBracket_given_no_closing_bracket_should_throw_exception(void){

  CEXCEPTION_T err;
  Stack *dataStack     = stackNew(10);
  Stack *operatorStack = stackNew(100);
  Number *two          = numberNew(2);
  Operator *openBracket= operatorNewByName("(");
	
 
  Try{ //(2
      stackPush(operatorStack,openBracket);
      stackPush(dataStack, two);
      executeClosingBracket( dataStack, operatorStack);
      TEST_FAIL_MESSAGE("should throw ERR_NO_BRACKET exception");
  } Catch(err)
      { TEST_ASSERT_EQUAL_MESSAGE( ERR_NO_BRACKET , err , "Expected ERR_NO_BRACKET exception"); }
 
}

void test_executeClosingBracket_given_no_OPEN_bracket_should_throw_exception(void){

  CEXCEPTION_T err;
  Stack *dataStack     = stackNew(10);
  Stack *operatorStack = stackNew(100);
  Number *two          = numberNew(2);
  Operator *closeBracket= operatorNewByName(")");
	
 
  Try{ //2)
      stackPush(operatorStack,closeBracket);
      stackPush(dataStack, two);
      executeClosingBracket( dataStack, operatorStack);
      TEST_FAIL_MESSAGE("should throw ERR_NO_BRACKET exception");
  } Catch(err)
      { TEST_ASSERT_EQUAL_MESSAGE( ERR_NO_BRACKET , err , "Expected ERR_NO_BRACKET exception"); }
 
}

void test_executeClosingBracket_given_empty_dataStack_should_throw_exception(void){

  CEXCEPTION_T err;
  Stack *dataStack     = stackNew(10);
  Stack *operatorStack = stackNew(100);
  Operator *openBracket = operatorNewByName("(");
  Operator *CloseBracket= operatorNewByName(")");
	
 
  Try{  //()
        stackPush(operatorStack,openBracket);
        stackPush(operatorStack,CloseBracket);
        executeClosingBracket( dataStack, operatorStack);
        TEST_FAIL_MESSAGE("should throw ERR_STACK_EMPTY exception");
   } Catch(err)
      { TEST_ASSERT_EQUAL_MESSAGE( ERR_STACK_EMPTY , err , "Expected ERR_STACK_EMPTY exception"); }
}





