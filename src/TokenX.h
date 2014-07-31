#ifndef Token_H
#define Token_H
#include "StringObject.h"

typedef enum{UNKOWN, NUMBER_TOKEN, OPERATOR_TOKEN, IDENTIFIER_TOKEN} TokenType;

typedef enum{NO_ASSOCIATIVITY, LEFT_TO_RIGHT, RIGHT_TO_LEFT} AssocType;

typedef enum{PREFIX, INFIX, POSTFIX} Affix;

typedef enum{UNKNOWN_OP, ADD_OP, SUB_OP, MUL_OP, NPERCENT_OP, DIV_OP, OR_OP, XOR_OP, AND_OP, BITWISE_AND_OP, BITWISE_OR_OP} OperatorID;

typedef struct
{
	TokenType type;
} Token;

typedef struct
{
	TokenType type;
	int value;
} Number;

typedef struct
{
	char *name;
	OperatorID id;
	int precedence;
	AssocType associativity;
	Affix affix;
} OperatorInfo;

typedef struct
{
	TokenType type;
	OperatorInfo *info;
} Operator;

typedef struct
{
	TokenType type;
	char *name;
} Identifier;

Token *getToken(String *strings);


#endif // Token_H
