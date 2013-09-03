#include "DS_OP_SqQueue.h"

void InitQueue(SqQueuePt Q)
{
	Q->base = (QElemType *)malloc(MAX_QSIZE * sizeof(QElemType));
	if(!Q->base)
		exit(OVERFLOW);
	Q->front = Q->rear = 0;
}

void DestroyQueue(SqQueuePt Q)
{
	if(Q->base)
		free(Q->base);
	Q->base = NULL;
	Q->front = Q->rear = 0;
}

void ClearQueue(SqQueuePt Q)
{
	Q->front = Q->front = 0;
}

Status QueueEmpty(const SqQueuePt Q)
{
	if(Q->front == Q->rear)
		return TRUE;
	else
		return FALSE;
}

int QueueLength(const SqQueuePt Q)
{
	return (Q->rear - Q->front + MAX_QSIZE) % MAX_QSIZE;
}

Status GetHead(const SqQueuePt Q, QElemType *e)
{
	if(Q->rear == Q->front)
		return ERROR;
	*e = Q->base[Q->front];
	return OK;
}

Status EnQueue(SqQueuePt Q, QElemType e)
{
	 if((Q->rear + 1) % MAX_QSIZE == Q->front)	/* 队列满 */
		 return ERROR;
	 Q->base[Q->rear] = e;
	 Q->rear = ((Q->rear + 1) % MAX_QSIZE);		/* 循环队列的front数值可以小于rear数值，必须取模计算 */
	 return OK;
}

Status DeQueue(SqQueuePt Q, QElemType *e)
{
	if(Q->rear == Q->front)
		return ERROR;
	*e = Q->base[Q->front];
	Q->front = ((Q->front + 1) % MAX_QSIZE);
}

void QueueTraverse(const SqQueuePt Q, void (*vi)(QElemType))
{
	int i = Q->front;
	while (i != Q->rear)
	{
		vi(Q->base[i]);
		i = (i + 1) % MAX_QSIZE;
	}
	printf("\n");
}