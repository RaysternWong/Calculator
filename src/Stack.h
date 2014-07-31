#ifndef Stack_H
#define Stack_H
#include "ErrorCode.h"

typedef struct
{
	void **buffer;
	int size;
	int length;
}Stack;


Stack *stackNew(int lengthOfStack);
void stackPush(Stack *stackPtr, void *element);
void *stackPop(Stack *stackPtr);
int stackisEmpty(Stack *stackPtr);
int stackisFull(Stack *stackPtr);
void stackDel(Stack *stack);
void *stackPeep(Stack *stackPtr);

#endif // stack_H