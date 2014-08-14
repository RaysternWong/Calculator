#include "Token.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "StringObject.h"
#include "NumberToken.h"
#include "OperatorToken.h"
#include "IdentifierToken.h"
#include "ErrorCode.h"
#include "CException.h"

/* To extract out number token , identifier token or operator token from the expression string
 * input :
 *			expression is the string that we wanted to extract the token
 * output :
 *			return number token if number is found in string
 *			return idendifier token if identifier is found in string
 * 			return operator token if operator is found in string
 */
Token *getToken(String *expression)
{	
	Number *num;
	Identifier *iden;
	Operator *op;
	int tempStart = 0 , tempLength = 0;
	char *tempIden; //temporary store idendifier name
	stringTrim(expression);	//Remove all the spaces in string

	/*Character at first position*/
	int charAtThisPos = expression->startindex;

	//if character start with numbers it is number token
	if(stringCharAtInSet(expression , charAtThisPos , numSet))
	{	
		String *removedWord = stringRemoveWordContaining (expression , numSet);	//Remove numbers in string
		tempStart = removedWord->startindex;
		tempLength = removedWord->length;
		char *numSubString = stringSubStringInChars(removedWord , removedWord->length); //Removed numbers become substring
		charAtThisPos = expression->startindex;
		
		if(stringCharAtInSet(expression , charAtThisPos , alphaSet))
			Throw(ERR_NOT_NUMBER_TOKEN);
		
		int integer = subStringToInteger(numSubString); //Convert substring to integer
		num = numberNew(integer); //get integer from subStringToInteger and create a new Number Token
		num->line = stringSubString(expression , tempStart , tempLength);

		return (Token*)num;
	}
	
	//if character start with A~Z/a~z or '_' it is identifier token
	else if(stringCharAtInSet(expression , charAtThisPos , alphaNumericSet)) 
	{
		String *removedWord = stringRemoveWordContaining (expression , alphaNumericSet); //Remove identifier from string
		tempStart = removedWord->startindex;
		tempLength = removedWord->length;
		char *idenSubString = stringSubStringInChars(removedWord , removedWord->length); //Removed identifier become substring
		iden = identifierNew(idenSubString); //create a new identifier token
		iden->line = stringSubString(expression , tempStart , tempLength);
		
		return (Token*)iden;
	}
	
	// if character not start with A~Z/a~z , '_' or numbers it is operator token
	else if(stringCharAtInSet(expression , charAtThisPos , opSet)) 
	{
		String *removedWord = stringRemoveOperator(expression , opSet); //Remove operator in string
		tempStart = removedWord->startindex;
		tempLength = removedWord->length;
		char *opSubString = stringSubStringInChars(removedWord , removedWord->length); //Removed operator become substring	
		op = operatorNewByName(opSubString);
		op->line = stringSubString(expression , tempStart , tempLength);
		
		return (Token*)op;
	}
	
	
}
