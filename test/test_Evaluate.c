#include "unity.h"
#include "Evaluate.h"
#include "mock_Token.h"
#include "mock_StringObject.h"
#include <string.h>
#include "Stack.h"
#include "OperatorToken.h"
#include "NumberToken.h"
#include "Operator.h"
#include "TokenDebug.h"
#include "ErrorCode.h"
#include "CException.h"


#define STACK_LENGTH 100

void setUp(void){}

void tearDown(void){}


void test_tryToPushOperatorAndEvaluate_given_plus_should_push_to_stack(void){

	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack	 = stackNew(STACK_LENGTH) ;
	Operator *Plus		 = operatorNewByName("+");
	Operator *ptrOpr;

	tryToPushOperatorAndEvaluate( Plus , operatorStack, dataStack );
	TEST_ASSERT_EQUAL_PTR ( Plus, (Operator *)stackPop( operatorStack));
	TEST_ASSERT_NULL ( (Number *)stackPop( dataStack ) );
}

void test_tryToPushOperatorAndEvaluate_given_2_Plus_4_Plus_should_answer_the_token_six(void){

	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	 = stackNew(STACK_LENGTH);
	Operator *Plus1		 = operatorNewByName("+");
	Operator *Plus2		 = operatorNewByName("+");
	Operator *op;
	Number *two = numberNew(2);
	Number *four = numberNew(4);
	Number *num;

	//2+4+ same predecedence
	stackPush( dataStack , two );
	stackPush( dataStack , four );
	stackPush( operatorStack , Plus1 );
	tryToPushOperatorAndEvaluate( Plus2 , operatorStack, dataStack );

	num = (Number *)stackPop( dataStack );
	TEST_ASSERT_NOT_NULL ( num );
	TEST_ASSERT_EQUAL (	NUMBER_TOKEN, num->type);
	TEST_ASSERT_EQUAL ( 6 , num->value );
  TEST_ASSERT_NULL ( (Number *)stackPop( dataStack ) );

	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
	TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( ADD_OP , op->info->id );
	TEST_ASSERT_NULL ( (Operator *)stackPop( operatorStack ) );
}

void test_tryToPushOperatorAndEvaluate_given_2_Plus_4_Multi_should_answer_the_token_four(void){


	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	 = stackNew(STACK_LENGTH);
	Operator *Plus		 = operatorNewByName("+");
	Operator *Multi		 = operatorNewByName("*");
	Operator *op;
	Number *two = numberNew(2);
	Number *four = numberNew(4);
	Number *num;

	//2+4* higher precedence
	stackPush( dataStack , two );
	stackPush( dataStack , four );
	stackPush( operatorStack , Plus );
	tryToPushOperatorAndEvaluate( Multi , operatorStack, dataStack );

	num = (Number *)stackPop( dataStack );
	TEST_ASSERT_NOT_NULL ( num );
	TEST_ASSERT_EQUAL (	NUMBER_TOKEN, num->type);
	TEST_ASSERT_EQUAL ( 4 , num->value );

  num = (Number *)stackPop( dataStack );
	TEST_ASSERT_NOT_NULL ( num );
	TEST_ASSERT_EQUAL (	NUMBER_TOKEN, num->type);
	TEST_ASSERT_EQUAL ( 2 , num->value );
  num = (Number *)stackPop( dataStack );
	TEST_ASSERT_NULL ( num );

	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
	TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( MUL_OP , op->info->id );

	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
	TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( ADD_OP , op->info->id );

	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NULL ( op );
}

void test_tryToPushOperatorAndEvaluate_given_bracket_bracket_put_into_stack(void){

  Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	 = stackNew(STACK_LENGTH);
	Operator *openBracket1	 = operatorNewByName("(");
	Operator *openBracket2	 = operatorNewByName("(");

  stackPush( operatorStack , openBracket1 );
	tryToPushOperatorAndEvaluate(openBracket2 , operatorStack, dataStack );

  Operator *op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( OPEN_BRACKET , op->info->id );
  
  op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( OPEN_BRACKET , op->info->id );
}

