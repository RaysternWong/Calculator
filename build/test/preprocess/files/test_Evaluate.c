#include "unity.h"
#include "mock_Token.h"
#include "mock_StringObject.h"
#include "TokenDebug.h"
#include "Stack.h"
#include "OperatorToken.h"
#include "Operator.h"
#include "NumberToken.h"
#include "Evaluate.h"
#include "ErrorCode.h"










void setUp(void){}



void tearDown(void){}





void test_tryToPushOperatorAndEvaluate_given_plus_should_push_to_stack(void){



 Stack *operatorStack = stackNew(100);

 Stack *dataStack = stackNew(100) ;

 Operator *Plus = operatorNewByName("+");

 Operator *ptrOpr;



 tryToPushOperatorAndEvaluate( Plus , operatorStack, dataStack );

 UnityAssertEqualNumber((_U_SINT)(_UP)((Plus)), (_U_SINT)(_UP)(((Operator *)stackPop( operatorStack))), (((void *)0)), (_U_UINT)30, UNITY_DISPLAY_STYLE_HEX32);



}



void test_tryToPushOperatorAndEvaluate_given_plus_multi_should_push_to_stack(void){



 Stack *operatorStack = stackNew(100);

 Stack *dataStack = stackNew(100) ;

 Operator *Plus = operatorNewByName("+");

 Operator *Multi = operatorNewByName("*");



 tryToPushOperatorAndEvaluate( Plus , operatorStack, dataStack );

 tryToPushOperatorAndEvaluate( Multi , operatorStack, dataStack );



 UnityAssertEqualNumber((_U_SINT)(_UP)((Multi)), (_U_SINT)(_UP)(((Operator *)stackPop( operatorStack))), (((void *)0)), (_U_UINT)44, UNITY_DISPLAY_STYLE_HEX32);

 UnityAssertEqualNumber((_U_SINT)(_UP)((Plus)), (_U_SINT)(_UP)(((Operator *)stackPop( operatorStack))), (((void *)0)), (_U_UINT)45, UNITY_DISPLAY_STYLE_HEX32);



}



void test_tryToPushOperatorAndEvaluate_given_2_Plus_4_Plus_should_answer_the_token_six(void){



 Stack *operatorStack = stackNew(100);

 Stack *dataStack = stackNew(100);

 Operator *Plus1 = operatorNewByName("+");

 Operator *Plus2 = operatorNewByName("+");

 Operator *op;

 Number *two = numberNew(2);

 Number *four = numberNew(4);

 Number *num;





 stackPush( dataStack , two );

 stackPush( dataStack , four );

 stackPush( operatorStack , Plus1 );

 tryToPushOperatorAndEvaluate( Plus2 , operatorStack, dataStack );



 num = (Number *)stackPop( dataStack );

 if ((((num)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)67);;};

 UnityAssertEqualNumber((_U_SINT)((NUMBER_TOKEN)), (_U_SINT)((num->type)), (((void *)0)), (_U_UINT)68, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((6)), (_U_SINT)((num->value)), (((void *)0)), (_U_UINT)69, UNITY_DISPLAY_STYLE_INT);



 op = (Operator *)stackPop( operatorStack );

 if ((((op)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)72);;};

 UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((op->type)), (((void *)0)), (_U_UINT)73, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((ADD_OP)), (_U_SINT)((op->info->id)), (((void *)0)), (_U_UINT)74, UNITY_DISPLAY_STYLE_INT);



}



void test_tryToPushOperatorAndEvaluate_given_2_Plus_4_Multi_should_answer_the_token_four(void){





 Stack *operatorStack = stackNew(100);

 Stack *dataStack = stackNew(100);

 Operator *Plus = operatorNewByName("+");

 Operator *Multi = operatorNewByName("*");

 Operator *op;

 Number *two = numberNew(2);

 Number *four = numberNew(4);

 Number *num;





 stackPush( dataStack , two );

 stackPush( dataStack , four );

 stackPush( operatorStack , Plus );

 tryToPushOperatorAndEvaluate( Multi , operatorStack, dataStack );





 num = (Number *)stackPop( dataStack );

 if ((((num)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)98);;};

 UnityAssertEqualNumber((_U_SINT)((NUMBER_TOKEN)), (_U_SINT)((num->type)), (((void *)0)), (_U_UINT)99, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((num->value)), (((void *)0)), (_U_UINT)100, UNITY_DISPLAY_STYLE_INT);



 op = (Operator *)stackPop( operatorStack );

 if ((((op)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)103);;};

 UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((op->type)), (((void *)0)), (_U_UINT)104, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((MUL_OP)), (_U_SINT)((op->info->id)), (((void *)0)), (_U_UINT)105, UNITY_DISPLAY_STYLE_INT);

}



