#pragma once
#ifndef _DS_OP_SQQUEUE_H
#define _DS_OP_SQQUEUE_H
#include "DS_Share.h"
#include "DS_Queue.h"
void InitQueue(SqQueuePt Q);
void DestroyQueue(SqQueuePt Q);
void ClearQueue(SqQueuePt Q);
Status QueueEmpty(const SqQueuePt Q);
Status GetHead(const SqQueuePt Q, QElemType *e);
int QueueLength(const SqQueuePt Q);
void EnQueue(SqQueuePt Q, QElemType e);
Status DeQueue(SqQueuePt Q, QElemType *e);
void QueueTraverse(const SqQueuePt Q, void (*vi)(QElemType));
#endif