void test_tryToPushOperatorAndEvaluate_given_2_Plus_4_Multi_5_Plus_should_answer_the_token_twenty_two(void){


	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	 = stackNew(STACK_LENGTH);
	Operator *Plus1		 = operatorNewByName("+");
	Operator *Plus2		 = operatorNewByName("+");
	Operator *Multi		 = operatorNewByName("*");
	Operator *op;
	Number *two  = numberNew(2);
	Number *four = numberNew(4);
	Number *five = numberNew(5);
	Number *num;

	//2+4*5+ same precedence
	stackPush( dataStack , two );
	stackPush( dataStack , four );
	stackPush( dataStack , five );
	stackPush( operatorStack , Plus1 );
	stackPush( operatorStack , Multi );

	tryToPushOperatorAndEvaluate(Plus2 , operatorStack, dataStack );

	num = (Number *)stackPop( dataStack );
	TEST_ASSERT_NOT_NULL ( num );
	TEST_ASSERT_EQUAL (	NUMBER_TOKEN, num->type);
	TEST_ASSERT_EQUAL ( 22 , num->value );
	TEST_ASSERT_NULL ( (Number *)stackPop( dataStack ) );

	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( ADD_OP , op->info->id );
  TEST_ASSERT_NULL ( (Operator *)stackPop( operatorStack ) );
}

void test_tryToPushOperatorAndEvaluate_given_2_Plus_13_Multi_7_AND_should_answer_the_token_ninety_three(void){


	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	   = stackNew(STACK_LENGTH);
	Operator *Plus		   = operatorNewByName("+");
	Operator *BIT_AND    = operatorNewByName("&");
	Operator *Multi		   = operatorNewByName("*");
	Operator *op;
	Number *two       = numberNew(2);
	Number *thirteen  = numberNew(13);
	Number *seven     = numberNew(7);
	Number *num;

	//2+13*7& same precedence
	stackPush( dataStack , two );
	stackPush( dataStack , thirteen );
	stackPush( dataStack , seven );
  stackPush( operatorStack , Plus );
	stackPush( operatorStack , Multi );

	tryToPushOperatorAndEvaluate( BIT_AND , operatorStack, dataStack );

	num = (Number *)stackPop( dataStack );
	TEST_ASSERT_NOT_NULL ( num );
	TEST_ASSERT_EQUAL (	NUMBER_TOKEN, num->type);
	TEST_ASSERT_EQUAL ( 2+(13*7) , num->value );
	TEST_ASSERT_NULL ( (Number *)stackPop( dataStack ) );

	op = (Operator *)stackPop( operatorStack );
	TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( BITWISE_AND_OP , op->info->id );
  TEST_ASSERT_NULL ( (Operator *)stackPop( operatorStack ) );
}

void test_doOperatorStackRewinding_given_2_and_3_plus_4_multi_5_should_get_correct_result(void){

	Stack *operatorStack = stackNew(STACK_LENGTH);
	Stack *dataStack 	   = stackNew(STACK_LENGTH);
  Number *two   = numberNew(2);
	Number *three = numberNew(3);
  Number *four  = numberNew(4);
  Number *five  = numberNew(5);
  Number *num;
	Operator *plus		 = operatorNewByName("+");
  Operator *and 		 = operatorNewByName("&");
	Operator *multi		 = operatorNewByName("*");
  Operator *op;
  
  //2&3+4*5
  stackPush( dataStack , two );
	stackPush( dataStack , three);
	stackPush( dataStack , four );
  stackPush( dataStack , five );
  stackPush( operatorStack , and );
  stackPush( operatorStack , plus );
	stackPush( operatorStack , multi );

  doOperatorStackRewinding ( dataStack , operatorStack );
  
  num = (Number *)stackPop( dataStack );
  TEST_ASSERT_NOT_NULL ( num );
	TEST_ASSERT_EQUAL (	NUMBER_TOKEN, num->type);
	TEST_ASSERT_EQUAL ( 2&3+4*5 , num->value );
  TEST_ASSERT_NULL ( (Number *)stackPop( dataStack ) );
}

