#ifndef NumberToken_H
#define NumberToken_H
#include "Token.h"

typedef struct
{
	TokenType type;
	int value;
}Number;

Number *numberNew(int value);
void numberDel(Number *num);
#endif // NumberToken_H
