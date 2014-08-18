#ifndef Token_H
#define Token_H
#include "StringObject.h"

typedef enum
{
	UNKNOWN,
	NUMBER_TOKEN,
	OPERATOR_TOKEN,
	IDENTIFIER_TOKEN
}TokenType;

typedef struct
{
	TokenType type;
}Token;

extern Token *currentToken;

Token *getToken(String *expression);
void tokenDisplay(Token *token);

#endif // Token_H