void test_tryToPushOperatorAndEvaluate_given_2_Plus_4_BITWISE_AND_should_answer_the_token_four(void){





 Stack *operatorStack = stackNew(100);

 Stack *dataStack = stackNew(100);

 Operator *Plus = operatorNewByName("+");

 Operator *BIT_AND = operatorNewByName("&");

 Operator *op;

 Number *two = numberNew(2);

 Number *four = numberNew(4);

 Number *num;





 stackPush( dataStack , two );

 stackPush( dataStack , four );

 stackPush( operatorStack , Plus );

 tryToPushOperatorAndEvaluate( BIT_AND , operatorStack, dataStack );





 num = (Number *)stackPop( dataStack );

 if ((((num)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)128);;};

 UnityAssertEqualNumber((_U_SINT)((NUMBER_TOKEN)), (_U_SINT)((num->type)), (((void *)0)), (_U_UINT)129, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((6)), (_U_SINT)((num->value)), (((void *)0)), (_U_UINT)130, UNITY_DISPLAY_STYLE_INT);



 op = (Operator *)stackPop( operatorStack );

  if ((((op)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)133);;};

 UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((op->type)), (((void *)0)), (_U_UINT)134, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((BITWISE_AND_OP)), (_U_SINT)((op->info->id)), (((void *)0)), (_U_UINT)135, UNITY_DISPLAY_STYLE_INT);



}



void test_tryToPushOperatorAndEvaluate_given_2_Plus_4_Multi_5_Plus_should_answer_the_token_twenty_two(void){





 Stack *operatorStack = stackNew(100);

 Stack *dataStack = stackNew(100);

 Operator *Plus1 = operatorNewByName("+");

 Operator *Plus2 = operatorNewByName("+");

 Operator *Multi = operatorNewByName("*");

 Operator *op;

 Number *two = numberNew(2);

 Number *four = numberNew(4);

 Number *five = numberNew(5);

 Number *num;





 stackPush( dataStack , two );

 stackPush( dataStack , four );

 stackPush( dataStack , five );

 stackPush( operatorStack , Plus1 );

 stackPush( operatorStack , Multi );



 tryToPushOperatorAndEvaluate(Plus2 , operatorStack, dataStack );



 num = (Number *)stackPop( dataStack );

 if ((((num)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)163);;};

 UnityAssertEqualNumber((_U_SINT)((NUMBER_TOKEN)), (_U_SINT)((num->type)), (((void *)0)), (_U_UINT)164, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((22)), (_U_SINT)((num->value)), (((void *)0)), (_U_UINT)165, UNITY_DISPLAY_STYLE_INT);



 op = (Operator *)stackPop( operatorStack );

 if ((((op)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)168);;};

  UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((op->type)), (((void *)0)), (_U_UINT)169, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((ADD_OP)), (_U_SINT)((op->info->id)), (((void *)0)), (_U_UINT)170, UNITY_DISPLAY_STYLE_INT);



}



void test_tryToPushOperatorAndEvaluate_given_2_Multi_13_Plus_7_AND_should_answer_the_token_ninety_three(void){





 Stack *operatorStack = stackNew(100);

 Stack *dataStack = stackNew(100);

 Operator *Plus = operatorNewByName("+");

 Operator *BIT_AND = operatorNewByName("&");

 Operator *Multi = operatorNewByName("*");

 Operator *op;

 Number *two = numberNew(2);

 Number *thirteen = numberNew(13);

 Number *seven = numberNew(7);

 Number *num;





 stackPush( dataStack , two );

 stackPush( dataStack , thirteen );

 stackPush( dataStack , seven );

  stackPush( operatorStack , Plus );

 stackPush( operatorStack , Multi );



 tryToPushOperatorAndEvaluate( BIT_AND , operatorStack, dataStack );



 num = (Number *)stackPop( dataStack );

 if ((((num)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)198);;};

 UnityAssertEqualNumber((_U_SINT)((NUMBER_TOKEN)), (_U_SINT)((num->type)), (((void *)0)), (_U_UINT)199, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((93)), (_U_SINT)((num->value)), (((void *)0)), (_U_UINT)200, UNITY_DISPLAY_STYLE_INT);



 op = (Operator *)stackPop( operatorStack );

 if ((((op)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)203);;};

  UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((op->type)), (((void *)0)), (_U_UINT)204, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((BITWISE_AND_OP)), (_U_SINT)((op->info->id)), (((void *)0)), (_U_UINT)205, UNITY_DISPLAY_STYLE_INT);



}



