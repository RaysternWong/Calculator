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
 * Given complicated expresison "4 + 99abc10" should able to get identifierToken
 */
void test_getToken_given_complicated_expression_should_able_to_identifierToken(void)
{
	CEXCEPTION_T err;
	String *str;
	Identifier *iden;
	
	str = stringNew(" 4 + 99abc10 ");	
	numberDel((Number*)getToken(str));
	operatorDel((Operator*)getToken(str));
	
	iden = (Identifier*)getToken(str);
	TEST_ASSERT_NOT_NULL(iden);
	TEST_ASSERT_EQUAL_STRING("99abc10" , iden->name);
	tokenDisplay((Token *)iden);

	
	identifierDel(iden);
	stringDel(str);
}

/* 
 * Given "2" 2 is a numToken , num->line should contain the location of numToken
 */
void test_getToken_given_2_should_get_2_and_pass_to_number_token(void)
{
	String *str = stringNew(" 22  ");
	Number *num = (Number*)getToken(str);

	TEST_ASSERT_NOT_NULL(num);
	TEST_ASSERT_EQUAL(NUMBER_TOKEN , num->type);
	TEST_ASSERT_EQUAL(22 , num->value);
	TEST_ASSERT_EQUAL(1 , num->line->startindex);
	TEST_ASSERT_EQUAL(2 , num->line->length);
	TEST_ASSERT_EQUAL(3 , str->startindex);
	TEST_ASSERT_EQUAL(2 , str->length);
	tokenDisplay((Token *)num);
	numberDel(num);
	
	num = (Number*)getToken(str);
	TEST_ASSERT_NULL(num);
	TEST_ASSERT_EQUAL(5 , str->startindex);
	TEST_ASSERT_EQUAL(0 , str->length);
	numberDel(num);
	
	stringDel(str);
}

/* 
 * Given " 50-4" 50 is a numToken , num->line should contain the location of numToken
 */
void test_getToken_given_50_minus_4_num_line_should_contain_the_numToken_location(void)
{
	String *str = stringNew(" 50-4");
	Number *num = (Number*)getToken(str);

	TEST_ASSERT_NOT_NULL(num);
	TEST_ASSERT_EQUAL(NUMBER_TOKEN , num->type);
	TEST_ASSERT_EQUAL(50 , num->value);
	TEST_ASSERT_EQUAL(1 , num->line->startindex);
	TEST_ASSERT_EQUAL(2 , num->line->length);
	
	numberDel(num);
	stringDel(str);
}

/* 
 * Given "_ABC" _ABC is a idenToken , iden->line should contain the location of idenToken
 */
void test_getToken_given__ABC_iden_line_should_contain_the_idenToken_location(void)
{
	String *str = stringNew("_ABC");
	Identifier *iden = (Identifier*)getToken(str);

	TEST_ASSERT_NOT_NULL(iden);
	TEST_ASSERT_EQUAL(IDENTIFIER_TOKEN , iden->type);
	TEST_ASSERT_EQUAL_STRING("_ABC" , iden->name);
	TEST_ASSERT_EQUAL(0 , iden->line->startindex);
	TEST_ASSERT_EQUAL(4 , iden->line->length);
	tokenDisplay((Token *)iden);
	
	identifierDel(iden);
	stringDel(str);
}

/* 
 * Given "+-" + is a OperatorToken , op->line should contain the location of OperatorToken
 */
void test_getToken_given_plus_minus_op_line_should_contain_the_OperatorToken_location(void)
{
	String *str = stringNew("+-");
	Operator *op;
	op = (Operator*)getToken(str);

	TEST_ASSERT_NOT_NULL(op);
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN , op->type);
	TEST_ASSERT_EQUAL(ADD_OP , op->info->id);
	TEST_ASSERT_EQUAL(0 , op->line->startindex);
	TEST_ASSERT_EQUAL(1 , op->line->length);
	operatorDel(op);
	
	op = (Operator*)getToken(str);
	TEST_ASSERT_NOT_NULL(op);
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN , op->type);
	TEST_ASSERT_EQUAL(SUB_OP , op->info->id);
	TEST_ASSERT_EQUAL(1 , op->line->startindex);
	TEST_ASSERT_EQUAL(1 , op->line->length);
	
	operatorDel(op);
	stringDel(str);
}

/* 
 * Given "---4" - is a OperatorToken and call getToken 3times, op->line should contain the location of OperatorToken
 */
void test_getToken_given_minusx3_4_op_line_should_contain_the_OperatorToken_location(void)
{
	String *str = stringNew("---4321");
	Number *num;
	operatorDel((Operator*)getToken(str));
	operatorDel((Operator*)getToken(str));
	operatorDel((Operator*)getToken(str));
	
	num = (Number*)getToken(str);
	TEST_ASSERT_NOT_NULL(num);
	TEST_ASSERT_EQUAL(NUMBER_TOKEN , num->type);
	TEST_ASSERT_EQUAL(4321 , num->value);
	TEST_ASSERT_EQUAL(3 , num->line->startindex);
	TEST_ASSERT_EQUAL(4 , num->line->length);
	tokenDisplay((Token *)num);
	
	numberDel(num);
	stringDel(str);
}

