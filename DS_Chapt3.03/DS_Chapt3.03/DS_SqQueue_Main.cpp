#include "DS_Share.h"
#include "DS_SqQueue.h"
#include "DS_OP_SqQueue.h"

void print(QElemType i)
{
	printf("%d ", i);
}

int main()
{
	int i = 0, len;
	Status j;
	QElemType data;
	SqQueue Q;

	InitQueue(&Q);
	printf("Is the queue empty after initiation? %u(1:Yes 0:No)\n",
		QueueEmpty(&Q));

	printf("Please input integer queue elements(no more than %d),\n"
		"enter -1 to exit: ", MAX_QSIZE - 1);
	do 
	{
		scanf("%d", &data);
		if(-1 == data)
			break;
		i++;
		EnQueue(&Q, data);
	} while (i < MAX_QSIZE - 1);
	printf("The length of the queue: %d\n", QueueLength(&Q));
	printf("Is the queue empty now? %u(1:Yes 0:No)\n", QueueEmpty(&Q));

	printf("Dequeue front & Enqueue rear for %d times consequently:\n",
		MAX_QSIZE);
	for(len = 1; len <= MAX_QSIZE; len++)
	{
		DeQueue(&Q, &data);
		printf("Delete %d, input the element to insert: ", data);
		scanf("%d", &data);
		EnQueue(&Q, data);
	}
	len = QueueLength(&Q);
	printf("Now the elements in queue are: \n");
	QueueTraverse(&Q, print);

	j = GetHead(&Q, &data);
	printf("Now the head element in queue is: %d\n", data);

	ClearQueue(&Q);
	printf("After clear queue, is queue empty %u(1:Yes 0:No)\n", 
		QueueEmpty(&Q));
	DestroyQueue(&Q);

	system("PAUSE");

	return 0;
}