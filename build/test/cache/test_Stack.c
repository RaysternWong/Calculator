#include "unity.h"
#include "Stack.h"
#include "ErrorCode.h"
#include "CException.h"






void setUp(void)

{







}



void tearDown(void)

{

}







void test_stackNew_should_setup_the_new_stack(void)

{

 Stack *stack;

    stack = stackNew(100);

 if ((((stack)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)25);;};

 if ((((stack->buffer)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)26);;};

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((stack->size)), (((void *)0)), (_U_UINT)27, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((100)), (_U_SINT)((stack->length)), (((void *)0)), (_U_UINT)28, UNITY_DISPLAY_STYLE_INT);

}



void test_stackPush_given_1number_push_to_stack_should_alocate(void)

{

 Stack *stack;

    stack = stackNew(100);

 int element1 = 1;

 int *ptrInt;



 stackPush(stack , &element1);

 ptrInt = (int*) stack->buffer[0];

 UnityAssertEqualNumber((_U_SINT)((element1)), (_U_SINT)((*ptrInt)), (((void *)0)), (_U_UINT)40, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((100)), (_U_SINT)((stack->length)), (((void *)0)), (_U_UINT)41, UNITY_DISPLAY_STYLE_INT);

}



void test_stackPush_given_2number_push_to_stack_should_alocate(void)

{

 Stack *stack;

    stack = stackNew(100);

 int element1 = 1;

 int element2 = 2;

 int *ptrInt1;

 int *ptrInt2;



 stackPush(stack , &element1);

 stackPush(stack , &element2);

 ptrInt1 = (int*) stack->buffer[0];

 ptrInt2 = (int*) stack->buffer[0];

 UnityAssertEqualNumber((_U_SINT)((element1)), (_U_SINT)((*ptrInt1)), (((void *)0)), (_U_UINT)57, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((element1)), (_U_SINT)((*ptrInt2)), (((void *)0)), (_U_UINT)58, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((100)), (_U_SINT)((stack->length)), (((void *)0)), (_U_UINT)59, UNITY_DISPLAY_STYLE_INT);

}



void test_stackPush_given_4number_push_to_stack_but_length_is_3_should_throw_exception(void)

{

 unsigned int err;

 Stack *stack;

    stack = stackNew(3);

 int element1 = 1;

 int element2 = 2;

 int element3 = 3;

 int element4 = 4;



 { jmp_buf *PrevFrame, NewFrame; unsigned int MY_ID = (0); PrevFrame = CExceptionFrames[(0)].pFrame; CExceptionFrames[MY_ID].pFrame = (jmp_buf*)(&NewFrame); CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); if (_setjmp(NewFrame) == 0) { if (&PrevFrame)

 {

  stackPush(stack, &element1);

  stackPush(stack, &element2);

  stackPush(stack, &element3);

  stackPush(stack, &element4);

  UnityFail( ("should throw ERR_STACK_FULL exception"), (_U_UINT)78);;

 }

 else { } CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); } else { err = CExceptionFrames[MY_ID].Exception; err=err; } CExceptionFrames[MY_ID].pFrame = PrevFrame; } if (CExceptionFrames[(0)].Exception != (0x5A5A5A5A))

 {

  UnityAssertEqualNumber((_U_SINT)((ERR_STACK_FULL)), (_U_SINT)((err)), ("Expected ERR_STACK_FULL exception"), (_U_UINT)82, UNITY_DISPLAY_STYLE_INT);

 }

}





void test_stackPop_given_2_number_should_pop_2_number_and_size_become_zero(void)

{

 Stack *stack;

    stack = stackNew(100);

 int element1 = 1;

 int element2 = 2;

 int *ptrInt1;

 int *ptrInt2;



 stackPush(stack , &element1);

 stackPush(stack , &element2);

 ptrInt2 = (int*) stackPop(stack);

 ptrInt1 = (int*) stackPop(stack);

 UnityAssertEqualNumber((_U_SINT)((element2)), (_U_SINT)((*ptrInt2)), (((void *)0)), (_U_UINT)100, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((element1)), (_U_SINT)((*ptrInt1)), (((void *)0)), (_U_UINT)101, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((stack->size)), (((void *)0)), (_U_UINT)102, UNITY_DISPLAY_STYLE_INT);

}



void test_stackPop_given_2number_but_pop_3_times_should_return_NULL(void)

{

 unsigned int err;

 Stack *stack;

    stack = stackNew(100);

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



 UnityAssertEqualNumber((_U_SINT)((element2)), (_U_SINT)((*ptrInt2)), (((void *)0)), (_U_UINT)122, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((element1)), (_U_SINT)((*ptrInt1)), (((void *)0)), (_U_UINT)123, UNITY_DISPLAY_STYLE_INT);

 if ((((ptrNULL)) == ((void *)0))) {} else {UnityFail( (" Expected NULL"), (_U_UINT)(_U_UINT)(_U_UINT)124);;};

}



void test_stackPeep_given_1_should_set_1_as_Peep(void)

{



    Stack *stack = stackNew(100);

 int element1 = 1;

 int *ptrInt1;



 stackPush(stack , &element1);

 ptrInt1 = (int*) stackPeep(stack);

 UnityAssertEqualNumber((_U_SINT)((element1)), (_U_SINT)((*ptrInt1)), (((void *)0)), (_U_UINT)136, UNITY_DISPLAY_STYLE_INT);



}



void test_stackPeep_given_1_2_should_set_2_as_Peep(void)

{

 Stack *stack;

    stack = stackNew(100);

 int element1 = 1;

 int element2 = 2;

 int *ptrInt;





 stackPush(stack , &element1);

 stackPush(stack , &element2);

 ptrInt = (int*) stackPeep(stack);

 UnityAssertEqualNumber((_U_SINT)((element2)), (_U_SINT)((*ptrInt)), (((void *)0)), (_U_UINT)152, UNITY_DISPLAY_STYLE_INT);



}



void test_stackPeep_given_nothing_should_set_NULL_as_Peep(void)

{

 Stack *stack;

    stack = stackNew(100);



 if ((((stackPeep(stack))) == ((void *)0))) {} else {UnityFail( (" Expected NULL"), (_U_UINT)(_U_UINT)(_U_UINT)161);;};

}
