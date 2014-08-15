#include "unity.h"
#include "mock_Token.h"
#include "OperatorToken.h"
#include "StringObject.h"
#include "NumberToken.h"
#include "ErrorCode.h"
#include "Operator.h"
#include "Stack.h"
#include "TokenDebug.h"
#include "CException.h"

void setUp(void){}

void tearDown(void){}

void test_getOperatorByIDInSecondaryTable_after_ADD_OP_is_passed_in_it_should_return_back_the_info_of_it(void)
{
	OperatorInfo *info = getOperatorByIDInSecondaryTable(PLUS_OP);
	TEST_ASSERT_NOT_NULL(info);
	TEST_ASSERT_EQUAL(PLUS_OP, info->id);
	TEST_ASSERT_EQUAL(90, info->precedence);
  TEST_ASSERT_EQUAL_STRING("+", info->name);
}

void test_getOperatorByIDInSecondaryTable_after_UNKNOWN_OP_is_passed_in_it_should_return_NULL(void)
{
	OperatorInfo *info = NULL;
  info = getOperatorByIDInSecondaryTable(UNKNOWN_OP);
	TEST_ASSERT_NULL(info);
}

void test_getOperatorByNameInSecondaryTable_after_plus_is_passed_in_it_should_return_back_the_info_of_it(void)
{
	OperatorInfo *info = getOperatorByNameInSecondaryTable("-");
	TEST_ASSERT_NOT_NULL(info);
	TEST_ASSERT_EQUAL_STRING("-", info->name);
	TEST_ASSERT_EQUAL(90, info->precedence);
  TEST_ASSERT_EQUAL(MINUS_OP, info->id);
}

void test_getOperatorByNameInSecondaryTable_after_unknown_string_is_passed_in_it_should_return_back_NULL(void)
{
	OperatorInfo *info = NULL;
  info = getOperatorByNameInSecondaryTable("asd");
	TEST_ASSERT_NULL(info);
}

void test_operatorTryConvertToPrefix_will_convert_the_SUB_OP_to_prefix(void)
{
	OperatorInfo *info = getOperatorByID(SUB_OP);
	Operator subOp = {.type = OPERATOR_TOKEN, info};
	operatorTryConvertToPrefix(&subOp);
	TEST_ASSERT_NOT_NULL(&subOp);
	TEST_ASSERT_EQUAL(MINUS_OP, subOp.info->id);
	TEST_ASSERT_EQUAL(90, subOp.info->precedence);
}

void test_operatorTryConvertToPrefix_will_throw_an_exception_due_to_the_operator_is_not_in_the_table(void)
{
	OperatorInfo *info = getOperatorByID(DIV_OP);
	Operator divOp = {.type = OPERATOR_TOKEN, info};
	CEXCEPTION_T err;
	
	Try
	{
		operatorTryConvertToPrefix(&divOp);
		TEST_FAIL_MESSAGE("Should throw an exception due to ERR_NOT_PREFIX_OPERATOR");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_NOT_PREFIX_OPERATOR, err, "Expected ERR_NOT_PREFIX_OPERATOR exception");
    TEST_ASSERT_NOT_NULL(&divOp);
	}
}

/*#1
 * Test create new operator token identify by the operator ID, given plus operator ID ADD_OP
 * operator->info shouldn't be NULL and operator->info should contain operator information
 */
void test_operatorNewByID_given_operator_ID_ADD_OP_should_store_operator_info_inside_operatorNewByID(void)
{
	Operator *operator;
	operator = operatorNewByID(ADD_OP);
	
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN , operator->type);
	TEST_ASSERT_NOT_NULL(operator);
	TEST_ASSERT_NOT_NULL(operator->info);
	TEST_ASSERT_EQUAL(ADD_OP , operator->info->id);
	operatorDel(operator);
}

/*#2
 * Given UNKNOWN OPERATOR ID and should throw an exception error
 */
void test_operatorNewByID_given_operator_ID_UNKNOWN_OP_should_Throw_Exception(void)
{
	CEXCEPTION_T err;
	Operator *operator = NULL;
	
	Try
	{
		operator = operatorNewByID(UNKNOWN_OP);
		TEST_FAIL_MESSAGE("Should throw ERR_UNKNOWN_OPERATOR exception");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_UNKNOWN_OPERATOR , err , "Expect ERR_UNKNOWN_OPERATOR exception");
		TEST_ASSERT_NULL(operator);
	}
	
	operatorDel(operator);
}

/*#3
 * Test create new operator token identify by the operator name, given operator name "*"
 * operator->info shouldn't be NULL and operator->info should contain operator information
 */
void test_operatorNewByName_given_multiply_operator_name_should_store_multiply_operator_info(void)
{
	Operator *operator;
	operator = operatorNewByName("*");
	
	TEST_ASSERT_NOT_NULL(operator);
	TEST_ASSERT_NOT_NULL(operator->info);
	TEST_ASSERT_EQUAL_STRING("*" , operator->info->name);
	TEST_ASSERT_EQUAL(MUL_OP , operator->info->id);
	TEST_ASSERT_EQUAL(80 , operator->info->precedence);
	operatorDel(operator);
}

/*#4
 * Test create new operator token identify by the operator name, given operator name "-"
 * operator->info shouldn't be NULL and operator->info should contain operator information
 */
void test_operatorNewByName_given_minus_operator_name_should_store_minus_operator_info(void)
{
	Operator *operator;
	operator = operatorNewByName("-");
	TEST_ASSERT_NOT_NULL(operator);
  TEST_ASSERT_NOT_NULL(operator->info);
	TEST_ASSERT_EQUAL_STRING("-" , operator->info->name);
	TEST_ASSERT_EQUAL(SUB_OP , operator->info->id);
	TEST_ASSERT_EQUAL(70 , operator->info->precedence);
	operatorDel(operator);
}

/*#5
 * Given "[" operator should throw an exception 
 * because this operator not contain in primary operator table
 */ 
void test_operatorNewByName_given_square_bracket_name_should_store_nothing(void)
{
	CEXCEPTION_T err;
	Operator *operator = NULL;	

	Try
	{
		operator = operatorNewByName("[");
		TEST_FAIL_MESSAGE("Should throw ERR_UNKNOWN_OPERATOR exception");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_UNKNOWN_OPERATOR , err , "Expect ERR_UNKNOWN_OPERATOR exception");
    TEST_ASSERT_NULL(operator);
 	}
	
	operatorDel(operator);
}

void test_operatorNewByName_given_curly_bracket_name_should_store_nothing(void)
{
	CEXCEPTION_T err;
	Operator *operator = NULL;
	
	Try
	{
		operator = operatorNewByName("'_'");
		TEST_FAIL_MESSAGE("Should throw ERR_UNKNOWN_OPERATOR exception");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_UNKNOWN_OPERATOR , err , "Expect ERR_UNKNOWN_OPERATOR exception");
    TEST_ASSERT_NULL(operator);
	}
	
	operatorDel(operator);
}