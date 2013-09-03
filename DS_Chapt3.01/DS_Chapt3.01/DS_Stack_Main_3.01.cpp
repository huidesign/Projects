#include "DS_OP_Stack.h"

void print(SElemType c)
{
	printf("%d ", c);
}

int main()
{
	int j;
	SqStack s = (SqStack)malloc(sizeof(SQStack));	//this is the key point, allocate space for SqStack
	SElemType e;
	InitStack(s);
	for(j = 1; j <= 12; j++)
		Push(s, j);
	printf("Elements in Stack is: ");
	StackTraverse(s, print);
	Pop(s, &e);
	printf("µ¯³öÕ»¶¥ÔªËØÎª: e = %d\n", e);
	printf("Õ»¿Õ·ñ: %d(1:¿Õ 0:·Ç¿Õ)", StackEmpty(s));
	GetTop(s, &e);
	printf("Õ»¶¥ÔªËØ e = %d Õ»µÄ³¤¶È %d\n", e, StackLength(s));
	ClearStack(s);
	printf("Çå¿ÕÕ»ºó£¬Õ»¿Õ·ñ: %d(1:¿Õ 0:·Ç¿Õ)\n", StackEmpty(s));
	DestroyStack(s);
	printf("ÏúÕ»ºó£¬s->top = %u s->base = %u s->stacksize = %d\n", 
		s->top, s->base, s->stacksize);
	
	system("PAUSE");
	return 0;
}