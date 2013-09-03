#include "DS_OP_LinkQueue.h"

void InitQueue(LinkQueue *Q)
{
	Q->front = (QueuePtr)malloc(sizeof(QNode));
	Q->rear = Q->front;
	if(!Q->front)
		exit(OVERFLOW);
	Q->front->next = NULL;
	Q->queuesize = 0;
}

void DestroyQueue(LinkQueue *Q)
{
	while(Q->front)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	Q->queuesize = 0;
}

void ClearQueue(LinkQueue *Q)
{	/* 带头节点？ */
	QueuePtr p, q;
	Q->rear = Q->front;
	p = Q->front->next;
	Q->front->next = NULL;
	while(p)
	{
		q = p;
		p = p->next;
		free(q);
	}
	Q->queuesize = 0;
}

Status QueueEmpty(const LinkQueue *Q)
{
	if(Q->front->next == NULL)
		return TRUE;
	else
		return FALSE;
}

int QueueLength(const LinkQueue *Q)
{
	return Q->queuesize;
}

Status GetHead_Q(const LinkQueue *Q, QElemType *e)
{
	QueuePtr p;
	if(Q->front == Q->rear)
		return ERROR;
	p=Q->front->next;
	*e = p->data;
	return OK;
}

void EnQueue(LinkQueue *Q, const QElemType e)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	Q->queuesize++;
}

Status DeQueue(LinkQueue *Q, QElemType *e)
{
	QueuePtr p;
	if(Q->front == Q->rear)
		return ERROR;
	p = Q->front->next;
	*e = p->data;
	Q->front->next = p->next;
	Q->queuesize--;
	if(Q->rear == p)
		Q->rear = Q->front;
	free(p);
	return OK;
}

void QueueTraverse(const LinkQueue *Q, void (*vi)(QElemType))
{
	QueuePtr p;
	p = Q->front->next;
	while(p)
	{
		vi(p->data);
		p = p->next;
	}
	printf("\n");
}