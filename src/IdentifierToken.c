#include "IdentifierToken.h"
#include "Token.h"
#include <malloc.h>
#include <stdio.h>

/* Create a new Identifier token
 * input :
 *			name is the identifier name
 * return :
 *			identifier token
 */
Identifier *identifierNew(char *name)
{
	Identifier *iden = malloc(sizeof(Identifier)); //*iden = identifier pointer
	iden->type = IDENTIFIER_TOKEN;
	iden->name = name;
	
	return iden;
}

/* Delete operator token
 * input :
 *			Operator pointer pointing operator token structure
 * output :
 *			clear operator token value and free the memory allocated
 */
void identifierDel(Identifier *iden)
{
	if(iden)
		free(iden);
}