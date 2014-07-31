#include "unity.h"
#include "TokenDebug.h"
#include "mock_Token.h"
#include "Operator.h"
#include "Stack.h"
#include "NumberToken.h"
#include "OperatorToken.h"

void setUp(void){}

void tearDown(void){}

void test_tokenDump_NUMBER_TOKEN_had_been_set_to_the_type_should_be_able_to_print_out_number(void)
{
	Number numberToken = {.type = NUMBER_TOKEN,
						  .value = 2};

		
	tokenDump((Token *)&numberToken);

}

void test_tokenDump_OPERATOR_TOKEN_had_been_set_to_the_type_should_be_able_to_print_out_operator(void)
{
	OperatorInfo *info = getOperatorByID(ADD_OP);
	Operator operatorToken = {.type = OPERATOR_TOKEN, info};
	
	tokenDump((Token *)&operatorToken);
}

