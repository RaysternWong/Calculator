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
	OperatorInfo *info = getOperatorByIDInSecondaryTable(ADD_OP);
	TEST_ASSERT_NOT_NULL(info);
	TEST_ASSERT_EQUAL(ADD_OP, info->id);
	TEST_ASSERT_EQUAL(90, info->precedence);
}

void test_getOperatorByIDInSecondaryTable_after_UNKNOWN_OP_is_passed_in_it_should_return_NULL(void)
{
	OperatorInfo *info = getOperatorByIDInSecondaryTable(UNKNOWN_OP);
	TEST_ASSERT_NULL(info);
}

void test_getOperatorByNameInSecondaryTable_after_plus_is_passed_in_it_should_return_back_the_info_of_it(void)
{
	OperatorInfo *info = getOperatorByNameInSecondaryTable("+");
	TEST_ASSERT_NOT_NULL(info);
	TEST_ASSERT_EQUAL_STRING("+", info->name);
	TEST_ASSERT_EQUAL(90, info->precedence);
}

void test_getOperatorByNameInSecondaryTable_after_unknown_string_is_passed_in_it_should_return_back_NULL(void)
{
	OperatorInfo *info = getOperatorByNameInSecondaryTable("asd");
	TEST_ASSERT_NULL(info);
}

void test_operatorTryConvertToPrefix_will_convert_the_SUB_OP_to_prefix(void)
{
	OperatorInfo *info = getOperatorByID(SUB_OP);
	Operator subOp = {.type = OPERATOR_TOKEN, info};
	operatorTryConvertToPrefix(&subOp);
	TEST_ASSERT_NOT_NULL(&subOp);
	TEST_ASSERT_EQUAL(SUB_OP, subOp.info->id);
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