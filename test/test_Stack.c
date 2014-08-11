#include "unity.h"
#include "Stack.h"
#include "CException.h"
#include "ErrorCode.h"

#define STACK_LENGTH 100

void setUp(void)
{

	

}

void tearDown(void)
{
}



void test_stackNew_should_setup_the_new_stack(void)
{	
	Stack *stack;
  stack = stackNew(STACK_LENGTH);
	TEST_ASSERT_NOT_NULL(stack);
	TEST_ASSERT_NOT_NULL(stack->buffer);
	TEST_ASSERT_EQUAL(0 , stack->size);
	TEST_ASSERT_EQUAL(STACK_LENGTH , stack->length);
}

void test_stackPush_given_1number_push_to_stack_should_alocate(void)
{
	Stack *stack;
    stack = stackNew(STACK_LENGTH);
	int element1 = 1;
	int *ptrInt;
	
	stackPush(stack , &element1);
	ptrInt = (int*) stack->buffer[0];
	TEST_ASSERT_EQUAL(element1, *ptrInt);
	TEST_ASSERT_EQUAL(STACK_LENGTH, stack->length);
}

void test_stackPush_given_2number_push_to_stack_should_alocate(void)
{
	Stack *stack;
    stack = stackNew(STACK_LENGTH);
	int element1 = 1;
	int element2 = 2;
	int *ptrInt1;
	int *ptrInt2;
	
	stackPush(stack , &element1);
	stackPush(stack , &element2);
	ptrInt1 = (int*) stack->buffer[0];
	ptrInt2 = (int*) stack->buffer[0];
	TEST_ASSERT_EQUAL(element1, *ptrInt1);
	TEST_ASSERT_EQUAL(element1, *ptrInt2);
	TEST_ASSERT_EQUAL(STACK_LENGTH, stack->length);
}

void test_stackPush_given_4number_push_to_stack_but_length_is_3_should_throw_exception(void)
{
	CEXCEPTION_T err;
	Stack *stack;
    stack = stackNew(3);
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	int element4 = 4;
	
	Try
	{	
		stackPush(stack, &element1);
		stackPush(stack, &element2);
		stackPush(stack, &element3);
		stackPush(stack, &element4);
		TEST_FAIL_MESSAGE("should throw ERR_STACK_FULL exception");
	}
	Catch (err)
	{ 	
		TEST_ASSERT_EQUAL_MESSAGE( ERR_STACK_FULL , err , "Expected ERR_STACK_FULL exception");
	}
}


void test_stackPop_given_2_number_should_pop_2_number_and_size_become_zero(void)
{	
	Stack *stack;
    stack = stackNew(STACK_LENGTH);
	int element1 = 1;
	int element2 = 2;
	int *ptrInt1;
	int *ptrInt2;
	
	stackPush(stack , &element1);
	stackPush(stack , &element2);
	ptrInt2 = (int*) stackPop(stack);
	ptrInt1 = (int*) stackPop(stack);
	TEST_ASSERT_EQUAL(element2  , *ptrInt2);
	TEST_ASSERT_EQUAL(element1  , *ptrInt1);
	TEST_ASSERT_EQUAL(0 , stack->size);
}

void test_stackPop_given_2number_but_pop_3_times_should_return_NULL(void)
{	
	CEXCEPTION_T err;
	Stack *stack;
    stack = stackNew(STACK_LENGTH);
	int element1 = 1;
	int element2 = 2;
	int *ptrInt1;
	int *ptrInt2;
	int *ptrNULL;
	
	stackPush(stack , &element1);
	stackPush(stack , &element2);
	ptrInt2 = (int*) stackPop(stack);
	ptrInt1 = (int*) stackPop(stack);
	ptrNULL = (int*) stackPop(stack);
	
	TEST_ASSERT_EQUAL(element2  , *ptrInt2);
	TEST_ASSERT_EQUAL(element1  , *ptrInt1);
	TEST_ASSERT_NULL(ptrNULL);	
}

void test_stackPeep_given_1_should_set_1_as_Peep(void)
{
    
    Stack *stack = stackNew(STACK_LENGTH);
	int element1 = 1;
	int *ptrInt1;
	
	stackPush(stack , &element1);
	ptrInt1 = (int*) stackPeep(stack);
	TEST_ASSERT_EQUAL(element1  , *ptrInt1);

}

void test_stackPeep_given_1_2_should_set_2_as_Peep(void)
{
	Stack *stack;
    stack = stackNew(STACK_LENGTH);
	int element1 = 1;
	int element2 = 2;
	int *ptrInt;

	
	stackPush(stack , &element1);
	stackPush(stack , &element2);
	ptrInt = (int*) stackPeep(stack);
	TEST_ASSERT_EQUAL(element2  , *ptrInt);

}

void test_stackPeep_given_nothing_should_set_NULL_as_Peep(void)
{
	Stack *stack;
    stack = stackNew(STACK_LENGTH);

	TEST_ASSERT_NULL( stackPeep(stack));
}

