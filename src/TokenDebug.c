#include <stdio.h>
#include "NumberToken.h"
#include "OperatorToken.h"
#include "TokenDebug.h"
#include "Debug.h"
#include "Token.h"

void tokenDump(Token *token)
{
	OperatorInfo *info;
	if(token == NULL)
	{
		printf("token is NULL");
		return;
	}
	if(((Number *)token)->type == NUMBER_TOKEN)
	{
		printf("Number Token = %d\n", ((Number *)token)->value);
	}
	else if(((Operator *)token)->type == OPERATOR_TOKEN)
	{
		printf("Operator Token = %s\n", (((Operator *)token)->info)->name);
	}

}