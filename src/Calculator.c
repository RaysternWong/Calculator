#include "Calculator.h"


/*
  This function is the combination of the ShuntingYard algorithm and getToken
  Input:
    - String *expression
  Output:
    - the result that is being returned
*/
int Calculator(String *expression)
{
	int result;

	result = evaluate(expression);
	return result;
}