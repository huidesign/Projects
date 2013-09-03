#include "DS_OP_SqQueue.h"

void print(QElemType i)
{
	printf("%d ", i);
}

int main()
{
	Status SFlag;
	int i, n = 11;
	QElemType data;
	SqQueue Q;

	InitQueue(&Q);
	printf("Is Queue Empty After Initiation? %u(1:Yes 0:No)\n", 
		QueueEmpty(&Q));
	printf("The Length Of Queue is: %d\n", QueueLength(&Q));

	printf("Please Input %d Integers To Fullfill the Queue:\n", n);
	for(i = 0; i < n; i++)
	{
		scanf("%d", &data);
		EnQueue(&Q, data);
	}
	printf("The Length Of Queue is: %d\n", QueueLength(&Q));
	printf("Is Queue Empty Now? %u(1:Yes 0:No)\n", QueueEmpty(&Q));
	printf("Now The Elements in Queue are: \n");
	QueueTraverse(&Q, print);

	DeQueue(&Q, &data);
	printf("Delete front element: %d\n", data);
	printf("Now The Elements in Queue are: \n");
	QueueTraverse(&Q, print);

	SFlag = GetHead(&Q, &data);
	if(SFlag)
		printf("The front element is: %d\n", data);
	else
		printf("No front element(Empty Queue)\n");

	ClearQueue(&Q);
	printf("After Empty Queue, Is Queue Empty? %u(1:Yes 0:No)\n",
		QueueEmpty(&Q));
	SFlag = GetHead(&Q, &data);
	if(SFlag)
		printf("The front element is: %d\n", data);
	else
		printf("No front element(Empty Queue)\n");

	DestroyQueue(&Q);

	system("PAUSE");
	return 0;
}