void test_evalauatePostfixesAndInfix_given_string_below_should_put_into_stack(void){
  
  int Result;
  Stack *dataStack       = stackNew(STACK_LENGTH);
	Stack *operatorStack   = stackNew(STACK_LENGTH);
  Number *two            = numberNew(2);
  Operator *openBracket  = operatorNewByName("(");
  Operator *closeBracket = operatorNewByName(")");
  Operator *op;
  String expression  = {.string="(2    )"};
    
  stackPush(operatorStack,openBracket);
  stackPush(dataStack    ,two);  
  getToken_ExpectAndReturn(&expression, NULL  );
  evalauatePostfixesAndInfix((Token*)closeBracket , &expression, operatorStack, dataStack);
    
  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( CLOSE_BRACKET , op->info->id );
  
  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( OPEN_BRACKET , op->info->id );

  TEST_ASSERT_NULL ( stackPop( operatorStack ));
 
}

void test_evalauatePostfixesAndInfix_given_5_should_get_throw_exception(void){

  CEXCEPTION_T err;
  Stack *dataStack     = stackNew(STACK_LENGTH);
	Stack *operatorStack = stackNew(STACK_LENGTH);
  Number *five   = numberNew(5);
  Number *two    = numberNew(2);
  
  String expression  = {.string="2 5"};
  

  stackPush (dataStack, two); 
  
  
  Try{
         evalauatePostfixesAndInfix((Token*)five, &expression,  operatorStack,  dataStack);
         TEST_FAIL_MESSAGE("should throw ERR_NOT_EXPECTING_NUMBER exception");
  } Catch (err)
  {    
      TEST_ASSERT_EQUAL_MESSAGE( ERR_NOT_EXPECTING_NUMBER , err , "Expected ERR_NOT_EXPECTING_NUMBER exception"); }
      
      
 }
 
 void test_evalauatePostfixesAndInfix_given_1plus5_multi_should_put_into_stack(void){
  
  int Result;
  Stack *dataStack       = stackNew(STACK_LENGTH);
	Stack *operatorStack   = stackNew(STACK_LENGTH);
  Number *one            = numberNew(1);
  Number *five           = numberNew(5);
  Operator *plus  = operatorNewByName("+");
  Operator *multi = operatorNewByName("*");
  Operator *op;
  String expression  = {.string="1+5 *"};
    
  stackPush(dataStack    ,one);
  stackPush(operatorStack,plus ); 
  stackPush(dataStack    ,five);  

  getToken_ExpectAndReturn(&expression, NULL  );
  
  evalauatePostfixesAndInfix((Token*)multi , &expression, operatorStack, dataStack);
    
  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
  TEST_ASSERT_EQUAL (	multi, op);
  
  Number *num = (Number *)stackPop( dataStack );
  TEST_ASSERT_EQUAL (	5 , num->value); 
  TEST_ASSERT_NOT_NULL ( stackPop( operatorStack ));
 
}
 

void test_evalauatePostfixesAndInfix_bracket_2_should_put_into_stack(void){
  
  int Result;
  Stack *dataStack       = stackNew(STACK_LENGTH);
	Stack *operatorStack   = stackNew(STACK_LENGTH);
  Number *two            = numberNew(2);
  Operator *openBracket  = operatorNewByName("(");
  Operator *closeBracket = operatorNewByName(")");
  Operator *op;
  String expression  = {.string="(2    )"};
    
  stackPush(operatorStack,openBracket);
  stackPush(dataStack    ,two);  
  
  getToken_ExpectAndReturn(&expression, NULL  );
  evalauatePostfixesAndInfix((Token*)closeBracket , &expression, operatorStack, dataStack);
    
  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( CLOSE_BRACKET , op->info->id );
  
  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( OPEN_BRACKET , op->info->id );

  TEST_ASSERT_NULL ( stackPop( operatorStack ));
 
}

