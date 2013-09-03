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
	printf("����ջ��Ԫ��Ϊ: e = %d\n", e);
	printf("ջ�շ�: %d(1:�� 0:�ǿ�)", StackEmpty(s));
	GetTop(s, &e);
	printf("ջ��Ԫ�� e = %d ջ�ĳ��� %d\n", e, StackLength(s));
	ClearStack(s);
	printf("���ջ��ջ�շ�: %d(1:�� 0:�ǿ�)\n", StackEmpty(s));
	DestroyStack(s);
	printf("��ջ��s->top = %u s->base = %u s->stacksize = %d\n", 
		s->top, s->base, s->stacksize);
	
	system("PAUSE");
	return 0;
}