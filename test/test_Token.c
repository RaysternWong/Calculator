#include "unity.h"
#include "Token.h"
#include "StringObject.h"
#include "NumberToken.h"
#include "OperatorToken.h"
#include "IdentifierToken.h"
#include "Operator.h"
#include "Stack.h"
#include "TokenDebug.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/* 
 * Given "  2  " make this integer 2 become number token
 */
void test_getToken_given_2_should_get_2_and_pass_to_number_token(void)
{
	String *str = stringNew("  2  ");
	Number *num = (Number*)getToken(str);

	TEST_ASSERT_NOT_NULL(num);
	TEST_ASSERT_EQUAL(NUMBER_TOKEN , num->type);
	TEST_ASSERT_EQUAL(2 , num->value);
	
	numberDel(num);
	stringDel(str);
}

/* 
 * Given "\t 841  " make this integer 841 become number token
 */
void test_getToken_given_tab_841_should_get_841_and_pass_to_number_token(void)
{
	String *str = stringNew("\t 841  ");
	Number *num = (Number*)getToken(str);

	TEST_ASSERT_NOT_NULL(num);
	TEST_ASSERT_EQUAL(NUMBER_TOKEN , num->type);
	TEST_ASSERT_EQUAL(841 , num->value);	
	
	numberDel(num);
	stringDel(str);
}

/* 
 * Given "\t 23 40 \t" and getToken twice now the number token value should be 40
 */
void test_getToken_given_tab_23_40_tab_and_getToken_x2_should_get_number_token_value_40(void)
{
	String *str = stringNew("\t 23 40 \t");
	Number *num;
	num = (Number*)getToken(str);
	num = (Number*)getToken(str);

	TEST_ASSERT_NOT_NULL(num);
	TEST_ASSERT_EQUAL(NUMBER_TOKEN , num->type);	
	TEST_ASSERT_EQUAL(40 , num->value);	
	
	numberDel(num);
	stringDel(str);
}

/* 
 * Given "\t  \t" should return NULL
 */
void test_getToken_given_tab_space_tab_and_getToken_should_return_NULL(void)
{
	String *str = stringNew("\t  \t");
	Number *num = (Number*)getToken(str);

	TEST_ASSERT_NULL(num);
	
	numberDel(num);
	stringDel(str);
}

/* 
 * Given " && " should return this as an operator token 
 */
void test_getToken_given_AND_operator_in_string_should_get_AND_operator_and_return_as_an_operator_token(void)
{
	String *str = stringNew(" && ");
	Operator *op = (Operator*)getToken(str);

	TEST_ASSERT_NOT_NULL(op);
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN , op->type);
	TEST_ASSERT_EQUAL_STRING("&&" , op->info->name);
	TEST_ASSERT_EQUAL(AND_OP , op->info->id);
	
	operatorDel(op);
	stringDel(str);
}

/*
 * Given " * " should return this as an operator token 
 */
void test_getToken_given_multiply_operator_in_string_should_get_multiply_operator_and_return_as_an_operator_token(void)
{
	String *str = stringNew(" * ");
	Operator *op = (Operator*)getToken(str);

	TEST_ASSERT_NOT_NULL(op);
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN , op->type);
	TEST_ASSERT_EQUAL_STRING("*" , op->info->name);
	TEST_ASSERT_EQUAL(MUL_OP , op->info->id);
	
	operatorDel(op);
	stringDel(str);
}

/*
 * Given " + % " and call getToken x2 should return percentage (%) operator in token type 
 */
void test_getToken_given_addition_operator_and_percentage_operator_in_string_call_getToken_x2_should_get_percentage_operator_and_return_as_an_operator_token(void)
{
	String *str = stringNew(" + % ");
	Operator *op; 
	op = (Operator*)getToken(str);
	op = (Operator*)getToken(str);

	TEST_ASSERT_NOT_NULL(op);
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN , op->type);
	TEST_ASSERT_EQUAL_STRING("%" , op->info->name);
	TEST_ASSERT_EQUAL(NPERCENT_OP , op->info->id);
	
	operatorDel(op);
	stringDel(str);
}