void test_evalauatePostfixesAndInfix_given_plus_should_put_into_stack(void){
  
  int Result;
  Stack *dataStack       = stackNew(STACK_LENGTH);
	Stack *operatorStack   = stackNew(STACK_LENGTH);
  Number *two            = numberNew(2);
  Operator *plus		     = operatorNewByName("+");
  Operator *openBracket  = operatorNewByName("(");
  Operator *closeBracket = operatorNewByName(")");
  Operator *op;
  String expression  = {.string="(2    )+"};
    
  stackPush(operatorStack,openBracket);
  stackPush(dataStack    ,two);
  
  getToken_ExpectAndReturn(&expression, (Token*)plus  );
  getToken_ExpectAndReturn(&expression, NULL  );
  
  evalauatePostfixesAndInfix((Token*)closeBracket , &expression, operatorStack, dataStack);
  
  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( ADD_OP , op->info->id );
  
  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( CLOSE_BRACKET , op->info->id );
  
  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( OPEN_BRACKET , op->info->id );

  TEST_ASSERT_NULL ( stackPop( operatorStack ));
 
}




void test_evalauatePostfixesAndInfix_given_bracket_bracket_2_bracket_bracket_minus_should_put_into_stack(void){
  
  int Result;
  Stack *dataStack       = stackNew(STACK_LENGTH);
	Stack *operatorStack   = stackNew(STACK_LENGTH);
  Number *two            = numberNew(2);
  Operator *openBracket1  = operatorNewByName("(");
  Operator *openBracket2  = operatorNewByName("(");
  Operator *closeBracket1 = operatorNewByName(")");
  Operator *closeBracket2 = operatorNewByName(")");
  Operator *op;

  String expression  = {.string=" ((2   ))"};
    
  stackPush(operatorStack,openBracket1);
  stackPush(operatorStack,openBracket2);
  stackPush(dataStack    ,two);
 
  getToken_ExpectAndReturn(&expression, (Token*)closeBracket1	  );
  getToken_ExpectAndReturn(&expression, NULL  );
  
  evalauatePostfixesAndInfix((Token*)closeBracket2, &expression, operatorStack, dataStack);
  
  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( CLOSE_BRACKET , op->info->id );
  
  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( CLOSE_BRACKET , op->info->id );
  
  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( OPEN_BRACKET , op->info->id );
  
  op = (Operator *)stackPop( operatorStack );
  TEST_ASSERT_NOT_NULL ( op );
  TEST_ASSERT_EQUAL (	OPERATOR_TOKEN, op->type);
	TEST_ASSERT_EQUAL ( OPEN_BRACKET , op->info->id );
  
  TEST_ASSERT_NULL ( stackPop( operatorStack ));
}

// test whether the minus that is infix got change to prefix or not
void test_convertToPrefixIfNotAlready_given_infix_minus_should_be_able_to_convert_to_prefix(void) {
  OperatorInfo *info = getOperatorByID(SUB_OP);
  Operator operator = {.type = OPERATOR_TOKEN, info};
  
  Token *token = convertToPrefixIfNotAlready(&operator);
  Operator *operate = (Operator *)token;
  TEST_ASSERT_EQUAL(PREFIX, operate->info->affix);
}

// test given multiply should throw an exception due to multiply is not in secondaryOperatorTable
// void test_convertToPrefixIfNotAlready_given_infix_multiply_should_throw_an_exception(void) {
  // OperatorInfo *info = getOperatorByID(MUL_OP);
  // Operator operator = {.type = OPERATOR_TOKEN, info};
  // CEXCEPTION_T err;
  
  // Try {
    // Token *token = convertToPrefixIfNotAlready(&operator);
    // Operator *operate = (Operator *)token;
    // TEST_FAIL_MESSAGE("Should throw an exception due to ERR_NOT_PREFIX_OPERATOR");
  // } Catch(err) {
      // TEST_ASSERT_EQUAL_MESSAGE(ERR_NOT_PREFIX_OPERATOR, err, "Expected ERR_NOT_PREFIX_OPERATOR");
    // }
// }