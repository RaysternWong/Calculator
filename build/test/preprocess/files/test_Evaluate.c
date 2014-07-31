#include "unity.h"
#include "mock_Token.h"
#include "mock_StringObject.h"
#include "TokenDebug.h"
#include "Stack.h"
#include "OperatorToken.h"
#include "Operator.h"
#include "NumberToken.h"
#include "Evaluate.h"










void setUp(void){}



void tearDown(void){}









void test_tryToPushOperatorAndEvaluate_given_plus_should_push_to_stack(void){



 Stack *operatorStack = stackNew(100);

 Stack *dataStack = stackNew(100) ;

 Operator plus = {.type = OPERATOR_TOKEN, .info =getOperatorByID(ADD_OP) };

 Operator *ptrOpr;





 tryToPushOperatorAndEvaluate( operatorStack, &plus ,dataStack );

 ptrOpr = (Operator *)stackPop( operatorStack);



 UnityAssertEqualNumber((_U_SINT)(_UP)((&plus)), (_U_SINT)(_UP)((ptrOpr)), (((void *)0)), (_U_UINT)34, UNITY_DISPLAY_STYLE_HEX32);



}



void test_tryToPushOperatorAndEvaluate_given_plus_multi_should_push_to_stack(void){



 Stack *operatorStack = stackNew(100);

 Stack *dataStack = stackNew(100) ;

 Operator Plus = {.type = OPERATOR_TOKEN, .info =getOperatorByID(ADD_OP) };

 Operator Multi = {.type = OPERATOR_TOKEN, .info =getOperatorByID(MUL_OP) };



 tryToPushOperatorAndEvaluate( operatorStack, &Plus ,dataStack );

 tryToPushOperatorAndEvaluate( operatorStack, &Multi ,dataStack );



 UnityAssertEqualNumber((_U_SINT)(_UP)((&Multi)), (_U_SINT)(_UP)(((Operator *)stackPop( operatorStack))), (((void *)0)), (_U_UINT)48, UNITY_DISPLAY_STYLE_HEX32);

 UnityAssertEqualNumber((_U_SINT)(_UP)((&Plus)), (_U_SINT)(_UP)(((Operator *)stackPop( operatorStack))), (((void *)0)), (_U_UINT)49, UNITY_DISPLAY_STYLE_HEX32);



}

void xtest_evaluate_given_token_2plus3_should_get_5(void){



 int result;



 Number two ={.type = NUMBER_TOKEN, .value = 2};

 Number three ={.type = NUMBER_TOKEN, .value = 3};

 Operator Plus = {.type = OPERATOR_TOKEN, .info =getOperatorByID(ADD_OP) };

 String expression ={.string="2+3"};



 getToken_CMockExpectAndReturn(77, &expression, (Token*)&two);

 getToken_CMockExpectAndReturn(78, &expression, (Token*)&Plus);

    getToken_CMockExpectAndReturn(79, &expression, (Token*)&three);





 result = evaluate(&expression);





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



    getToken_CMockExpectAndReturn(98, &expression, (Token*)&two);

 getToken_CMockExpectAndReturn(99, &expression, (Token*)&Plus);

    getToken_CMockExpectAndReturn(100, &expression, (Token*)&three);

 getToken_CMockExpectAndReturn(101, &expression, (Token*)&Multi);

 getToken_CMockExpectAndReturn(102, &expression, (Token*)&five);

    getToken_CMockExpectAndReturn(103, &expression, (Token*)&Plus);

 getToken_CMockExpectAndReturn(104, &expression, (Token*)&six);



 result = evaluate(&expression);



}
