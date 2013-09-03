#pragma once
#ifndef	_DS_OP_STACK_H
#define	_DS_OP_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "DS_Share.h"
#include "DS_Stack.h"

void InitStack(SqStack s);
void DestroyStack(SqStack s);
void ClearStack(SqStack s);
Status StackEmpty(const SqStack s);
int StackLength(const SqStack s);
Status GetTop(const SqStack s, SElemType *e);
void Push(SqStack s, const SElemType e);
Status Pop(SqStack s, SElemType *e);
void StackTraverse(const SqStack s, void (*visit)(SElemType));

#endif