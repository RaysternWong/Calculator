#include "unity.h"
#include "Calculator.h"
#include "command_prompt.h"
#include "history_buffer.h"
#include "get_ch.h"
#include "putch.h"
#include "Evaluate.h"
#include "Token.h"
#include "TokenDebug.h"
#include "Stack.h"
#include "StringObject.h"
#include <stdlib.h>
#include <string.h>
#include "OperatorToken.h"
#include "NumberToken.h"
#include "Operator.h"
#include "IdentifierToken.h"
#include "ErrorCode.h"
#include "CException.h"
#include <stdio.h>
#include <malloc.h>

void setUp(void)
{
}

void tearDown(void)
{
}

// test given 1 + 2 should return the result 3
void test_Calculator_given_1_add_2_should_return_3(void)
{
	String *str = stringNew("1+2");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(3 , result);
}

// test given - 1 + 2 should return the result 1
void test_Calculator_given_minus_1_add_2_should_return_1(void)
{
	String *str = stringNew("-1+2");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(1 , result);
}

// test given - - 2 * 20 should return the result 40
void test_Calculator_given_minus_minus_2_multiply_20_should_return_40(void)
{
	String *str = stringNew("--2*20");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(40 , result);
}

// test given (-2) * 80 should return the result -160
void test_Calculator_given_openBracket_minus_2_closeBracket_multiply_80_should_return_minus_160(void)
{
	String *str = stringNew(" (-2) *80 ");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(-160 , result);
}

// test given (8 && 1) + 21 should return the result 22
void test_Calculator_given_openBracket_8_AND_1_closeBracket_add_21_should_return_22(void)
{
	String *str = stringNew(" (8 && 1)+21\t");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(22 , result);
}

// test given (12 | 2) / 2 should return the result 7
void test_Calculator_given_openBracket_12_bitwiseOr_2_closeBracket_divide_2_should_return_7(void)
{
	String *str = stringNew(" (12 | 2) / 2 \t");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(7 , result);
}

// test given ~ 1 + 2 should return the result 2 
void test_Calculator_given_bitwiseNot_1_add_2_should_return_2(void) {
	String *str = stringNew("~1 + 2 \t");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(2 , result);
}

// test given 5 % 2 should return the result 1
void test_Calculator_given_5_modulo_2_should_return_the_result_1(void) {
	String *str = stringNew("5 % 2 \t");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(1 , result);
}

// test given (2 << 1) + 5 should return the result 9
void test_Calculator_given_openBracket_2_shiftLeft_by_1_closeBracket_add_5_should_return_9(void) {
	String *str = stringNew("(2 << 1) + 5 \t");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(9 , result);
}

// test given (8 >> 2) * 6 should return the result 12
void test_Calculator_given_openBracket_8_shiftRight_by_2_closeBracket_multiply_6_should_return_12(void) {
	String *str = stringNew("(8 >> 2) * 6 \t");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(12 , result);
}

// test given (1 + 2) < 5 should return the result 1 
void test_Calculator_given_openBracket_1_add_2_closeBracket_Lesser_than_5_should_return_1(void) {
	String *str = stringNew("(1 + 2) < 5 \t");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(1 , result);
}

// test given (1 + 1) > 5 should return the result 0
void test_Calculator_given_openBracket_1_add_1_closeBracket_greater_than_5_should_return_the_result_0(void) {
	String *str = stringNew("(1 + 1) > 5 \t");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(0 , result);
}

// test given (3 + 3) == 6 should return the result 1
void test_Calculator_given_openBracket_3_add_3_closeBracket_equal_to_6_should_return_1(void) {
	String *str = stringNew("(3 + 3) == 6 \t");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(1 , result);
}

// test given (2 & 1) + 3 should return the result 3
void test_Calculator_given_openBracket_2_bitwiseAnd_1_closeBracket_add_3_should_return_3(void) {
	String *str = stringNew("(2 & 1) + 3 \t");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(3 , result);
}

// test given (5 || 10) + 5 should return the result 6
void test_Calculator_given_openBracket_5_Or_10_closeBracket_add_5_should_return_6(void) {
	String *str = stringNew("(5 || 10) + 5 \t");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(6 , result);
}

// test given (5 || 10) && 1 * (6 + 1) should return the result 1
void test_Calculator_given_openBracket_5_Or_10_closeBracket_And_1_multiply_openBracket_6_add_1_closeBracket_should_return_7(void) {
	String *str = stringNew("(5 || 10) && 1 * (6 + 1)\t");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(1 , result);
}

// test given !2 should return 2
void test_Calculator_given_Not_2_should_return(void) {
	String *str = stringNew("!2\t");
	
	int result = Calculator(str);

	TEST_ASSERT_EQUAL(-3 , result);
}