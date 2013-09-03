#include "DS_OP_SqQueue.h"

void InitQueue(SqQueuePt Q)
{
	Q->base = (QElemType *)malloc(QUEUE_INIT_SIZE * sizeof(QElemType));
	if(!Q->base)
		exit(ERROR);
	Q->front = Q->rear = 0;
	Q->queuesize = QUEUE_INIT_SIZE;
}

void DestroyQueue(SqQueuePt Q)
{
	if(Q->base)
		free(Q->base);
	Q->base = NULL;
	Q->front = Q->rear = Q->queuesize = 0;
}

void ClearQueue(SqQueuePt Q)
{
	Q->front = Q->rear = 0;
}

Status QueueEmpty(const SqQueuePt Q)
{
	if(Q->front == Q->rear)
		return TRUE;
	else
		return FALSE;
}

Status GetHead(const SqQueuePt Q, QElemType *e)
{
	if(Q->front == Q->rear)
		return ERROR;
	*e = Q->base[Q->front];
	return OK;
}

int QueueLength(const SqQueuePt Q)
{
	return (Q->rear - Q->front + Q->queuesize) % Q->queuesize;
}

void EnQueue(SqQueuePt Q, QElemType e)
{
	int i;
	if((Q->rear + 1) % Q->queuesize == Q->front)
	{/* 队列满，增加存贮单元 */
		Q->base = (QElemType *)realloc(Q->base, 
			(Q->queuesize + QUEUE_INCREMENT) * sizeof(QElemType));	/* 将=号写成==了，查了半天 */
		if(!Q->base)
			exit(ERROR);
		if(Q->front > Q->rear)
		{/* 因为增删元素的缘故，front在rear前面时需将front以后的元素后移QUEUE_INCREMENT单位 */
			for(i = Q->queuesize - 1; i >= Q->front; i--)
				Q->base[i + QUEUE_INCREMENT] = Q->base[i];
			Q->front += QUEUE_INCREMENT;
		}
		Q->queuesize += QUEUE_INCREMENT;
	}
	Q->base[Q->rear] = e;
	Q->rear = ++Q->rear % Q->queuesize;
}

Status DeQueue(SqQueuePt Q, QElemType *e)
{
	if(Q->front == Q->rear)
		return ERROR;
	*e = Q->base[Q->front];
	Q->front = ++Q->front % Q->queuesize;
	return OK;
}

void QueueTraverse(const SqQueuePt Q, void (*vi)(QElemType))
{
	int i = Q->front;
	while(i != Q->rear)
	{
		vi(Q->base[i]);
		i = ++i % Q->queuesize;
	}
	printf("\n");
}