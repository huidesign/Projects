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
	printf("成功地构造了一个空数列!\n");
	printf("队列是否为空？%d(1:空0:否) ", QueueEmpty(&q));
	printf("队列长度为%d\n", QueueLength(&q));
	EnQueue(&q, 5);
	EnQueue(&q, -5);
	EnQueue(&q, 10);
	printf("插入三个元素(5,-5,10)后，队列的长度为%d\n", QueueLength(&q));
	printf("队列是否为空？%d(1:空0:否) ", QueueEmpty(&q));
	printf("队列的元素依次为： ");
	QueueTraverse(&q, print);
	i = GetHead_Q(&q, &d);
	if(i == OK)
		printf("队头元素是： %d\n", d);
	DeQueue(&q, &d);
	printf("删除了队头元素: %d\n", d);
	i = GetHead_Q(&q, &d);
	if(i == OK)
		printf("新的队头元素是： %d\n", d);
	ClearQueue(&q);
	printf("清空队列后: q.front = %u, q.rear = %u, \n"
		"            q.front->next = %u, q.queuesize = %d\n", 
		q.front, q.rear, q.front->next, q.queuesize);
	DestroyQueue(&q);
	printf("删除队列后: q.front = %u, q.rear = %u, "
		" q.queuesize = %d\n", q.front, q.rear, q.queuesize);

	system("PAUSE");
	return 0;
}