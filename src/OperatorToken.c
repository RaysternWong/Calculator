#include "OperatorToken.h"
#include <malloc.h>
#include "ErrorCode.h"
#include "Operator.h"
#include <stdio.h>

/* Operator Table contain all the operator information
 */
OperatorInfo primaryOperatorTable[] = 
{
	{.name = "*", 	.id = MUL_OP, 			.precedence = 80, .associativity = LEFT_TO_RIGHT, .affix = INFIX, .execute = executeMul},
	{.name = "%", 	.id = NPERCENT_OP, 		.precedence = 80, .associativity = LEFT_TO_RIGHT, .affix = INFIX, .execute = executeModulo},
	{.name = "/", 	.id = DIV_OP, 			.precedence = 80, .associativity = LEFT_TO_RIGHT, .affix = INFIX, .execute = executeDiv},
	{.name = "+", 	.id = ADD_OP, 			.precedence = 70, .associativity = LEFT_TO_RIGHT, .affix = INFIX, .execute = executeAdd},
	{.name = "-", 	.id = SUB_OP, 			.precedence = 70, .associativity = LEFT_TO_RIGHT, .affix = INFIX, .execute = executeSub},
	{.name = "<<", 	.id = BITWISE_SHIFT_LEFT_OP, 	.precedence = 68, .associativity = LEFT_TO_RIGHT, .affix = INFIX, .execute = executeShiftLeft},
	{.name = ">>", 	.id = BITWISE_SHIFT_RIGHT_OP, 	.precedence = 68, .associativity = LEFT_TO_RIGHT, .affix = INFIX, .execute = executeShiftRight},
	{.name = "<", 	.id = LESSER_OP,		.precedence = 66, .associativity = LEFT_TO_RIGHT, .affix = INFIX, .execute = executeLesser},
	{.name = ">", 	.id = GREATER_OP, 		.precedence = 66, .associativity = LEFT_TO_RIGHT, .affix = INFIX, .execute = executeGreater},
	{.name = "==", 	.id = EQUAL_OP, 		.precedence = 64, .associativity = LEFT_TO_RIGHT, .affix = INFIX, .execute = executeEqual},
	{.name = "&", 	.id = BITWISE_AND_OP, 	.precedence = 60, .associativity = LEFT_TO_RIGHT, .affix = INFIX, .execute = executeBitAnd},
	{.name = "^", 	.id = XOR_OP, 			.precedence = 50, .associativity = LEFT_TO_RIGHT, .affix = INFIX, .execute = executeXor},
	{.name = "|", 	.id = BITWISE_OR_OP, 	.precedence = 40, .associativity = LEFT_TO_RIGHT, .affix = INFIX, .execute = executeBitOr},	
	{.name = "&&", 	.id = AND_OP, 			.precedence = 30, .associativity = LEFT_TO_RIGHT, .affix = INFIX, .execute = executeAnd},
	{.name = "||", 	.id = OR_OP, 			.precedence = 20, .associativity = LEFT_TO_RIGHT, .affix = INFIX, .execute = executeOr},
	{.name = ")", 	.id = CLOSE_BRACKET, 	.precedence = 10, .associativity = LEFT_TO_RIGHT, .affix = POSTFIX},
	{.name = "(", 	.id = OPEN_BRACKET, 	.precedence = 9,  .associativity = LEFT_TO_RIGHT, .affix = PREFIX}
};

/* Operator Table contain prefix operator "+" and "-" information
 */
OperatorInfo secondaryOperatorTable[] = 
{
	{.name = "+", 	.id = ADD_OP,			.precedence = 100,	.associativity = RIGHT_TO_LEFT,	.affix = PREFIX},
	{.name = "-", 	.id = SUB_OP,			.precedence = 100,	.associativity = RIGHT_TO_LEFT,	.affix = PREFIX},
	{.name = "!", 	.id = NOT_OP,			.precedence = 90,	.associativity = RIGHT_TO_LEFT,	.affix = PREFIX},
	{.name = "~", 	.id = BITWISE_NOT_OP,	.precedence = 90,	.associativity = RIGHT_TO_LEFT,	.affix = PREFIX}
};

/* Create new structure for operator (Identify by ID)
 * input :
 *			operator ID to indicate which operator is this
 * return :
 *			return the op pointer which is operatorToken
 */
Operator *operatorNewByID(OperatorID id)
{
	int i = 0;
	Operator *op = malloc(sizeof(Operator)); //*op = operator pointer
	op->type	 = OPERATOR_TOKEN;
	op->info = NULL;
	
	for(i ; i < PRIMARY_TABLE_SIZE ; i++)
	{
		if(primaryOperatorTable[i].id == id)
			op->info = &primaryOperatorTable[i];
	}
	
	return op;
}

/* Create new structure for operator (Identify by ID)
 * input :
 *			operator ID to indicate which operator is this
 * return :
 *			return the op pointer which is operatorToken
 */
Operator *operatorNewByName(char *name)
{
	int i = 0 , result;
	Operator *op = malloc(sizeof(Operator)); //*op = operator pointer
	op->type	 = OPERATOR_TOKEN;
	op->info = NULL;
	
	for(i ; i < PRIMARY_TABLE_SIZE ; i++)
	{
		result = strcmp(primaryOperatorTable[i].name, name);
		
		if(result == 0)
			op->info = &primaryOperatorTable[i];
	}
	
	return op;
}

/* Delete operator token
 * input :
 *			Operator pointer pointing operator token structure
 * output :
 *			clear operator token value and free the memory allocated
 */
void operatorDel(Operator *op)
{
	if(op)		
		free(op);
}

OperatorInfo *getOperatorByID(OperatorID id)
{
	int i = 0;
	OperatorInfo *info = NULL;
	for(i; i < PRIMARY_TABLE_SIZE; i++)
	{		
		if(primaryOperatorTable[i].id == id)
			return &primaryOperatorTable[i];
	}
}

OperatorInfo *getOperatorByName(char *name)
{
	int i = 0, result;
	OperatorInfo *info;
	for(i; i < PRIMARY_TABLE_SIZE; i++)
	{
		result = strcmp(primaryOperatorTable[i].name, name);
		if(result == 0)
		{
			return &primaryOperatorTable[i];
		}
	
	}
	return NULL;
}

OperatorInfo *getOperatorByIDInSecondaryTable(OperatorID id)
{
	int i = 0;
	OperatorInfo *info;
	for(i; i < SECONDARY_TABLE_SIZE; i++)
	{		
		if(secondaryOperatorTable[i].id == id)
			return &secondaryOperatorTable[i];
	}
	return NULL;
}

OperatorInfo *getOperatorByNameInSecondaryTable(char *name)
{
	int i = 0, result;
	OperatorInfo *info;
	for(i; i < SECONDARY_TABLE_SIZE; i++)
	{
		result = strcmp(secondaryOperatorTable[i].name, name);
		if(result == 0)
		{
			return &secondaryOperatorTable[i];
		}
	
	}
	return NULL;
}

Operator *operatorTryConvertToPrefix(Operator *operator)
{
	OperatorInfo *secondaryInfo = getOperatorByIDInSecondaryTable(operator->info->id);
	printf("%d\n\n" , secondaryInfo->id);	
	
	if(secondaryInfo != NULL)
	{
		operator->type = OPERATOR_TOKEN;
		operator->info = secondaryInfo;
		return operator;
	}
	
	return NULL;
}