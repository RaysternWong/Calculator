#ifndef IdentifierToken_H
#define IdentifierToken_H
#include "Token.h"
#include "StringObject.h"

typedef struct
{
	TokenType type;
	char *name;
	String *line;
}Identifier;

Identifier *identifierNew(char *name);
void identifierDel(Identifier *iden);
#endif // IdentifierToken_H
