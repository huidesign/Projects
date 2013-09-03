#include "DS_OP_Stack.h"

void InitStack(SqStack s)
{
	s->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if(!s->base)
		exit(OVERFLOW);
	s->top = s->base;
	s->stacksize = STACK_INIT_SIZE;
}

void DestroyStack(SqStack s)
{
	free(s->base);
	s->base = NULL;
	s->top = NULL;
	s->stacksize = 0;
}

void ClearStack(SqStack s)
{
	s->top = s->base;
}

Status StackEmpty(const SqStack s)
{
	if(s->top == s->base)
		return TRUE;
	else
		return FALSE;
}

int StackLength(const SqStack s)
{
	return s->stacksize;
}

Status GetTop(const SqStack s, SElemType *e)
{
	if(s->top > s->base)
	{
		*e = *(s->top - 1);
		return OK;
	}
	else
		return ERROR;
}

void Push(SqStack s, const SElemType e)
{
	if((s->top - s->base) >= s->stacksize)
	{
		s->base = (SElemType *)realloc(s->base,
			(s->stacksize + STACK_INCREMENT) * sizeof(SElemType));
		if(!s->base)
			exit(OVERFLOW);
		s->top = s->base + s->stacksize;
		s->stacksize += STACK_INCREMENT;
	}
	*(s->top)++ =e;
}

Status Pop(SqStack s, SElemType *e)
{
	if(s->top == s->base)
		return ERROR;
	*e = *--s->top;
	return OK;
}

void StackTraverse(const SqStack s, void (*visit)(SElemType))
{
	int i, j = s->top - s->base;
	for(i = 0; i < j; i++)
		visit(*(s->base + i));
	printf("\n");
}