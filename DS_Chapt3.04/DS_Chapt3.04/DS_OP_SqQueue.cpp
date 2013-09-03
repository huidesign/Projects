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
	{/* �����������Ӵ�����Ԫ */
		Q->base = (QElemType *)realloc(Q->base, 
			(Q->queuesize + QUEUE_INCREMENT) * sizeof(QElemType));	/* ��=��д��==�ˣ����˰��� */
		if(!Q->base)
			exit(ERROR);
		if(Q->front > Q->rear)
		{/* ��Ϊ��ɾԪ�ص�Ե�ʣ�front��rearǰ��ʱ�轫front�Ժ��Ԫ�غ���QUEUE_INCREMENT��λ */
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