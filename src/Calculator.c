#include "Calculator.h"
#include "command_prompt.h"
#include "history_buffer.h"
#include "get_ch.h"
#include "putch.h"
#include "Evaluate.h"
#include "Token.h"
#include "TokenDebug.h"
#include "Stack.h"
#include "StringObject.h"
#include <stdlib.h>
#include <string.h>
#include "OperatorToken.h"
#include "NumberToken.h"
#include "Operator.h"
#include "IdentifierToken.h"
#include "ErrorCode.h"
#include "CException.h"
#include <stdio.h>
#include <malloc.h>


int Calculator(String *expression)
{
	int result;

	result = evaluate(expression);
	return result;
}