/* 
 * Given "MAX" should return store "MAX" in identifier token
 */
void test_getToken_given_MAX_should_store_MAX_in_identifier_token(void)
{
	String *str = stringNew("MAX");
	Identifier *iden = (Identifier*)getToken(str);
	
	TEST_ASSERT_NOT_NULL(iden);
	TEST_ASSERT_EQUAL(IDENTIFIER_TOKEN , iden->type);
	TEST_ASSERT_EQUAL_STRING("MAX" , iden->name);
	
	identifierDel(iden);
	stringDel(str);
}

/* 
 * Given "_MAX_Mas2" should return store "_MAX_Mas2" in identifier token
 */
void test_getToken_given__MAX_Mas2_should_store__MAX_Mas2_in_identifier_token(void)
{
	String *str = stringNew("_MAX_Mas2");
	Identifier *iden = (Identifier*)getToken(str);
	
	TEST_ASSERT_NOT_NULL(iden);
	TEST_ASSERT_EQUAL(IDENTIFIER_TOKEN , iden->type);
	TEST_ASSERT_EQUAL_STRING("_MAX_Mas2" , iden->name);
	
	identifierDel(iden);
	stringDel(str);
}

/* 
 * Given "MAX232 + 4" should return store "MAX232 + 4" in identifier token
 */
void test_getToken_given_MAX232_plus_4_should_store_MAX232_in_identifier_token(void)
{
	String *str = stringNew("MAX232 + 4");
	Identifier *iden = (Identifier*)getToken(str);
	
	TEST_ASSERT_NOT_NULL(iden);
	TEST_ASSERT_EQUAL(IDENTIFIER_TOKEN , iden->type);
	TEST_ASSERT_EQUAL_STRING("MAX232" , iden->name);
	
	identifierDel(iden);
	stringDel(str);
}

/* 
 * Given "124 + MAX80" should return store "MAX80" in identifier token
 */
void test_getToken_given_124_plus_MAX80_should_store_MAX80_in_identifier_token(void)
{
	String *str = stringNew("124 MAX80");
	Identifier *iden;
	iden = (Identifier*)getToken(str);
	iden = (Identifier*)getToken(str);
	
	TEST_ASSERT_NOT_NULL(iden);
	TEST_ASSERT_EQUAL(IDENTIFIER_TOKEN , iden->type);
	TEST_ASSERT_EQUAL_STRING("MAX80" , iden->name);
	
	identifierDel(iden);
	stringDel(str);
}

/* 
 * Given "456_MAX" should throw exception
 */
void test_getToken_given_456_MAX_should_return_NULL(void)
{
	CEXCEPTION_T err;
	
	String *str;
	Identifier *iden = NULL;
	
	Try
	{
		str = stringNew("456_MAX");
		iden = (Identifier*)getToken(str);
		TEST_FAIL_MESSAGE("Should throw ERR_NOT_NUMBER_TOKEN exception");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_NOT_NUMBER_TOKEN , err , "Expect ERR_NOT_NUMBER_TOKEN exception");
		TEST_ASSERT_NULL(iden);
	}
	
	identifierDel(iden);
	stringDel(str);
}

/* 
 * Given "123Zye" should throw exception
 */
void test_getToken_given_123zye_should_return_NULL(void)
{
	CEXCEPTION_T err;
	
	String *str;
	Identifier *iden = NULL;
	
	Try
	{
		str = stringNew("123zye");
		iden = (Identifier*)getToken(str);
		TEST_FAIL_MESSAGE("Should throw ERR_NOT_NUMBER_TOKEN exception");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_NOT_NUMBER_TOKEN , err , "Expect ERR_NOT_NUMBER_TOKEN exception");
		TEST_ASSERT_NULL(iden);
	}
	
	identifierDel(iden);
	stringDel(str);
}
