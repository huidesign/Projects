#pragma once
#ifndef _DS_STACK_H
#define	_DS_STACK_H

#define STACK_INIT_SIZE	10
#define STACK_INCREMENT	2
#define SElemType int

struct SQStack {
	SElemType	*base;
	SElemType	*top;
	int	stacksize;
};
typedef struct SQStack *SqStack;

#endif