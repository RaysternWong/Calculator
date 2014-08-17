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

void test_Calculator(void)
{
	String *str = stringNew("1+2");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(3 , result);
}

void test_Calculator1(void)
{
	String *str = stringNew("-1+2");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(1 , result);
}

void test_Calculator2(void)
{
	String *str = stringNew("--2*20");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(40 , result);
}

void test_Calculator3(void)
{
	String *str = stringNew(" (-2) *80 ");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(-160 , result);
}

void test_Calculator4(void)
{
	String *str = stringNew(" (8 && 1)+21\t");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(22 , result);
}

void test_Calculator5(void)
{
	String *str = stringNew(" (12 | 2) / 2 \t");
	
	int result = Calculator(str);
	
	TEST_ASSERT_EQUAL(7 , result);
}