/* 
 * Given "4 &&  " and getToken 2times
 * should get numToken 4 and operatorToken &&
 */
void test_getToken_given_4_logical_AND_8_and_getToken_2times_should_get_NumberToken_and_OperatorToken(void)
{
	String *str = stringNew(" 4 &&  ");
	Number *num;
	Operator *op;
	
	num = (Number*)getToken(str);
	
	TEST_ASSERT_NOT_NULL(num);
	TEST_ASSERT_EQUAL(NUMBER_TOKEN , num->type);
	TEST_ASSERT_EQUAL(4 , num->value);
	TEST_ASSERT_EQUAL(1 , num->line->startindex);
	TEST_ASSERT_EQUAL(1 , num->line->length);
	tokenDisplay((Token *)num);
	numberDel(num);
	
	op = (Operator*)getToken(str);

	TEST_ASSERT_NOT_NULL(op);
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN , op->type);
	TEST_ASSERT_EQUAL_STRING("&&" , op->info->name);
	TEST_ASSERT_EQUAL(AND_OP , op->info->id);
	TEST_ASSERT_EQUAL(3 , op->line->startindex);
	TEST_ASSERT_EQUAL(2 , op->line->length);
	tokenDisplay((Token *)op);	
	operatorDel(op);
	
	op = (Operator*)getToken(str);
	TEST_ASSERT_NULL(op);
	TEST_ASSERT_EQUAL(7 , str->startindex);
	TEST_ASSERT_EQUAL(0 , str->length);
	
	operatorDel(op);
	stringDel(str);
}

/* 
 * Given "({56})" and getToken 2times
 * should throw an exception
 */
void test_getToken_given_open_bracket_square_bracket_56_close_bracket_square_bracket_getTokenx2_should_throw_an_exception(void)
{
	CEXCEPTION_T err;
	String *str = stringNew("({56})");
	Number *num;
	Operator *op;
	
	Try
	{
		operatorDel((Operator*)getToken(str));
		op = (Operator*)getToken(str);
		TEST_FAIL_MESSAGE("Should throw ERR_UNKNOWN_OPERATOR exception");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_UNKNOWN_OPERATOR , err , "Expect ERR_UNKNOWN_OPERATOR exception");
	}
	
	operatorDel(op);
	stringDel(str);
}

/* 
 * Given "|| | +" and getToken 2times
 * should get "||" , "|" and "+" operatorToken 
 */
void test_getToken_given_logical_OR_BITWISE_OR_and_ADD_operator_should_get_these_3_operator_token(void)
{
	String *str = stringNew("|| | +");
	Number *num;
	Operator *op;
	
	op = (Operator*)getToken(str); //get "||"
	
	TEST_ASSERT_NOT_NULL(op);
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN , op->type);
	TEST_ASSERT_EQUAL(0 , op->line->startindex);
	TEST_ASSERT_EQUAL(2 , op->line->length);
	TEST_ASSERT_EQUAL(2 , str->startindex);	
	TEST_ASSERT_EQUAL(4 , str->length);
	operatorDel(op);
	
	op = (Operator*)getToken(str); //get "|"

	TEST_ASSERT_NOT_NULL(op);
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN , op->type);
	TEST_ASSERT_EQUAL(3 , op->line->startindex);
	TEST_ASSERT_EQUAL(1 , op->line->length);
	TEST_ASSERT_EQUAL(4 , str->startindex);	
	TEST_ASSERT_EQUAL(2 , str->length);
	operatorDel(op);
	
	op = (Operator*)getToken(str); //get "+"

	TEST_ASSERT_NOT_NULL(op);
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN , op->type);
	TEST_ASSERT_EQUAL(5 , op->line->startindex);
	TEST_ASSERT_EQUAL(1 , op->line->length);
	TEST_ASSERT_EQUAL(6 , str->startindex);	
	TEST_ASSERT_EQUAL(0 , str->length);
	operatorDel(op);
	
	op = (Operator*)getToken(str); //get NULL because no more token

	TEST_ASSERT_NULL(op);	
	operatorDel(op);
	
	stringDel(str);
}

