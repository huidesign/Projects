#pragma once
#ifndef _DS_LINKQUEUE
#define _DS_LINKQUEUE

typedef int QElemType;

struct QNode {
	QElemType data;
	struct QNode *next;
};

typedef struct QNode QNode, *QueuePtr;

typedef struct {
	QueuePtr front, rear;
	int queuesize;
}LinkQueue;

#endif