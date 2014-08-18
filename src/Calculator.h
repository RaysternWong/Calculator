#ifndef Calculator_H
#define Calculator_H

#include "Evaluate.h"
#include "Token.h"
#include "TokenDebug.h"
#include "Stack.h"
#include "StringObject.h"
#include "OperatorToken.h"
#include "NumberToken.h"
#include "Operator.h"
#include "IdentifierToken.h"
#include "ErrorCode.h"
#include "CException.h"

int Calculator(String *expression);
#endif // Calculator_H
