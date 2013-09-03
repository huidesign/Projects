#include "DS_OP_LinkQueue.h"

void print(QElemType e)
{
	printf("%d ", e);
}

int main()
{
	int i;
	QElemType d;
	LinkQueue q;
	InitQueue(&q);
	printf("�ɹ��ع�����һ��������!\n");
	printf("�����Ƿ�Ϊ�գ�%d(1:��0:��) ", QueueEmpty(&q));
	printf("���г���Ϊ%d\n", QueueLength(&q));
	EnQueue(&q, 5);
	EnQueue(&q, -5);
	EnQueue(&q, 10);
	printf("��������Ԫ��(5,-5,10)�󣬶��еĳ���Ϊ%d\n", QueueLength(&q));
	printf("�����Ƿ�Ϊ�գ�%d(1:��0:��) ", QueueEmpty(&q));
	printf("���е�Ԫ������Ϊ�� ");
	QueueTraverse(&q, print);
	i = GetHead_Q(&q, &d);
	if(i == OK)
		printf("��ͷԪ���ǣ� %d\n", d);
	DeQueue(&q, &d);
	printf("ɾ���˶�ͷԪ��: %d\n", d);
	i = GetHead_Q(&q, &d);
	if(i == OK)
		printf("�µĶ�ͷԪ���ǣ� %d\n", d);
	ClearQueue(&q);
	printf("��ն��к�: q.front = %u, q.rear = %u, \n"
		"            q.front->next = %u, q.queuesize = %d\n", 
		q.front, q.rear, q.front->next, q.queuesize);
	DestroyQueue(&q);
	printf("ɾ�����к�: q.front = %u, q.rear = %u, "
		" q.queuesize = %d\n", q.front, q.rear, q.queuesize);

	system("PAUSE");
	return 0;
}