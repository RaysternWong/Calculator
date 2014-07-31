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

 if ((((num)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)68);;};

 UnityAssertEqualNumber((_U_SINT)((NUMBER_TOKEN)), (_U_SINT)((num->type)), (((void *)0)), (_U_UINT)69, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((6)), (_U_SINT)((num->value)), (((void *)0)), (_U_UINT)70, UNITY_DISPLAY_STYLE_INT);



 op = (Operator *)stackPop( operatorStack );

 if ((((op)) == ((void *)0))) {} else {UnityFail( (" Expected NULL"), (_U_UINT)(_U_UINT)(_U_UINT)73);;};







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

 tryToPushOperatorAndEvaluate(Multi , operatorStack, dataStack );





 num = (Number *)stackPop( dataStack );

 if ((((num)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)99);;};

 UnityAssertEqualNumber((_U_SINT)((NUMBER_TOKEN)), (_U_SINT)((num->type)), (((void *)0)), (_U_UINT)100, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((num->value)), (((void *)0)), (_U_UINT)101, UNITY_DISPLAY_STYLE_INT);



 op = (Operator *)stackPop( operatorStack );

 if ((((op)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)104);;};

 UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((op->type)), (((void *)0)), (_U_UINT)105, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((MUL_OP)), (_U_SINT)((op->info->id)), (((void *)0)), (_U_UINT)106, UNITY_DISPLAY_STYLE_INT);

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

 if ((((num)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)130);;};

 UnityAssertEqualNumber((_U_SINT)((NUMBER_TOKEN)), (_U_SINT)((num->type)), (((void *)0)), (_U_UINT)131, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((6)), (_U_SINT)((num->value)), (((void *)0)), (_U_UINT)132, UNITY_DISPLAY_STYLE_INT);



 op = (Operator *)stackPop( operatorStack );

 if ((((op)) == ((void *)0))) {} else {UnityFail( (" Expected NULL"), (_U_UINT)(_U_UINT)(_U_UINT)135);;};



}



void xtest_tryToPushOperatorAndEvaluate_given_2_Plus_4_Multi_3_should_answer_the_token_fourteen(void){





 Stack *operatorStack = stackNew(100);

 Stack *dataStack = stackNew(100);

 Operator *Plus = operatorNewByName("+");

 Operator *Multi = operatorNewByName("*");

 Number *two = numberNew(2);

 Number *four = numberNew(4);

 Number *three = numberNew(3);





 stackPush( dataStack , two );

 stackPush( dataStack , four );

 stackPush( operatorStack , Plus );

 tryToPushOperatorAndEvaluate( Multi , operatorStack, dataStack );



 Number *ans = (Number *)stackPop( dataStack );

 UnityAssertEqualNumber((_U_SINT)((14)), (_U_SINT)((ans->value)), (((void *)0)), (_U_UINT)157, UNITY_DISPLAY_STYLE_INT);



}





void xtest_tryToPushOperatorAndEvaluate_given_2_multi_2_plus_2_should_answer_the_token_six(void){





 Stack *operatorStack = stackNew(100);

 Stack *dataStack = stackNew(100);

 Operator *Plus = operatorNewByName("+");

 Operator *Multi = operatorNewByName("*");

 Number *two = numberNew(2);



 stackPush( dataStack , two );

 stackPush( dataStack , two );

 tryToPushOperatorAndEvaluate( Multi , operatorStack , dataStack );

 tryToPushOperatorAndEvaluate( Plus , operatorStack , dataStack );

 stackPush( dataStack , two );





 Number *ans = (Number *)stackPop( dataStack );

 UnityAssertEqualNumber((_U_SINT)((6)), (_U_SINT)((ans->value)), (((void *)0)), (_U_UINT)179, UNITY_DISPLAY_STYLE_INT);



}



void test_evaluate_given_token_2_plus_3_should_get_5(void){



 int Result;



 Number *two = numberNew(2);

 Number *three = numberNew(3);

 Operator *Plus = operatorNewByName("+");

 String expression = {.string="2+3"};



 getToken_CMockExpectAndReturn(192, &expression, (Token*)two);

 getToken_CMockExpectAndReturn(193, &expression, (Token*)Plus);

    getToken_CMockExpectAndReturn(194, &expression, (Token*)three);

    getToken_CMockExpectAndReturn(195, &expression, ((void *)0));



 Result = evaluate(&expression);

 UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((Result)), (((void *)0)), (_U_UINT)198, UNITY_DISPLAY_STYLE_INT);



}



void xtest_evaluate_given_token_2_plus_3_Mutiple_5_plus_6_should_get_23(void){



 int result;

    Number two ={.type = NUMBER_TOKEN, .value = 2};

 Number three ={.type = NUMBER_TOKEN, .value = 3};

 Number five ={.type = NUMBER_TOKEN, .value = 5};

 Number six ={.type = NUMBER_TOKEN, .value = 6};

 Operator Plus = {.type = OPERATOR_TOKEN, .info =getOperatorByID(ADD_OP) };

 Operator Multi = {.type = OPERATOR_TOKEN, .info =getOperatorByID(MUL_OP) };

 String expression = {.string="2+3*5+6"};



    getToken_CMockExpectAndReturn(213, &expression, (Token*)&two);

 getToken_CMockExpectAndReturn(214, &expression, (Token*)&Plus);

    getToken_CMockExpectAndReturn(215, &expression, (Token*)&three);

 getToken_CMockExpectAndReturn(216, &expression, (Token*)&Multi);

 getToken_CMockExpectAndReturn(217, &expression, (Token*)&five);

    getToken_CMockExpectAndReturn(218, &expression, (Token*)&Plus);

 getToken_CMockExpectAndReturn(219, &expression, (Token*)&six);



 result = evaluate(&expression);



}
