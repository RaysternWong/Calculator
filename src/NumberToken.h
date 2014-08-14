#ifndef NumberToken_H
#define NumberToken_H
#include "Token.h"
#include "StringObject.h"

typedef struct
{
	TokenType type;
	String *line;
	int value;
}Number;

Number *numberNew(int value);
void numberDel(Number *num);
#endif // NumberToken_H
