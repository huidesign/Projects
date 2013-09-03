#pragma once
#ifndef _DS_OP_LINKQUEUE
#define _DS_OP_LINKQUEUE
#include "DS_Share.h"
#include "DS_LinkQueue.h"

void InitQueue(LinkQueue *Q);
void DestroyQueue(LinkQueue *Q);
void ClearQueue(LinkQueue *Q);
Status QueueEmpty(const LinkQueue *Q);
int QueueLength(const LinkQueue *Q);
Status GetHead_Q(const LinkQueue *Q, QElemType *e);
void EnQueue(LinkQueue *Q, const QElemType e);
Status DeQueue(LinkQueue *Q, QElemType *e);
void QueueTraverse(const LinkQueue *Q, void (*vi)(QElemType));

#endif