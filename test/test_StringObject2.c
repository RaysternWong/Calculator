#include "unity.h"
#include "StringObject.h"
#include <string.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_stringRemoveOperator_complicated_expression_should_able_remove_operator(void)
{
	String *str = stringNew(" (-223 *10) - 6 ");
	stringTrim(str);
	
	String *removedOp = stringRemoveOperator(str , opSet); // "("
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL_STRING(" (-223 *10) - 6 " , removedOp->string); 
	TEST_ASSERT_EQUAL(1 , removedOp->startindex);
	TEST_ASSERT_EQUAL(1 , removedOp->length);
	TEST_ASSERT_EQUAL(2 , str->startindex);
	TEST_ASSERT_EQUAL(14 , str->length);
	stringDel(removedOp);
	
	removedOp = stringRemoveOperator(str , opSet); // "-"
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL(2 , removedOp->startindex);
	TEST_ASSERT_EQUAL(1 , removedOp->length);
	TEST_ASSERT_EQUAL(3 , str->startindex);
	TEST_ASSERT_EQUAL(13 , str->length);
	stringDel(removedOp);
	
	removedOp = stringRemoveWordContaining(str , numSet); // "223"
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL(3 , removedOp->startindex);
	TEST_ASSERT_EQUAL(3 , removedOp->length);
	TEST_ASSERT_EQUAL(6 , str->startindex);
	TEST_ASSERT_EQUAL(10 , str->length);
	stringDel(removedOp);
	
	removedOp = stringRemoveOperator(str , opSet); // "*"
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL(7 , removedOp->startindex);
	TEST_ASSERT_EQUAL(1 , removedOp->length);
	TEST_ASSERT_EQUAL(8 , str->startindex);
	TEST_ASSERT_EQUAL(8 , str->length);
	stringDel(removedOp);
	
	removedOp = stringRemoveWordContaining(str , numSet); // "10"
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL(8 , removedOp->startindex);
	TEST_ASSERT_EQUAL(2 , removedOp->length);
	TEST_ASSERT_EQUAL(10 , str->startindex);
	TEST_ASSERT_EQUAL(6 , str->length);
	stringDel(removedOp);
	
	removedOp = stringRemoveOperator(str , opSet); // ")"
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL(10 , removedOp->startindex);
	TEST_ASSERT_EQUAL(1 , removedOp->length);
	TEST_ASSERT_EQUAL(11 , str->startindex);
	TEST_ASSERT_EQUAL(5 , str->length);
	stringDel(removedOp);
	
	removedOp = stringRemoveOperator(str , opSet); // "-"
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL(12 , removedOp->startindex);
	TEST_ASSERT_EQUAL(1 , removedOp->length);
	TEST_ASSERT_EQUAL(13 , str->startindex);
	TEST_ASSERT_EQUAL(3 , str->length);
	stringDel(removedOp);
	
	removedOp = stringRemoveWordContaining(str , numSet); // "6"
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL(14 , removedOp->startindex);
	TEST_ASSERT_EQUAL(1 , removedOp->length);
	TEST_ASSERT_EQUAL(15 , str->startindex);
	TEST_ASSERT_EQUAL(1 , str->length);
	stringDel(removedOp);
	
	removedOp = stringRemoveWordContaining(str , numSet); // no more words to remove
	stringTrim(str);
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL(0 , removedOp->startindex);
	TEST_ASSERT_EQUAL(0 , removedOp->length);
	TEST_ASSERT_EQUAL(16 , str->startindex);
	TEST_ASSERT_EQUAL(0 , str->length);
	stringDel(removedOp);
	
	stringDel(str);
}

void test_stringRemoveOperator_complicated_expression_should_able_remove_operator2(void)
{
	String *str = stringNew(" &&10 | (70 ||2345) \t\t");
	stringTrim(str);
	
	String *removedOp = stringRemoveOperator(str , opSet); // "&&"
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL_STRING(" &&10 | (70 ||2345) \t\t" , removedOp->string); 
	TEST_ASSERT_EQUAL(1 , removedOp->startindex);
	TEST_ASSERT_EQUAL(2 , removedOp->length);
	TEST_ASSERT_EQUAL(3 , str->startindex);
	TEST_ASSERT_EQUAL(19 , str->length);
	stringDel(removedOp);
	
	removedOp = stringRemoveWordContaining(str , numSet); // "10"
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL(3 , removedOp->startindex);
	TEST_ASSERT_EQUAL(2 , removedOp->length);
	TEST_ASSERT_EQUAL(5 , str->startindex);
	TEST_ASSERT_EQUAL(17 , str->length);
	stringDel(removedOp);
	
	removedOp = stringRemoveOperator(str , opSet); // "|"
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL(6 , removedOp->startindex);
	TEST_ASSERT_EQUAL(1 , removedOp->length);
	TEST_ASSERT_EQUAL(7 , str->startindex);
	TEST_ASSERT_EQUAL(15 , str->length);
	stringDel(removedOp);
	
	removedOp = stringRemoveOperator(str , opSet); // "("
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL(8 , removedOp->startindex);
	TEST_ASSERT_EQUAL(1 , removedOp->length);
	TEST_ASSERT_EQUAL(9 , str->startindex);
	TEST_ASSERT_EQUAL(13 , str->length);
	stringDel(removedOp);
	
	removedOp = stringRemoveWordContaining(str , numSet); // "70"
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL(9 , removedOp->startindex);
	TEST_ASSERT_EQUAL(2 , removedOp->length);
	TEST_ASSERT_EQUAL(11 , str->startindex);
	TEST_ASSERT_EQUAL(11 , str->length);
	stringDel(removedOp);
	
	removedOp = stringRemoveOperator(str , opSet); // "||"
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL(12 , removedOp->startindex);
	TEST_ASSERT_EQUAL(2 , removedOp->length);
	TEST_ASSERT_EQUAL(14 , str->startindex);
	TEST_ASSERT_EQUAL(8 , str->length);
	stringDel(removedOp);
	
	stringDel(str);
}