void test_tryToPushOperatorAndEvaluate_given_2_plus_4_plus_5__Multi_should_answer_the_token_five(void){





 Stack *operatorStack = stackNew(100);

 Stack *dataStack = stackNew(100);

 Operator *Plus1 = operatorNewByName("+");

 Operator *Plus2 = operatorNewByName("+");

 Operator *Multi = operatorNewByName("*");

 Operator *op;

 Number *two = numberNew(2);

 Number *four = numberNew(4);

 Number *five = numberNew(5);

 Number *num;





 stackPush( dataStack , two );

 stackPush( dataStack , four );

  stackPush( dataStack , five );

  stackPush( operatorStack , Plus1 );

 stackPush( operatorStack , Plus2 );

 tryToPushOperatorAndEvaluate( Multi , operatorStack , dataStack );



  num = (Number *)stackPop( dataStack );

 if ((((num)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)232);;};

 UnityAssertEqualNumber((_U_SINT)((NUMBER_TOKEN)), (_U_SINT)((num->type)), (((void *)0)), (_U_UINT)233, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((num->value)), (((void *)0)), (_U_UINT)234, UNITY_DISPLAY_STYLE_INT);



 op = (Operator *)stackPop( operatorStack );

 if ((((op)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)237);;};

  UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((op->type)), (((void *)0)), (_U_UINT)238, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((MUL_OP)), (_U_SINT)((op->info->id)), (((void *)0)), (_U_UINT)239, UNITY_DISPLAY_STYLE_INT);



}



void test_evaluate_given_token_2_plus_3_should_get_5(void){



 int Result;



 Number *two = numberNew(2);

 Number *three = numberNew(3);

 Operator *Plus = operatorNewByName("+");

 String expression = {.string="2+3"};



 getToken_CMockExpectAndReturn(252, &expression, (Token*)two);

 getToken_CMockExpectAndReturn(253, &expression, (Token*)Plus);

  getToken_CMockExpectAndReturn(254, &expression, (Token*)three);

  getToken_CMockExpectAndReturn(255, &expression, ((void *)0));



 Result = evaluate(&expression);

 UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((Result)), (((void *)0)), (_U_UINT)258, UNITY_DISPLAY_STYLE_INT);



}



void test_evaluate_given_token_2_plus_3_Mutiple_5_plus_6_should_get_23(void){



 int Result;

  Number *two = numberNew(2);

 Number *three = numberNew(3);

  Number *five = numberNew(5);

  Number *six = numberNew(6);

 Operator *Plus1 = operatorNewByName("+");

  Operator *Plus2 = operatorNewByName("+");

 Operator *Multi = operatorNewByName("*");

 String expression = {.string="2+3*5+6"};



  getToken_CMockExpectAndReturn(274, &expression, (Token*)two);

 getToken_CMockExpectAndReturn(275, &expression, (Token*)Plus1);

  getToken_CMockExpectAndReturn(276, &expression, (Token*)three);

 getToken_CMockExpectAndReturn(277, &expression, (Token*)Multi);

 getToken_CMockExpectAndReturn(278, &expression, (Token*)five);

  getToken_CMockExpectAndReturn(279, &expression, (Token*)Plus2);

 getToken_CMockExpectAndReturn(280, &expression, (Token*)six);

  getToken_CMockExpectAndReturn(281, &expression, ((void *)0));



 Result = evaluate(&expression);

  UnityAssertEqualNumber((_U_SINT)((23)), (_U_SINT)((Result)), (((void *)0)), (_U_UINT)284, UNITY_DISPLAY_STYLE_INT);



}
