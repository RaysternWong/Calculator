#include "Stack.h"
#include <malloc.h>
#include <stdio.h>
#include "CException.h"

Stack *stackNew(int lengthOfStack){

	Stack *stack = malloc(sizeof(Stack));
	stack->buffer = malloc(sizeof(void*) * lengthOfStack);
	stack->size = 0;
	stack->length = lengthOfStack;

	return stack;
}

void stackPush(Stack *stackPtr, void *element)
{
	stackPtr->buffer[stackPtr->size] = element ;
	stackPtr->size++;

	if(stackisFull(stackPtr))
		Throw(ERR_STACK_FULL);
}

void *stackPop(Stack *stackPtr)
{
	void *Pop;

	if(stackisEmpty(stackPtr))
		return NULL;
   	
    Pop = stackPtr->buffer[stackPtr->size-1];
	stackPtr->size--;

	return Pop;
}

void *stackPeep(Stack *stackPtr){

  void *Peep;
  
  if(stackisEmpty(stackPtr))
		return NULL;
  
  Peep = stackPtr->buffer[stackPtr->size-1];
  
  return Peep;
}

int stackisFull(Stack *stackPtr)
{
	if(stackPtr->size > stackPtr->length)
		return 1;
	else
		return 0;
}


int stackisEmpty(Stack *stackPtr)
{
	if(stackPtr->size == 0)
		return 1;
	else	
		return 0;
}

void stackDel(Stack *stack)
{
	free(stack);
}