void test_getToken_given_minus_18_BITWISE_OR_432_should_get_numToken_and_OperatorToken(void)
{
	Number *num;
	Operator *op;
	String *str = stringNew("- 18 | 4 32");
	
	op = (Operator*)getToken(str);
	TEST_ASSERT_NOT_NULL(op);
	TEST_ASSERT_EQUAL_STRING("-" , op->info->name);
	TEST_ASSERT_EQUAL(0 , op->line->startindex);
	TEST_ASSERT_EQUAL(1 , op->line->length);	
	TEST_ASSERT_EQUAL(1 , str->startindex);	
	TEST_ASSERT_EQUAL(10 , str->length);
	tokenDisplay((Token *)op);
	operatorDel(op);	
	
	num = (Number*)getToken(str);
	TEST_ASSERT_NOT_NULL(num);
	TEST_ASSERT_EQUAL(NUMBER_TOKEN , num->type);
	TEST_ASSERT_EQUAL(18 , num->value);
	TEST_ASSERT_EQUAL(2 , num->line->startindex);
	TEST_ASSERT_EQUAL(2 , num->line->length);
	TEST_ASSERT_EQUAL(4 , str->startindex);	
	TEST_ASSERT_EQUAL(7 , str->length);
	tokenDisplay((Token *)num);
	numberDel(num);
	
	stringDel(str);
}

void test_getToken_given_complicated_expression_should_able_to_getToken(void)
{
	Number *num;
	Operator *op;
	String *str = stringNew(" (-2*4) &&  ");
	
	op = (Operator*)getToken(str);
	TEST_ASSERT_NOT_NULL(op);
	TEST_ASSERT_EQUAL_STRING("(" , op->info->name);
	TEST_ASSERT_EQUAL(1 , op->line->startindex);
	TEST_ASSERT_EQUAL(1 , op->line->length);	
	TEST_ASSERT_EQUAL(2 , str->startindex);	
	TEST_ASSERT_EQUAL(10 , str->length);
	tokenDisplay((Token *)op);
	operatorDel(op);	
	
	op = (Operator*)getToken(str);
	TEST_ASSERT_NOT_NULL(op);
	TEST_ASSERT_EQUAL_STRING("-" , op->info->name);
	TEST_ASSERT_EQUAL(2 , op->line->startindex);
	TEST_ASSERT_EQUAL(1 , op->line->length);	
	TEST_ASSERT_EQUAL(3 , str->startindex);	
	TEST_ASSERT_EQUAL(9 , str->length);
	tokenDisplay((Token *)op);
	operatorDel(op);	
	
	num = (Number*)getToken(str);
	TEST_ASSERT_NOT_NULL(num);
	TEST_ASSERT_EQUAL(NUMBER_TOKEN , num->type);
	TEST_ASSERT_EQUAL(2 , num->value);
	TEST_ASSERT_EQUAL(3 , num->line->startindex);
	TEST_ASSERT_EQUAL(1 , num->line->length);
	TEST_ASSERT_EQUAL(4 , str->startindex);	
	TEST_ASSERT_EQUAL(8 , str->length);
	tokenDisplay((Token *)num);
	numberDel(num);
	
	operatorDel((Operator*)getToken(str));
	numberDel((Number*)getToken(str));
	operatorDel((Operator*)getToken(str));
	
	op = (Operator*)getToken(str);
	TEST_ASSERT_NOT_NULL(op);
	TEST_ASSERT_EQUAL_STRING("&&" , op->info->name);
	TEST_ASSERT_EQUAL(8 , op->line->startindex);
	TEST_ASSERT_EQUAL(2 , op->line->length);	
	TEST_ASSERT_EQUAL(10 , str->startindex);	
	TEST_ASSERT_EQUAL(2 , str->length);
	tokenDisplay((Token *)op);
	operatorDel(op);	
	
	op = (Operator*)getToken(str);
	TEST_ASSERT_NULL(op);
	TEST_ASSERT_EQUAL(12 , str->startindex);	
	TEST_ASSERT_EQUAL(0 , str->length);
	operatorDel(op);
	
	stringDel(str);
}

void test_tokenDisplay_given_1_plus_2_should_display_and_pointing_1(void)
{
	String *expression = stringNew("1+2");
	Number *num = numberNew(1);
	num->line = stringSubString(expression , 0 , 1);
	tokenDisplay((Token *)num);
	
	numberDel(num);
	stringDel(expression);
}

void test_tokenDisplay_given_negative_43_times_50_should_display_and_pointing_50(void)
{
	String *expression = stringNew("-43 * 50");
	Number *num = numberNew(50);
	num->line = stringSubString(expression , 6 , 2);
	tokenDisplay((Token *)num);
	
	numberDel(num);
	stringDel(expression);
}

void test_tokenDisplay_given_plus_99_logical_AND_should_display_1_plus_2(void)
{
	String *expression = stringNew("+ 99 &&");
	Operator *op = operatorNewByName("&&");
	op->line = stringSubString(expression , 5 , 2);
	tokenDisplay((Token *)op);
	
	operatorDel(op);
	stringDel(expression);
}

void test_tokenDisplay_given_99abc10_should_display_this_identifier(void)
{
	String *expression = stringNew("99abc10");
	Identifier *iden = identifierNew("99abc10");
	iden->line = stringSubString(expression , 0 , 7);
	tokenDisplay((Token *)iden);
	
	identifierDel(iden);
	stringDel(expression);
}